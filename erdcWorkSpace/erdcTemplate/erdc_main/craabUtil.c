#include "craabUtil.h"

void turn_off_afe_power_things_down(void){
  LPDacCfg(0,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  AfeSwitchFullCfg(SWITCH_GROUP_T,SWID_ALLOPEN);
  
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
  
  AfeAdcPwrUp(BITM_AFE_AFECON_ADCEN);
  AfeAdcFiltCfg(SINC3OSR_5,SINC2OSR_178,LFPBYPEN_BYP,ADCSAMPLERATE_800K);
  pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
  delay_10us(5);  //50uS
}

//return current in uA;
float calcCurrent_hptia(uint16_t DAT, int RGAIN){
  //float vv = calcADCVolt(DAT);
  float RLOAD=0;
  int32_t adcSign = DAT;
  float vv = (adcSign-32768.0)/65536.0*V_ADC_REF_mV*-1;
  return ((vv/(RGAIN-(RLOAD-100)) *1000)+1)/2; //divided by 2 because PGA of  2 in hptia setup
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
  //float vv = calcADCVolt(DAT);
  int32_t adcSign = DAT;
  float vv = (adcSign-32768.0)/65536.0*V_ADC_REF_mV*2;
  return vv/(RGAIN-(RLOAD-100)) *1000;
}

float calcADCVolt(uint16_t DAT){
  return (DAT-32768.0)/65535*3600+1100;
}

uint16_t pollReadADC(void){
     /*start ADC conversion*/
   AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);

   /*Read ADC data*/
   while(!(pADI_AFE->ADCINTSTA&BITM_AFE_ADCINTSTA_ADCRDY));
   while(!(pADI_AFE->ADCINTSTA&BITM_AFE_ADCINTSTA_ADCRDY));
   while(!(pADI_AFE->ADCINTSTA&BITM_AFE_ADCINTSTA_ADCRDY));
   pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
   
   uint16_t adcRaw;
   adcRaw = pADI_AFE->ADCDAT;
   return adcRaw;
}
