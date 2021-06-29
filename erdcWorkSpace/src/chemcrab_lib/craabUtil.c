#include "craabUtil.h"

/*UART*/
volatile uint8_t  ucInCnt;
volatile uint32_t ucCOMIID0;
volatile uint32_t iNumBytesInFifo;
#define USE_SINC2_FOR_TEST 0

uint8_t  ucComRx;
uint8_t szInSring[UART_INBUFFER_LEN];
uint8_t* return_uart_buffer(void){
	return szInSring;
}
/*end UART*/

uint8_t adcModeSel = 0;
volatile uint8_t tmr2_timeout = 0;
volatile uint8_t adcRdy = 0;
volatile uint16_t ADCRAW = 0;

/*FLAG VARIABLE CONTROL*/
uint8_t flag = 0;
int flag_set(void)
{
	flag=1;
	return 1;
}

int flag_reset(void)
{
	flag=0;
	return 1;
}

int get_flag(void)
{
	return flag;
}
/*END FLAG VARIABLE CONTROL*/

void ClockInit(void)
{
  DigClkSel(DIGCLK_SOURCE_HFOSC);
  ClkDivCfg(1,1);
  AfeClkSel(AFECLK_SOURCE_HFOSC);
  AfeSysClkDiv(AFE_SYSCLKDIV_1);
}

// Configure the UART for 115200-8-N-1 baud rate
void UartInit(void)
{
  DioCfgPin(pADI_GPIO0,PIN10,1);               // Setup P0.10 as UART pin
  DioCfgPin(pADI_GPIO0,PIN11,1);               // Setup P0.11 as UART pin
  pADI_UART0->COMLCR2 = 0x3;                   // Set PCLk oversampling rate 32. (PCLK to UART baudrate generator is /32)
  UrtCfg(pADI_UART0,B9600,
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
}

void UART_Int_Handler(void)
{
   UrtLinSta(pADI_UART0);
   ucCOMIID0 = UrtIntSta(pADI_UART0);
   if ((ucCOMIID0 & 0xE) == 0xc || (ucCOMIID0 & 0xE) == 0x4)	          // Receive byte
   {
     iNumBytesInFifo = pADI_UART0->COMRFC;    // read the Num of bytes in FIFO
     for(uint8_t i = 0; i <iNumBytesInFifo;++i){
       ucComRx = UrtRx(pADI_UART0);
       szInSring[i]=ucComRx;
     }
     if (szInSring[0] == 27) {
       NVIC_SystemReset();
     }
     UrtFifoClr(pADI_UART0, BITM_UART_COMFCR_RFCLR// Clear the Rx/TX FIFOs
             |BITM_UART_COMFCR_TFCLR);
     flag_set();
   }
}

void turn_off_afe_power_things_down(void){
  LPDacCfg(0,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  AfeSwitchFullCfg(SWITCH_GROUP_T,SWID_ALLOPEN);

  powerDownADC();

  AfeLpTiaPwrDown(CHAN0, BITM_AFE_LPTIACON0_TIAPDEN|BITM_AFE_LPTIACON0_PAPDEN); //power down LPTIA and PA
  AfeHpTiaPwrUp(0); //power down hptia
  LPDacPwrCtrl(CHAN0, PWR_DOWN); //power down DAC
  AfePwrCfg(AFE_HIBERNATE); //put analog die to sleep
}

void adcCurrentSetup_lptia(uint8_t channel){
  //AfeSysCfg(ENUM_AFE_PMBW_LP,ENUM_AFE_PMBW_BW50);
  AfeAdcPgaCfg(GNPGA_1_5,0); //for current use GNPGA_4
  
  if(channel > 0){
    AfeAdcChan(MUXSELP_LPTIA1_P,MUXSELN_LPTIA1_N);
    //AfeAdcChan(MUXSELP_LPTIA1_LPF,MUXSELN_LPTIA1_N);
  }
  else{
    AfeAdcChan(MUXSELP_LPTIA0_P,MUXSELN_LPTIA0_N);
    //AfeAdcChan(MUXSELP_LPTIA0_LPF,MUXSELN_LPTIA0_N);
  }
  
  AfeAdcChopEn(1);
  AfeAdcIntCfg(BITM_AFE_ADCINTIEN_ADCRDYIEN);
  NVIC_EnableIRQ(AFE_ADC_IRQn);
  AfeAdcPwrUp(BITM_AFE_AFECON_ADCEN);
  
  AfeAdcFiltCfg(SINC3OSR_5,SINC2OSR_178,LFPBYPEN_NOBYP,ADCSAMPLERATE_800K);
  pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
  delay_10us(5);
}

void adcVoltageSetup_lptia(uint8_t channel){
    AfeSysCfg(ENUM_AFE_PMBW_LP,ENUM_AFE_PMBW_BW50);
    AfeAdcPgaCfg(GNPGA_1,0);
    
    if(channel > 0){
      AfeAdcChan(MUXSELP_VRE1,MUXSELN_VSET1P1);
    }
    else{
      AfeAdcChan(MUXSELP_VRE0,MUXSELN_VSET1P1);
    }
    
    
    
    AfeAdcChopEn(1);
    AfeAdcIntCfg(BITM_AFE_ADCINTIEN_ADCRDYIEN);
    NVIC_EnableIRQ(AFE_ADC_IRQn);
    AfeAdcPwrUp(BITM_AFE_AFECON_ADCEN);
    
    AfeAdcFiltCfg(SINC3OSR_5,SINC2OSR_178,LFPBYPEN_NOBYP,ADCSAMPLERATE_800K);
    pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
    delay_10us(5);
}

//return current in uA;
float calcCurrent_hptia(uint16_t DAT, int RGAIN){
  float RLOAD=100;      //RLOAD is fixed to 100ohms when using SE as HPTIA input
  int32_t adcSign = DAT;
  float vv = (adcSign-32768.0)/65535.0*V_ADC_REF_mV*-1;
  return -1*((vv/(RGAIN-(RLOAD-100)) *1000)+1)/2;
}

//void adcCurrentSetup_lptia(void){
//  AfeAdcChan(MUXSELP_LPTIA0_LPF,MUXSELN_LPTIA0_N);
//  AfeSysCfg(ENUM_AFE_PMBW_LP,ENUM_AFE_PMBW_BW50);
//  AfeAdcPgaCfg(GNPGA_2,0); //for current use GNPGA_4
//  AfeAdcChopEn(1);
//
//  AfeAdcPwrUp(BITM_AFE_AFECON_ADCEN);
//  AfeAdcFiltCfg(SINC3OSR_5,SINC2OSR_178,LFPBYPEN_BYP,ADCSAMPLERATE_800K);
//  pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
//  delay_10us(5);  //50uS
//}

void powerDownADC(void){
  /*power down ADC*/
   AfeAdcPwrUp(0);
   AfeAdcGo(ADCIDLE);
}

//return current in uA;
float calcCurrent_lptia(uint16_t DAT, int RGAIN, int RLOAD){
  int32_t adcSign = DAT;
  float vv = (adcSign-32768.0)/65536.0*V_ADC_REF_mV*2;
  return vv/(RGAIN-(RLOAD-100)) *1000;
}

float calcADCVolt(uint16_t DAT){
  return (DAT-32768.0)/65535*3600+1100;
}

#if defined ( __ICCARM__ )
   #pragma location="never_retained_ram"
   uint16_t szADCSamples[16000];   // 32KB SRAM can be used to gather ADC samples,
#elif defined (__CC_ARM)
  uint16_t szADCSamples[16000] __attribute__((section(".ARM.__at_0x20040000"))); // 32KB SRAM can be used to gather ADC samples,
#else
   #pragma message("WARNING: Need to place this variable in a large RAM section using your selected toolchain.")
#endif

uint16_t* return_adc_buffer(void){
	return szADCSamples;
}

void sensor_setup_cv(void){
    /*SNS INIT*/
  LPDacPwrCtrl(CHAN0,PWR_UP);
  LPDacCfg(CHAN0,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  LPDacWr(CHAN0, 62, 62*64);

  /*power up PA,TIA,no boost, full power*/
  AfeLpTiaPwrDown(CHAN0,0);
  AfeLpTiaAdvanced(CHAN0,BANDWIDTH_NORMAL,CURRENT_NOR);
  AfeLpTiaSwitchCfg(CHAN0,SWMODE_SHORT);  /*short TIA feedback for Sensor setup*/

  AfeLpTiaCon(CHAN0,LPTIA_RLOAD_0,LPTIA_RGAIN_96K,LPTIA_RFILTER_1M);
  AfeLpTiaSwitchCfg(CHAN0,SWMODE_NORM);  /*TIA switch to normal*/
  /*END SNS INIT*/
}

void hptia_setup(void){
  pADI_AFE->BUFSENCON = 0x37; // ADC Low Power 1.8V reference for faster wake up times, adc current limit, enables high power 1.8V adc reference
  AfeHpTiaSeCfg(HPTIASE_RTIA_80K,BITM_HPTIA_CTIA_4PF,0); //RGAIN of 80K

  LPDacCfg(0,LPDACSWDIAG,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  LPDacCfg(1,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  AfeLpTiaSwitchCfg(1,SWMODE_NORM);   // Ensure Channel 1 LPTIA switches set for normal mode
  AfeLpTiaSwitchCfg(0,SWMODE_RAMP);   // Ensure Channel 0 LPTIA switches set for Ramp mode

  AfeHpTiaCon(HPTIABIAS_VZERO0); //connect vzero0 to positive input of TIA
  AfeHpTiaPwrUp(true);

  AfeLpTiaSwitchCfg(CHAN0,SWMODE_RAMP);   //setup ULP TIA for Ramp test
  LPDacCfg(CHAN0,LPDACSWDIAG,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);  //change ULP DAC setting from DC to Diagnostic mode

  AfeSwitchFullCfg(SWITCH_GROUP_T,SWID_T9|SWID_T5_SE0RLOAD);   //short T5,T9 for SE0
}

//THIS IS A TEMPORARY FIX TO ADDRESS ISSUES WE'VE BEEN HAVING WITH THE HSTIA, SHOULD BE REPLACED WITH A MORE MODULAR SETUP FUNCTION
void AFE_SETUP_LPTIA_LPDAC(uint8_t channel){
  if(channel == CHAN0){
    pADI_ALLON->PWRMOD=0x8009;
    pADI_AFE->AFECON=0x90000;
    pADI_AFE->PMBW=0x4200C;
    pADI_AFE->ADCFILTERCON=0x2A11;
    pADI_AFE->ADCINTIEN=0x0;
    pADI_AFE->DFTCON=0x0;
    pADI_AFE->ADCCON=0x10221;
    pADI_AFE->CALDATLOCK=0xDE87A5A0;
    pADI_AFE->LPREFBUFCON=0x0;
    pADI_AFE->LPTIASW1=0x0;
    pADI_AFE->LPTIASW0=0x34;
    //pADI_AFE->LPTIASW0=0x3C;    //trying to fix high IR drop between RE and CE
    pADI_AFE->LPTIACON0=0x4038;
    pADI_AFE->LPDACSW0=0x34;
    pADI_AFE->LPDACCON0=0x1;
    pADI_AFE->LPDACCON1=0x2;
    pADI_AFE->HSDACCON=0x1FE;
    pADI_AFE->WGCON=0x4;
    pADI_AFE->WGFCW=0x45D1;
    pADI_AFE->WGAMPLITUDE=0x516;
    pADI_AFE->HSRTIACON=0x3E0;
    pADI_AFE->DE1RESCON=0xFD;
    pADI_AFE->DE0RESCON=0xFD;
    pADI_AFE->TSWFULLCON=0x0;
    delay_10us(1000);
  }
  else{
    pADI_ALLON->PWRMOD=0x8009;
    pADI_AFE->AFECON=0x90000;
    pADI_AFE->PMBW=0x4200C;
    pADI_AFE->ADCFILTERCON=0x2A11;
    pADI_AFE->ADCINTIEN=0x0;
    pADI_AFE->DFTCON=0x0;
    pADI_AFE->ADCCON=0x40322;   //Changed to connect ADC to CHAN1
    pADI_AFE->CALDATLOCK=0xDE87A5A0;
    pADI_AFE->LPREFBUFCON=0x0;
    pADI_AFE->LPTIASW1=0x34;     //Swapped CHAN0 and CHAN1 values here and below
    //pADI_AFE->LPTIASW1=0x3C;
    pADI_AFE->LPTIASW0=0x0;
    pADI_AFE->LPTIACON0=0x0;
    pADI_AFE->LPTIACON1=0x4038;
    pADI_AFE->LPDACSW0=0x0;
    pADI_AFE->LPDACSW1=0x34;
    pADI_AFE->LPDACCON0=0x2;
    pADI_AFE->LPDACCON1=0x1;
    pADI_AFE->HSDACCON=0x1FE;
    pADI_AFE->WGCON=0x4;
    pADI_AFE->WGFCW=0x45D1;
    pADI_AFE->WGAMPLITUDE=0x516;
    pADI_AFE->HSRTIACON=0x3E0;
    pADI_AFE->DE1RESCON=0xFD;
    pADI_AFE->DE0RESCON=0xFD;
    pADI_AFE->TSWFULLCON=0x0;
    delay_10us(1000); 
  }
}

void hptia_setup_parameters(uint32_t RTIA){
  pADI_AFE->BUFSENCON = 0x37; // ADC Low Power 1.8V reference for faster wake up times, adc current limit, enables high power 1.8V adc reference
  AfeHpTiaSeCfg(RTIA,BITM_HPTIA_CTIA_4PF,0); //RGAIN of 80K

  LPDacCfg(0,LPDACSWDIAG,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  LPDacCfg(1,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  //AfeLpTiaSwitchCfg(1,SWMODE_NORM);   // Ensure Channel 1 LPTIA switches set for normal mode
  //AfeLpTiaSwitchCfg(0,SWMODE_RAMP);   // Ensure Channel 0 LPTIA switches set for Ramp mode

  AfeHpTiaCon(HPTIABIAS_VZERO0); //connect vzero0 to positive input of TIA
  AfeHpTiaPwrUp(true);

  //AfeLpTiaSwitchCfg(CHAN0,SWMODE_RAMP);   //setup ULP TIA for Ramp test
  LPDacCfg(CHAN0,LPDACSWDIAG,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);  //change ULP DAC setting from DC to Diagnostic mode

  //AfeSwitchFullCfg(SWITCH_GROUP_T,SWID_T9|SWID_T5_SE0RLOAD);   //short T5,T9 for SE0
}

void lptia_setup_parameters(uint32_t RTIA){
  pADI_AFE->BUFSENCON = 0x37; // ADC Low Power 1.8V reference for faster wake up times, adc current limit, enables high power 1.8V adc reference
  AfeHpTiaSeCfg(RTIA,BITM_HPTIA_CTIA_4PF,0); //RGAIN of 80K

  LPDacCfg(0,LPDACSWDIAG,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  LPDacCfg(1,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  AfeLpTiaSwitchCfg(1,SWMODE_NORM);   // Ensure Channel 1 LPTIA switches set for normal mode
  AfeLpTiaSwitchCfg(0,SWMODE_RAMP);   // Ensure Channel 0 LPTIA switches set for Ramp mode

  //AfeHpTiaCon(HPTIABIAS_VZERO0); //connect vzero0 to positive input of TIA
  AfeHpTiaPwrUp(true);

  AfeLpTiaSwitchCfg(CHAN0,SWMODE_RAMP);   //setup ULP TIA for Ramp test
  LPDacCfg(CHAN0,LPDACSWDIAG,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);  //change ULP DAC setting from DC to Diagnostic mode

  AfeSwitchFullCfg(SWITCH_GROUP_T,SWID_T9|SWID_T5_SE0RLOAD);   //short T5,T9 for SE0
}

uint16_t HSRTIA_LOOKUP(uint8_t choice){
  switch(choice){
  case 0: return HPTIASE_RTIA_200;
  case 1: return HPTIASE_RTIA_1K;
  case 2: return HPTIASE_RTIA_5K;
  case 3: return HPTIASE_RTIA_10K;
  case 4: return HPTIASE_RTIA_20K;
  case 5: return HPTIASE_RTIA_40K;
  case 6: return HPTIASE_RTIA_80K;
  case 7: return HPTIASE_RTIA_160K;
  default: return HPTIASE_RTIA_80K;
  }
  return 0;
}

uint16_t LPRTIA_LOOKUP(uint8_t choice){
  switch(choice){
    case 0: return LPTIA_RGAIN_DISCONNECT;
    case 1: return LPTIA_RGAIN_1K;
    case 2: return LPTIA_RGAIN_2K;
    case 3: return LPTIA_RGAIN_3K;
    case 4: return LPTIA_RGAIN_4K;
    case 5: return LPTIA_RGAIN_6K;
    case 6: return LPTIA_RGAIN_8K;
    case 7: return LPTIA_RGAIN_10K;
    case 8: return LPTIA_RGAIN_12K;
    case 9: return LPTIA_RGAIN_16K;
    case 10: return LPTIA_RGAIN_20K;
    case 11: return LPTIA_RGAIN_24K;
    case 12: return LPTIA_RGAIN_30K;
    case 13: return LPTIA_RGAIN_32K;
    case 14: return LPTIA_RGAIN_40K;
    case 15: return LPTIA_RGAIN_48K;
    case 16: return LPTIA_RGAIN_64K;
    case 17: return LPTIA_RGAIN_85K;
    case 18: return LPTIA_RGAIN_96K;
    case 19: return LPTIA_RGAIN_100K;
    case 20: return LPTIA_RGAIN_120K;
    case 21: return LPTIA_RGAIN_128K;
    case 22: return LPTIA_RGAIN_160K;
    case 23: return LPTIA_RGAIN_196K;
    case 24: return LPTIA_RGAIN_256K;
    case 25: return LPTIA_RGAIN_512K;
    default: return LPTIA_RGAIN_1K;
  }
  return 0;
}

int HSRTIA_VAL_LOOKUP(uint32_t RGAIN){
  switch(RGAIN){
    case HPTIASE_RTIA_200:  return    200;
    case HPTIASE_RTIA_1K:   return   1000;
    case HPTIASE_RTIA_5K:   return   5000;
    case HPTIASE_RTIA_10K:  return  10000;
    case HPTIASE_RTIA_20K:  return  20000;
    case HPTIASE_RTIA_40K:  return  40000;
    case HPTIASE_RTIA_80K:  return  80000;
    case HPTIASE_RTIA_160K: return 160000;
  default : return 80000;
  }
  return 0;
}

int LPRTIA_VAL_LOOKUP(uint32_t RGAIN){
  switch(RGAIN){
    case LPTIA_RGAIN_DISCONNECT:        return 0;
    case LPTIA_RGAIN_1K:                return 1000;             
    case LPTIA_RGAIN_2K:                return 2000;
    case LPTIA_RGAIN_3K:                return 3000;
    case LPTIA_RGAIN_4K:                return 4000;
    case LPTIA_RGAIN_6K:                return 6000;
    case LPTIA_RGAIN_8K:                return 8000;                
    case LPTIA_RGAIN_10K:               return 10000;
    case LPTIA_RGAIN_12K:               return 12000;
    case LPTIA_RGAIN_16K:               return 16000;
    case LPTIA_RGAIN_20K:               return 20000;
    case LPTIA_RGAIN_24K:               return 24000;
    case LPTIA_RGAIN_30K:               return 30000;
    case LPTIA_RGAIN_32K:               return 32000;
    case LPTIA_RGAIN_40K:               return 40000;
    case LPTIA_RGAIN_48K:               return 48000;
    case LPTIA_RGAIN_64K:               return 64000;
    case LPTIA_RGAIN_85K:               return 85000;
    case LPTIA_RGAIN_96K:               return 96000;
    case LPTIA_RGAIN_100K:              return 100000;
    case LPTIA_RGAIN_120K:              return 120000;
    case LPTIA_RGAIN_128K:              return 128000;
    case LPTIA_RGAIN_160K:              return 160000;
    case LPTIA_RGAIN_196K:              return 196000;
    case LPTIA_RGAIN_256K:              return 256000;
    case LPTIA_RGAIN_512K:              return 512000;
    default: return 1000;
  }
  return 0;
}

//Temporary function to run tests with/without rheostat parameter input
//Set the return value to 0 to exclude rheostat resistance (RRI) from parameter input prompts
int rheostat_available(void){
  return 0;
}

//Identifies the int to pass to the Rheostat in order to set the comnfigurable rheostat resistance
//Returns an int between 0 and numPoints
uint16_t rheostat_resistance(uint16_t target_resistance){
  uint16_t numPoints = 256;
  uint16_t minRes = 0;
  uint16_t maxRes = 10000;
  uint16_t stepSize = (int)(maxRes-minRes)/numPoints;
  uint16_t i = 0;
  while(stepSize*i < target_resistance){
    i = i + 1;
  }
  if(stepSize*i-target_resistance > target_resistance - stepSize*(i-1)){
    i = i - 1;
  }
  return i;
}

int getVoltageInput(void){

  int voltage = 0;
  
  while(1){
    if(get_flag()){
      char v[5];
      uint8_t *uBuffer;
      uBuffer=return_uart_buffer();
      for(int i=0 ; i<5 ; ++i){
        v[i] = uBuffer[i];
      }
      
      voltage+=(v[4]-48)*1;
      voltage+=(v[3]-48)*10;
      voltage+=(v[2]-48)*100;
      voltage+=(v[1]-48)*1000;
      if(v[0] == '-'){
        voltage = -1*voltage;
      }
      flag_reset();
      return voltage;
    }
  }
}

//Returns a uint16_t representing  the UART input
uint16_t getParameter(int dec){
  
  uint16_t parameter = 0;
  
  while(1){
    if(get_flag()){
      if(dec==7){
          char v[7];
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          for(int i=0 ; i<dec ; ++i){
            v[i] = uBuffer[i];
          }
          parameter+=(v[6]-48);
          parameter+=(v[5]-48)*10;
          parameter+=(v[4]-48)*100;
          parameter+=(v[3]-48)*1000;
          parameter+=(v[2]-48)*10000;
          parameter+=(v[1]-48)*100000;
          parameter+=(v[0]-48)*1000000;
          flag_reset();
          return parameter;
      }
      if(dec==6){
          char v[6];
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          for(int i=0 ; i<dec ; ++i){
            v[i] = uBuffer[i];
          }
          parameter+=(v[5]-48);
          parameter+=(v[4]-48)*10;
          parameter+=(v[3]-48)*100;
          parameter+=(v[2]-48)*1000;
          parameter+=(v[1]-48)*10000;
          parameter+=(v[0]-48)*100000;
          flag_reset();
          return parameter;
      }
      if(dec==5){
          char v[5];
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          for(int i=0 ; i<dec ; ++i){
            v[i] = uBuffer[i];
          }
          parameter+=(v[4]-48);
          parameter+=(v[3]-48)*10;
          parameter+=(v[2]-48)*100;
          parameter+=(v[1]-48)*1000;
          parameter+=(v[0]-48)*10000;
          flag_reset();
          return parameter;
      }
      if(dec==4){
          char v[4];
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          for(int i=0 ; i<dec ; ++i){
            v[i] = uBuffer[i];
          }
          parameter+=v[3]-48;
          parameter+=(v[2]-48)*10;
          parameter+=(v[1]-48)*100;
          parameter+=(v[0]-48)*1000;
          flag_reset();
          return parameter;
      }
      if(dec==3){
          char v[3];
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          for(int i=0 ; i<dec ; ++i){
            v[i] = uBuffer[i];
          }
          parameter+=(v[2]-48);
          parameter+=(v[1]-48)*10;
          parameter+=(v[0]-48)*100;
          flag_reset();
          return parameter;
      }
      
      if(dec==2){
          char v[2];
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          for(int i=0 ; i<dec ; ++i){
            v[i] = uBuffer[i];
          }
          parameter+=(v[1]-48);
          parameter+=(v[0]-48)*10;
          flag_reset();
          return parameter;
      }
      
      if(dec==1){
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          parameter = uBuffer[0];
          flag_reset();
          return parameter;
      }
    }
  }
}

uint16_t getSensorChannel(void){
  //printf("Sensor Channel(0 or 1) : ");
  printf("[:SCI]");
  uint16_t sensChanIn = getParameter(1)-48;
  if(sensChanIn > 0){
    return CHAN1;
  }
  return CHAN0;
}

void GptCfgVoltammetry(uint16_t mvRate){
   GptLd(pADI_TMR2, sweeprateLookup(mvRate));      // Load timer 2
   GptCfg(pADI_TMR2,TCTL_CLK_HFOSC, TCTL_PRE_DIV64,
          BITM_TMR_CTL_MODE|
          BITM_TMR_CTL_RLD|
          BITM_TMR_CTL_EN);     // Enable Timer2 for periodic mode, counting down, using HFOSC as clock source
   
   NVIC_EnableIRQ(TMR2_EVT_IRQn);       // Enable Timer 2  interrupt source in NVIC
}

//Holds the program until a timeout interrupt is generated by timer 2               
void GptWaitForFlag(void){
  while(!tmr2_timeout){}//hold program until timer timeout flag is set
  tmr2_timeout = 0;
}

uint16_t sweeprateLookup(uint16_t mvRate){
  switch(mvRate){
    case 10: return 0x55B1;
    case 20: return 0x2AD8;
    case 30: return 0x1C90;
    case 40: return 0x156C;
    case 50: return 0x1123;
    case 60: return 0x0E48;
    case 70: return 0x0C3D;
    case 80: return 0x0AB6;
    case 90: return 0x0985;
    case 100: return 0x0891;
    case 150: return 0x05B5;
    case 200: return 0x0448;
    case 250: return 0x036D;
    case 300: return 0x02DB;
    case 350: return 0x0272;
    case 400: return 0x0224;
    case 450: return 0x01E7;
    case 500: return 0x01B6;
    default: return 0x1123;
  }
  return 0;
}

uint16_t getAdcVal(void){
  return ADCRAW;
}

void setAdcMode(uint8_t mode){
  adcModeSel = mode;
}

int burstSample(int mode, uint8_t chan){
  int sum = 0;
  int numSamples = 32;
  if(mode == 0){        //ADC is sampling from the LPTIA to measure current
    adcCurrentSetup_lptia(chan);

  }
  if(mode == 1){         //ADC is sampling from VREO/VRE1 to Reference capacitor to measure sensor potential
    adcVoltageSetup_lptia(chan);
  }
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  for(int i = 0 ; i<numSamples ; ++i){
    while(!adcRdy){};
    adcRdy = 0;
    sum = sum + getAdcVal();
  }
  return sum/numSamples;
}

//converts ADC value to volts for data outputting
float adc_to_volts(float adcVal){
  float VREF = 1.82;
  float ADCVBIAS_CAP = 1.11;
  float VIN = (VREF*((adcVal-32768)/(32768)))+ADCVBIAS_CAP;
  float shift = 0.030;
  return (VIN + shift);
}

//converts ADC value from LPTIA to microamps(uA) for data outputting
float adc_to_current(float adcVal, int RTIA){
  float kFactor = 1.835/1.82;
  float PGA_GAIN = 1.5;
  float fVolt = ((adcVal-32768)/PGA_GAIN)*V_ADC_REF_mV/32768*kFactor;
  return (((fVolt/RTIA*1000)-1));
}

void AfeAdc_Int_Handler(void){
  uint32_t sta;
  sta = pADI_AFE->ADCINTSTA;
  if(adcModeSel == 1){
    if(sta&BITM_AFE_ADCINTSTA_DFTRDY){
      pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_DFTRDY;	//clear DFTRDY interrupt bit
      dftRdy = 1;       //set dftRdy flag
      //pADI_AFE->AFECON &= (~(BITM_AFE_AFECON_DFTEN|BITM_AFE_AFECON_ADCCONVEN|BITM_AFE_AFECON_ADCEN));  //stop conversion
    }
  }
  else{
    if(sta&BITM_AFE_ADCINTSTA_ADCRDY){
      pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;   //clear ADCRDY interrupt bit
      ADCRAW = pADI_AFE->ADCDAT;
      adcRdy = 1;
      //pADI_AFE->AFECON &= (~(BITM_AFE_AFECON_DFTEN|BITM_AFE_AFECON_ADCCONVEN|BITM_AFE_AFECON_ADCEN));  //stop conversion
    }
  }
}

void GP_Tmr2_Int_Handler(void)
{
   volatile int uiT2STA = 0;
   uiT2STA = GptSta(pADI_TMR2);
   if((uiT2STA&0x0001)==0x0001)  //timeout event pending
   {
      GptClrInt(pADI_TMR2,BITM_TMR_CLRINT_TIMEOUT);// Clear Timer 2 timeout interrupt
      tmr2_timeout = 1;
   }
}