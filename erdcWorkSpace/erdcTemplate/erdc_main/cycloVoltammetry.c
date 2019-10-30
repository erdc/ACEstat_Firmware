#include "cycloVoltammetry.h"
#include "craabUtil.h"

#define MAX_BUFFER_LENGTH 16000

#if defined ( __ICCARM__ )
   #pragma location="never_retained_ram"
   uint16_t szADCSamples[16000];   // 32KB SRAM can be used to gather ADC samples,
#elif defined (__CC_ARM)
  uint16_t szADCSamples[16000] __attribute__((section(".ARM.__at_0x20040000"))); // 32KB SRAM can be used to gather ADC samples,
#else
   #pragma message("WARNING: Need to place this variable in a large RAM section using your selected toolchain.")
#endif

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

void cv_ramp(void){
  /*RAMP*/
  uint16_t Cbias, Czero;
  uint16_t ADCRAW;
  int RGAIN = 80000;
  uint16_t SETTLING_DELAY = 50;
  uint16_t RAMP_STEP_DELAY = 1000  ;          //delay before increasing step

  float vDiff;
  float tc;
    /*start wave and measurement*/
  Czero = 32;
  Cbias = 800;
  
  
  /*Ramp -468mV to 408.6mV*/
  for (Cbias = 800; Cbias < 3275; ++Cbias){ 
    LPDacWr(CHAN0, Czero, Cbias);         // Set VBIAS/VZERO output voltages 
    delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle 
    delay_10us(RAMP_STEP_DELAY);
    
    ADCRAW = pollReadADC();
    tc = calcCurrent_hptia(ADCRAW, RGAIN);
    vDiff = Cbias*0.54+200-1100.36;
    printf("Volt:%f,Current:%f\n", vDiff,tc);    
  }

  /*RAMP 408.06mV to -468mV*/
  for (Cbias = 3275; Cbias > 800; --Cbias){  
    LPDacWr(CHAN0, Czero, Cbias);         // Set VBIAS/VZERO output voltages 
    delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle 
    delay_10us(RAMP_STEP_DELAY);
    
    ADCRAW = pollReadADC();
    tc = calcCurrent_hptia(ADCRAW, RGAIN);
    vDiff = Cbias*0.54+200-1100.36;
    printf("Volt:%f,Current:%f\n", vDiff,tc);    
  }
  /*END RAMP*/
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
/*Imax = 0.9V/RGAIN*/
uint32_t sampleCount = 0;
#define mvStepDelay 147 //delay for 5mV/S
void cv_ramp_parameters(uint16_t start, uint16_t end, uint32_t RGAIN){
  uint16_t SETTLING_DELAY = 5;
  uint16_t RAMP_STEP_DELAY = 10*mvStepDelay;          //14.7mS 68 loops to achieve 50mV 14.7mS*68 gives 50mV per second
  float vDiff;
  float tc;
  uint16_t Cbias, Czero;
  uint16_t ADCRAW;
  
  uint16_t cStart = (start-200)/0.54;
  uint16_t cEnd =(end-200)/0.54;
  int RTIA = RTIA_VAL_LOOKUP(RGAIN);
  
  Czero = 32;
  Cbias = cStart;
  
  sampleCount = 0;
  
  for (Cbias = cStart; Cbias < cEnd; ++Cbias){ 
    LPDacWr(CHAN0, Czero, Cbias);         // Set VBIAS/VZERO output voltages 
    delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle 
    delay_10us(RAMP_STEP_DELAY);
    
    ADCRAW = pollReadADC();
    szADCSamples[sampleCount]=Cbias;
    sampleCount++;
    szADCSamples[sampleCount]=ADCRAW;
    sampleCount++;
  }

  for (Cbias = cEnd; Cbias > cStart; --Cbias){  
      LPDacWr(CHAN0, Czero, Cbias);         // Set VBIAS/VZERO output voltages 
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle 
      delay_10us(RAMP_STEP_DELAY);
      
      ADCRAW = pollReadADC();
      szADCSamples[sampleCount]=Cbias;
      sampleCount++;
      if(sampleCount>MAX_BUFFER_LENGTH) {
        printf("MEMORY OVERFLOW\n");
        sampleCount=0;
        break;
      }
      szADCSamples[sampleCount]=ADCRAW;
      sampleCount++;
      if(sampleCount>MAX_BUFFER_LENGTH) {
        printf("MEMORY OVERFLOW\n");
        sampleCount=0;
        break;
      }
    }
  printf("RANGE IS %f to %f\n", cStart*0.54+200-1100.36, cEnd*0.54+200-1100.36);
  printf("RGAIN VALUE IS %i\n", RTIA);
  for(uint32_t i = 0; i < sampleCount; i+=2){
    vDiff = szADCSamples[i]*0.54+200-1100.36; 
    tc = calcCurrent_hptia(szADCSamples[i+1], RTIA);
    printf("Volt:%f,Current:%f\n", vDiff,tc);   
  }  
}

void sqv_ramp_parameters(uint16_t start, uint16_t end, uint32_t RGAIN, uint16_t amplitude){
  uint16_t SETTLING_DELAY = 5;
  uint16_t RAMP_STEP_DELAY = 10*mvStepDelay;          //14.7mS 68 loops to achieve 50mV 14.7mS*68 gives 50mV per second
  float vDiff;
  float tc;
  uint16_t Cbias, Czero;
  uint16_t ADCRAW;
  
  uint16_t cStart = (start-200)/0.54;
  uint16_t cEnd =(end-200)/0.54;
  int RTIA = RTIA_VAL_LOOKUP(RGAIN);
  
  uint16_t amp = (amplitude-200)/0.54;
  
  Czero = 32;
  Cbias = cStart;
  
  sampleCount = 0;
  
  /*palmsense device does 2 sweps for some reason only reports one*/
  for (Cbias = cStart; Cbias < cEnd; Cbias+=10){ 
    LPDacWr(CHAN0, Czero, Cbias+amp);         
    delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle 
    delay_10us(1250); //delay 12.5ms
    LPDacWr(CHAN0, Czero, Cbias-amp);      
    delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle 
    delay_10us(1250); //delay 12.5ms
  }
  
  for (Cbias = cStart; Cbias < cEnd; Cbias+=10){ 
    LPDacWr(CHAN0, Czero, Cbias+amp);         
    delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle 
    delay_10us(1250); //delay 12.5ms
    ADCRAW = pollReadADC();
    szADCSamples[sampleCount]=Cbias;
    sampleCount++;
    if(sampleCount>MAX_BUFFER_LENGTH) {
        printf("MEMORY OVERFLOW\n");
        sampleCount=0;
        break;
      }
    szADCSamples[sampleCount]=ADCRAW;
    sampleCount++;
    if(sampleCount>MAX_BUFFER_LENGTH) {
        printf("MEMORY OVERFLOW\n");
        sampleCount=0;
        break;
      }
    
    LPDacWr(CHAN0, Czero, Cbias-amp);      
    delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle 
    delay_10us(1250); //delay 12.5ms
    ADCRAW = pollReadADC();
    szADCSamples[sampleCount]=ADCRAW;
    sampleCount++;
    if(sampleCount>MAX_BUFFER_LENGTH) {
        printf("MEMORY OVERFLOW\n");
        sampleCount=0;
        break;
      }
  }
  printf("RANGE IS %f to %f\n", cStart*0.54+200-1100.36, cEnd*0.54+200-1100.36);
  printf("RGAIN VALUE IS %i\n", RTIA);
  for(uint32_t i = 0; i < sampleCount; i+=3){
    vDiff = szADCSamples[i]*0.54+200-1100.36;
    tc = calcCurrent_hptia(szADCSamples[i+1]-szADCSamples[i+2], RTIA);
    printf("Volt:%f,Current:%f\n", vDiff,tc);  
  }
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
