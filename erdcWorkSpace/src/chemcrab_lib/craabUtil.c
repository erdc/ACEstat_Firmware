#include "craabUtil.h"

/*UART*/
volatile uint8_t  ucInCnt;
volatile uint32_t ucCOMIID0;
volatile uint32_t iNumBytesInFifo;

uint8_t  ucComRx;
uint8_t szInSring[UART_INBUFFER_LEN];
uint8_t* return_uart_buffer(void){
	return szInSring;
}
/*end UART*/

uint8_t adcModeSel = 0;
volatile uint8_t tmr2_timeout = 0;
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

void adcCurrentSetup_hptia(void){
  AfeAdcChan(MUXSELP_HPTIA_P,MUXSELN_HPTIA_N);
  AfeSysCfg(ENUM_AFE_PMBW_LP,ENUM_AFE_PMBW_BW50);
  AfeAdcPgaCfg(GNPGA_2,0); //for current use GNPGA_4
  AfeAdcChopEn(1);
  
  AfeAdcIntCfg(BITM_AFE_ADCINTIEN_ADCRDYIEN);
  NVIC_EnableIRQ(AFE_ADC_IRQn);
  AfeAdcPwrUp(BITM_AFE_AFECON_ADCEN);
  
  AfeAdcFiltCfg(SINC3OSR_5,SINC2OSR_178,LFPBYPEN_BYP,ADCSAMPLERATE_800K);
  pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
  delay_10us(5);  //50uS
}

//return current in uA;
float calcCurrent_hptia(uint16_t DAT, int RGAIN){
  float RLOAD=0;
  int32_t adcSign = DAT;
  float vv = (adcSign-32768.0)/65536.0*V_ADC_REF_mV*-1;
  return ((vv/(RGAIN-(RLOAD-100)) *1000)+1)/2; //divided by 2 because PGA of 2 in hptia setup
}


void adcCurrentSetup_lptia(void){
  AfeAdcChan(MUXSELP_LPTIA0_LPF,MUXSELN_LPTIA0_N);
  AfeSysCfg(ENUM_AFE_PMBW_LP,ENUM_AFE_PMBW_BW50);
  AfeAdcPgaCfg(GNPGA_2,0); //for current use GNPGA_4
  AfeAdcChopEn(1);

  AfeAdcPwrUp(BITM_AFE_AFECON_ADCEN);
  AfeAdcFiltCfg(SINC3OSR_5,SINC2OSR_178,LFPBYPEN_BYP,ADCSAMPLERATE_800K);
  pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
  delay_10us(5);  //50uS
}

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

void hptia_setup_parameters(uint32_t RTIA){
  pADI_AFE->BUFSENCON = 0x37; // ADC Low Power 1.8V reference for faster wake up times, adc current limit, enables high power 1.8V adc reference
  AfeHpTiaSeCfg(RTIA,BITM_HPTIA_CTIA_4PF,0); //RGAIN of 80K

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

uint16_t RTIA_LOOKUP(uint8_t choice){
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

int RTIA_VAL_LOOKUP(uint32_t RGAIN){
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

//Returns a uint16_t representing  the 4-digit UART input
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
        //not in use
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
        //Blank, have not required a 2-digit paramter yet
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