#include "ADuCM355.h"
#include "ClkLib.h"
#include "UrtLib.h"
#include "GptLib.h"
#include "AfeWdtLib.h"
#include "DioLib.h"
#include "RstLib.h"
#include "AfeTiaLib.h"
#include "PwrLib.h"
#include "craabUtil.h"
#include "cycloVoltammetry.h"

void ClockInit(void);
void UartInit(void);

#define  UART_INBUFFER_LEN 16
volatile uint8_t szInSring[UART_INBUFFER_LEN];
volatile uint8_t  ucInCnt;
volatile uint32_t ucCOMIID0;
volatile uint32_t iNumBytesInFifo;
/*end UART*/
uint8_t flag = 0;
uint16_t startingVoltage = 0;
uint16_t endingVoltage = 0;
uint16_t amplitude = 0;

char v[4];

int main(void){
  /*setup functions. only run when board powers on*/
  AfeWdtGo(false);
  ClockInit();
  UartInit();
  DioOenPin(pADI_GPIO2,PIN4,1);               // Enable P2.4 as Output to toggle DS2 LED
  DioPulPin(pADI_GPIO2,PIN4,1);               // Enable pull-up
  DioTglPin(pADI_GPIO2,PIN4);                 // Flash LED
  
  /*End powerup setup*/
  printf("Enter Starting Voltage and Ending Voltage. Middle is 1100mV\n");
  printf("Also enter a number for max current 0: 4.5mA, 1: 900uA, 2: 180uA,\n 3: 90uA, 4: 45uA, 5: 22.5uA, 6: 11.25uA, 7: 5.625uA\n");
  printf("Also enter amplitide\n");
  printf("Ex: 070015004100 is -400 to 400 max current 45uA Amplitude 100\n");
  
  while(1){
if(flag){
    DioTglPin(pADI_GPIO2,PIN4);           // Flash LED  
    
    for (int i = 0; i < 4; ++i){
      v[i]=szInSring[i];
    }
    startingVoltage=0;
    startingVoltage+=v[3]-48;
    startingVoltage+=(v[2]-48)* 10;
    startingVoltage+=(v[1]-48)*100;
    startingVoltage+=(v[0]-48)*1000;

    for (int i = 0; i < 4; ++i){
      v[i]=szInSring[4+i];
    }
    endingVoltage=0;
    endingVoltage+=v[3]-48;
    endingVoltage+=(v[2]-48)* 10;
    endingVoltage+=(v[1]-48)*100;
    endingVoltage+=(v[0]-48)*1000;
    
    uint8_t RTIACHOICE = szInSring[8]-48;
    uint32_t RGAIN = RTIA_LOOKUP(RTIACHOICE);
    
    for (int i = 0; i < 3; ++i){
      v[i]=szInSring[9+i];
    }
    amplitude = 0;
    amplitude += (v[0]-48)*100;
    amplitude += (v[1]-48)*10;
    amplitude += (v[2]-48);
    
    /*cv ramp setup*/
    AfePwrCfg(AFE_ACTIVE);  //set AFE power mode to active
    
    /*LPTIA REQUIRED TO HAVE DAC OUTPUT*/
    /*power up PA,TIA,no boost, full power*/
    AfeLpTiaPwrDown(CHAN0,0);
    AfeLpTiaAdvanced(CHAN0,BANDWIDTH_NORMAL,CURRENT_NOR);
    AfeLpTiaSwitchCfg(CHAN0,SWMODE_SHORT);  /*short TIA feedback for Sensor setup*/
    AfeLpTiaCon(CHAN0,LPTIA_RLOAD_0,LPTIA_RGAIN_96K,LPTIA_RFILTER_1M);
    AfeLpTiaSwitchCfg(CHAN0,SWMODE_NORM);  /*TIA switch to normal*/
    /*LPTIA REQUIRED TO HAVE DAC OUTPUT*/
    
    hptia_setup_parameters(RGAIN);
    adcCurrentSetup_hptia();
    /*end cv ramp setup*/
    
    /*RAMP HERE*/
    sqv_ramp_parameters(startingVoltage,endingVoltage,RGAIN, amplitude);
    /*END RAMP*/
    
    turn_off_afe_power_things_down();
    DioTglPin(pADI_GPIO2,PIN4);           // Flash LED
    flag = 0;
    }
  }
  /*CLEANUP turn things off*/
  turn_off_afe_power_things_down();
  DioTglPin(pADI_GPIO2,PIN4);           // Flash LED
  /******************************************************************************************************/
  //PwrCfg(ENUM_PMG_PWRMOD_HIBERNATE,BITM_PMG_PWRMOD_MONVBATN,BITM_PMG_SRAMRET_BNK2EN); //SLEEP

  return 0;
}

void ClockInit(void)
{
   DigClkSel(DIGCLK_SOURCE_HFOSC);
   ClkDivCfg(1,1);
   AfeClkSel(AFECLK_SOURCE_HFOSC);
   AfeSysClkDiv(AFE_SYSCLKDIV_1);
}

/*****************************************************************************/
// Configure the UART for 115200-8-N-1 baud rate
void UartInit(void)
{
  DioCfgPin(pADI_GPIO0,PIN10,1);               // Setup P0.10 as UART pin
  DioCfgPin(pADI_GPIO0,PIN11,1);               // Setup P0.11 as UART pin
  pADI_UART0->COMLCR2 = 0x3;                   // Set PCLk oversampling rate 32. (PCLK to UART baudrate generator is /32)
  UrtCfg(pADI_UART0,B115200,
         (BITM_UART_COMLCR_WLS|3),0);          // Configure UART for 115200 baud rate
  UrtFifoCfg(pADI_UART0, RX_FIFO_8BYTE,      // Configure the UART FIFOs for 8 bytes deep
             BITM_UART_COMFCR_FIFOEN);
  UrtFifoClr(pADI_UART0, BITM_UART_COMFCR_RFCLR// Clear the Rx/TX FIFOs
             |BITM_UART_COMFCR_TFCLR);
  UrtIntCfg(pADI_UART0,BITM_UART_COMIEN_ERBFI |
            BITM_UART_COMIEN_ETBEI |
            BITM_UART_COMIEN_ELSI);            // Enable Rx, Tx and Rx buffer full Interrupts
  /*ADDED*/ 
  NVIC_EnableIRQ(UART_EVT_IRQn);              // Enable UART interrupt source in NVIC
  /*Enable UART wakeup intterupt*/
  //NVIC_EnableIRQ(AFE_EVT3_IRQn);    //UART_RX connected to EXT Int3
}

uint8_t  ucComRx;

void UART_Int_Handler(void)
{
   UrtLinSta(pADI_UART0);
   ucCOMIID0 = UrtIntSta(pADI_UART0);
   if ((ucCOMIID0 & 0xE) == 0x4)	          // Receive byte
   {
     printf("Byte Received\n");
     iNumBytesInFifo = pADI_UART0->COMRFC;    // read the Num of bytes in FIFO
     for(uint8_t i = 0; i <iNumBytesInFifo;++i){
       ucComRx = UrtRx(pADI_UART0);
       szInSring[i]=ucComRx;
     }
     UrtFifoClr(pADI_UART0, BITM_UART_COMFCR_RFCLR// Clear the Rx/TX FIFOs
             |BITM_UART_COMFCR_TFCLR);
     flag = 1;
   }
}