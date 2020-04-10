#include "voltammetry.h"

/***************CYCLIC VOLTAMMETRY**************/
void runCV(uint8_t* szInSring){
  uint16_t cvStartVolt = 0;
  uint16_t cvMidVolt = 0;
  uint16_t cvEndVolt = 0;
  char v[4];

  for (int i = 0; i < 4; ++i){
    v[i]=szInSring[i];
  }
  cvStartVolt=0;
  cvStartVolt+=v[3]-48;
  cvStartVolt+=(v[2]-48)* 10;
  cvStartVolt+=(v[1]-48)*100;
  cvStartVolt+=(v[0]-48)*1000;

  for (int i = 0; i < 4; ++i){
    v[i]=szInSring[4+i];
  }
  cvMidVolt=0;
  cvMidVolt+=v[3]-48;
  cvMidVolt+=(v[2]-48)* 10;
  cvMidVolt+=(v[1]-48)*100;
  cvMidVolt+=(v[0]-48)*1000;

  for (int i = 0; i < 4; ++i){
    v[i]=szInSring[8+i];
  }
  cvEndVolt=0;
  cvEndVolt+=v[3]-48;
  cvEndVolt+=(v[2]-48)* 10;
  cvEndVolt+=(v[1]-48)*100;
  cvEndVolt+=(v[0]-48)*1000;

  uint8_t RTIACHOICE = szInSring[12]-48;
  uint32_t RGAIN = RTIA_LOOKUP(RTIACHOICE);
  /*cv ramp setup*/
  AfePwrCfg(AFE_ACTIVE);  //set AFE power mode to active

  LPDacPwrCtrl(CHAN0,PWR_UP);
  LPDacCfg(CHAN0,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  LPDacWr(CHAN0, 62, 62*64);

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

  cv_ramp_parameters(cvStartVolt,cvMidVolt,cvEndVolt,RGAIN);

  /*END RAMP*/

  turn_off_afe_power_things_down();
  DioTglPin(pADI_GPIO2,PIN4);           // Flash LED
}

void cv_ramp_parameters(uint16_t start, uint16_t mid, uint16_t end, uint32_t RGAIN){
  uint16_t SETTLING_DELAY = 5;
  uint16_t RAMP_STEP_DELAY = 10*mvStepDelay;          //14.7mS 68 loops to achieve 50mV 14.7mS*68 gives 50mV per second
  uint16_t Cbias, Czero;
  uint16_t ADCRAW;

  uint16_t cStart = (start-200)/0.54;
  uint16_t cMid = (mid-200)/0.54;
  uint16_t cEnd =(end-200)/0.54;
  int RTIA = RTIA_VAL_LOOKUP(RGAIN);

  Czero = 26;
  Cbias = cStart;

  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();

  for (Cbias = cStart; Cbias < cMid; ++Cbias){
    LPDacWr(CHAN0, Czero, Cbias);         // Set VBIAS/VZERO output voltages
    delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
    delay_10us(RAMP_STEP_DELAY);

    ADCRAW = pollReadADC();
    szADCSamples[sampleCount]=Cbias;
    sampleCount++;
    szADCSamples[sampleCount]=ADCRAW;
    sampleCount++;
  }

  for (Cbias = cMid; Cbias > cEnd; --Cbias){
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
  printCVResults(cStart,cMid,cEnd,sampleCount,RTIA);

}

void printCVResults(float cStart, float cMid, float cEnd, int sampleCount, int RTIA){
  float midVoltage = 1093.88;
  printf("RANGE IS %f to %f to %f\n", cStart*0.54+200-midVoltage, cMid*0.54+200-midVoltage, cEnd*0.54+200-midVoltage);
  printf("RGAIN VALUE IS %i\n", RTIA);
  uint16_t* szADCSamples = return_adc_buffer();
  float tc, vDiff;
  for(uint32_t i = 0; i < sampleCount; i+=2){
    vDiff = szADCSamples[i]*0.54+200-1100.36;
    tc = calcCurrent_hptia(szADCSamples[i+1], RTIA);
    //printf("Volt:%f,Current:%f\n", vDiff,tc);
    printf("%f,%f\n", vDiff,tc);
  }
}
/****************END CYCLIC VOLTAMMETRY**********************/

/****************SQUARE WAVE VOLTAMMETRY***************************/
void sqv_dep_time(uint16_t start, uint16_t time){
	uint16_t Cbias, Czero;
	uint16_t cStart = (start-200)/0.54;

	Czero=32;
	Cbias=cStart;

	LPDacWr(CHAN0, Czero, Cbias);
	delay_10us(time*100*1000);
};

void sqv_ramp_parameters(uint16_t start, uint16_t end, uint32_t RGAIN, uint16_t amplitude, int dep){
  uint16_t SETTLING_DELAY = 5;
  uint16_t RAMP_STEP_DELAY = 10*mvStepDelay;          //14.7mS 68 loops to achieve 50mV 14.7mS*68 gives 50mV per second
  uint16_t Cbias, Czero;
  uint16_t ADCRAW;

  uint16_t cStart = (start-200)/0.54;
  uint16_t cEnd =(end-200)/0.54;
  int RTIA = RTIA_VAL_LOOKUP(RGAIN);

  uint16_t amp = (amplitude-200)/0.54;

  Czero = 26;
  Cbias = cStart;

  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();

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
  printSWVResults(cStart, cEnd, amplitude, sampleCount, RTIA, dep);
}

void runSWV(uint8_t* szInSring){
  uint16_t SWVstartingVoltage = 0;
  uint16_t SWVendingVoltage = 0;
  uint16_t SWVamplitude = 0;
  uint16_t depTime = 0;
  char v[4];

  for (int i = 0; i < 4; ++i){
    v[i]=szInSring[i];
  }

  SWVstartingVoltage=0;
  SWVstartingVoltage+=v[3]-48;
  SWVstartingVoltage+=(v[2]-48)* 10;
  SWVstartingVoltage+=(v[1]-48)*100;
  SWVstartingVoltage+=(v[0]-48)*1000;

  for (int i = 0; i < 4; ++i){
    v[i]=szInSring[4+i];
  }
  SWVendingVoltage=0;
  SWVendingVoltage+=v[3]-48;
  SWVendingVoltage+=(v[2]-48)* 10;
  SWVendingVoltage+=(v[1]-48)*100;
  SWVendingVoltage+=(v[0]-48)*1000;

  uint8_t RTIACHOICE = szInSring[8]-48;
  uint32_t RGAIN = RTIA_LOOKUP(RTIACHOICE);

  for (int i = 0; i < 3; ++i){
    v[i]=szInSring[9+i];
  }
  SWVamplitude = 0;
  SWVamplitude += (v[0]-48)*100;
  SWVamplitude += (v[1]-48)*10;
  SWVamplitude += (v[2]-48);

  for (int i = 0; i < 3; ++i){
    v[i]=szInSring[12+i];
  }
  depTime = 0;
  depTime += (v[0]-48)*100;
  depTime += (v[1]-48)*10;
  depTime += (v[2]-48);

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
  sqv_dep_time(SWVstartingVoltage, depTime);
  sqv_ramp_parameters(SWVstartingVoltage,SWVendingVoltage,RGAIN, SWVamplitude, depTime);
  /*END RAMP*/

  turn_off_afe_power_things_down();
  DioTglPin(pADI_GPIO2,PIN4);           // Flash LED
}

void printSWVResults(float cStart, float cEnd, uint16_t amp, int sampleCount, int RTIA, int dep){
  float midVoltage = 1093.88;
  printf("Range is %f to %f\n", cStart*0.54+200-midVoltage, cEnd*0.54+200-midVoltage);
  printf("Rgain value is %i\n", RTIA);
  printf("Amplitude is %i\n", amp);
  printf("Deposition time is %i\n", dep);
  uint16_t* szADCSamples = return_adc_buffer();
  float vDiff, tc;

  for(uint32_t i = 0; i < sampleCount; i+=3){
    vDiff = szADCSamples[i]*0.54+200-1100.36;
    tc = calcCurrent_hptia(szADCSamples[i+1]-szADCSamples[i+2], RTIA);
    //printf("Volt:%f,Current:%f\n", vDiff,tc);
    printf("%f,%f\n", vDiff,tc);
  }
}
/*************END SQUARE WAVE VOLTAMMETRY**************************/
