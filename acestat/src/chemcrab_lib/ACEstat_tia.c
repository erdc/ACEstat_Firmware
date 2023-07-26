#include "ACEstat_tia.h"
#include "ACEstat_misc.h"

uint16_t HSRTIA_LOOKUP(uint8_t choice){
  
  /**Mask names show TIA feedback resistance in Ohms*/
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
  
  /**Mask names show TIA feedback resistance in Ohms*/
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
  
  /**Integer value of TIA resistance needed for ADC conversions*/
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
  
  /**Integer value of TIA resistance needed for ADC conversions*/
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

void AFE_SETUP_LPTIA_LPDAC(uint8_t sensor_channel){
  if(sensor_channel == CHAN0){
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
    pADI_AFE->LPTIACON0=0x58;
    pADI_AFE->HSTIACON=0x1;
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
    pADI_AFE->ADCCON=0x40322;                   //Changed to connect ADC to CHAN1
    pADI_AFE->CALDATLOCK=0xDE87A5A0;
    pADI_AFE->LPREFBUFCON=0x0;
    pADI_AFE->LPTIASW1=0x34;                    //Swapped CHAN0 and CHAN1 values here and below
    //pADI_AFE->LPTIASW1=0x3C;
    pADI_AFE->LPTIASW0=0x0;
    pADI_AFE->LPTIACON0=0x0;
    pADI_AFE->LPTIACON1=0x4038;
    pADI_AFE->HSTIACON=0x1;
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
  pADI_AFE->BUFSENCON = 0x37;                   //ADC Low Power 1.8V reference for faster wake up times, adc current limit, enables high power 1.8V adc reference
  AfeHpTiaSeCfg(RTIA,BITM_HPTIA_CTIA_4PF,0);    //RGAIN of 80K

  LPDacCfg(0,LPDACSWDIAG,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  LPDacCfg(1,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  AfeLpTiaSwitchCfg(1,SWMODE_NORM);             //Ensure Channel 1 LPTIA switches set for normal mode
  AfeLpTiaSwitchCfg(0,SWMODE_RAMP);             //Ensure Channel 0 LPTIA switches set for Ramp mode

  AfeHpTiaCon(HPTIABIAS_VZERO0);                //connect vzero0 to positive input of TIA
  AfeHpTiaPwrUp(true);

  AfeLpTiaSwitchCfg(CHAN0,SWMODE_RAMP);         //setup ULP TIA for Ramp test
  LPDacCfg(CHAN0,LPDACSWDIAG,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);  //change ULP DAC setting from DC to Diagnostic mode

  //AfeSwitchFullCfg(SWITCH_GROUP_T,SWID_T9|SWID_T5_SE0RLOAD);   //short T5,T9 for SE0
}

void lptia_setup_parameters(uint32_t RTIA){
  pADI_AFE->BUFSENCON = 0x37;                   //ADC Low Power 1.8V reference for faster wake up times, adc current limit, enables high power 1.8V adc reference
  AfeHpTiaSeCfg(RTIA,BITM_HPTIA_CTIA_4PF,0);    //RGAIN of 80K

  LPDacCfg(0,LPDACSWDIAG,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  LPDacCfg(1,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  AfeLpTiaSwitchCfg(1,SWMODE_NORM);             //Ensure Channel 1 LPTIA switches set for normal mode
  AfeLpTiaSwitchCfg(0,SWMODE_RAMP);             //Ensure Channel 0 LPTIA switches set for Ramp mode

  //AfeHpTiaCon(HPTIABIAS_VZERO0);              //connect vzero0 to positive input of TIA
  AfeHpTiaPwrUp(true);

  AfeLpTiaSwitchCfg(CHAN0,SWMODE_RAMP);         //setup ULP TIA for Ramp test
  LPDacCfg(CHAN0,LPDACSWDIAG,VBIAS12BIT_VZERO6BIT,LPDACREF2P5); //change ULP DAC setting from DC to Diagnostic mode

  AfeSwitchFullCfg(SWITCH_GROUP_T,SWID_T9|SWID_T5_SE0RLOAD);    //short T5,T9 for SE0
}

void AFE_SETUP_VOLTAMMETRY(uint8_t channel, uint32_t RTIA){
  AfePwrCfg(AFE_ACTIVE);                        //set AFE power mode to active
  LPDacPwrCtrl(channel,PWR_UP);                 //power up LPDAC on requested sensor_channel
  LPDacCfg(channel,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);     //config DAC on requested sensor_channel
  AfeLpTiaPwrDown(channel,0);                   //power up LPTIA on requested sensor_channel
  AfeLpTiaAdvanced(channel,BANDWIDTH_NORMAL,CURRENT_NOR);
  AfeLpTiaCon(channel,LPTIA_RLOAD_0,LPTIA_RGAIN_96K,LPTIA_RFILTER_1M); 
  delay_10us(1000);
  AFE_SETUP_LPTIA_LPDAC(channel);               //ensure LPTIA/LPDAC registers match required configuration
  AfeLpTiaCon(channel, LPTIA_RLOAD_0, RTIA, LPTIA_RFILTER_DISCONNECT);    //Setup LPTIA gain to match user input
}