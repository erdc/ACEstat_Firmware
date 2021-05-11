#include "voltammetry.h"

/***************CYCLIC VOLTAMMETRY**************/
void runCV(void){
  setAdcMode(0);
  
  uint8_t cvSensChan = getSensorChannel();
  
  //printf("Zero voltage between 0000mV - 9999mV : ");
  printf("[:ZVI]");
  uint16_t cvZeroVolt = getParameter(4);
  
  //printf("Starting voltage between 0000mV - 9999mV : ");
  printf("[:SVI]");
  uint16_t cvStartVolt = getParameter(4);
  
  //printf("Vertex voltage between 0000mV - 9999mV : ");
  printf("[:VVI]");
  uint16_t cvVertexVolt = getParameter(4);
  
  //printf("Ending voltage between 0000mV - 9999mV : ");
  printf("[:EVI]");
  uint16_t cvEndVolt = getParameter(4);
  
  //printf("Voltage sweep rate between 000mV/s - 999mV/s : ");
  printf("[:SRI]");
  uint16_t sweepRate = getParameter(3);
  
  //printf("Equilibrium Time 0000s - 9999s");
  printf("[:TEI]");
  uint16_t tEquilibrium = getParameter(4);
  
  if(rheostat_available()){
    //printf("Rheostat resistance 0000ohm - 9999ohm);
    printf("[:RRI]");
    uint16_t rheostatRes = getParameter(4);
    uint16_t rheostatInput = rheostat_resistance(rheostatRes);
  }
  
  //printf("TIA Gain Resistor:\n");
  //printf("2 Digits 00-25\n");
  printf("[:RTIAI]");
  uint8_t RTIACHOICE = getParameter(2);
  uint32_t RGAIN = LPRTIA_LOOKUP(RTIACHOICE); //PASS INT VAL RATHER THAN ASCII
  
  /*cv ramp setup*/
  AfePwrCfg(AFE_ACTIVE);  //set AFE power mode to active

  LPDacPwrCtrl(cvSensChan,PWR_UP);
  LPDacCfg(cvSensChan,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);

  /*LPTIA REQUIRED TO HAVE DAC OUTPUT*/
  /*power up PA,TIA,no boost, full power*/
  AfeLpTiaPwrDown(cvSensChan,0);
  AfeLpTiaAdvanced(cvSensChan,BANDWIDTH_NORMAL,CURRENT_NOR);
  AfeLpTiaCon(cvSensChan,LPTIA_RLOAD_0,LPTIA_RGAIN_96K,LPTIA_RFILTER_1M); 
  delay_10us(1000);
  
  //Temporary fix to test LPTIA functionality.  Sets up AFE according to example configuration
  AFE_SETUP_LPTIA_LPDAC(cvSensChan);
  AfeLpTiaCon(cvSensChan, LPTIA_RLOAD_100, RGAIN, LPTIA_RFILTER_DISCONNECT);   //temporary re-introduction of configrable gain for testing

  /*RAMP HERE*/
  equilibrium_delay(cvSensChan, cvStartVolt, cvZeroVolt, tEquilibrium);
  cv_ramp_parameters(cvSensChan, cvZeroVolt,cvStartVolt,cvVertexVolt,cvEndVolt,RGAIN, sweepRate);
  /*END RAMP*/

  turn_off_afe_power_things_down();
  printf("[END:CV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

void cv_ramp_parameters(uint8_t chan, uint16_t zeroV, uint16_t startV, uint16_t vertexV, uint16_t endV, uint32_t RGAIN, uint16_t sweepRate){    

  
  
  uint16_t SETTLING_DELAY = 5;
  uint16_t DACSHIFT = 0;
  uint16_t cBias, cZero;
  GptCfgVoltammetry(sweepRate); //configure general-purpose digital timer to use chosen sweeprate
  uint16_t cStart = ((startV-200)/0.54)-DACSHIFT;
  uint16_t cVertex = ((vertexV-200)/0.54)-DACSHIFT;
  uint16_t cEnd =((endV-200)/0.54)-DACSHIFT;
  int RTIA = LPRTIA_VAL_LOOKUP(RGAIN);
  
  cZero = (zeroV-200)/34.38;
  cBias = cStart;
  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  //DAC step increment.  Step size is roughly inc*0.54mV
  uint16_t inc = 1;
  
  //Sweep starts at a negative voltage
  if(startV < vertexV){
    for (cBias = cStart; cBias < cVertex; cBias = cBias + inc){
      LPDacWr(chan, cZero, cBias);         // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,chan);
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,chan);
        sampleCount++;
      }
    }
    for (cBias = cVertex; cBias > cEnd; cBias = cBias - inc){
      LPDacWr(chan, cZero, cBias);         // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,chan);
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,chan);
        sampleCount++;
      }
    }
  }
  //Sweep starts at a positive voltage
  else{
    for (cBias = cStart; cBias > cVertex; cBias = cBias - inc){
      LPDacWr(chan, cZero, cBias);         // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,chan);
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,chan);
        sampleCount++;
      }
    }
    
    for (cBias = cVertex; cBias < cEnd; cBias = cBias + inc){
      LPDacWr(chan, cZero, cBias);         // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,chan);
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,chan);
        sampleCount++;
      }
    }
  }

  //Open the RE/CE connections to put the sensor in "open circuit" state
  pADI_AFE->LPTIASW0=0x0;
  pADI_AFE->LPDACSW0=0x20;
  
  printCVResults(cZero,cStart,cVertex,cEnd,sampleCount,RTIA);
}

void printCVResults(float cZero, float cStart, float cVertex, float cEnd, int sampleCount, int RTIA){
  float zeroVoltage = 200+(cZero*34.38);
  printf("[RANGE:%f,%f,%f]", cStart*0.54+200-zeroVoltage, cVertex*0.54+200-zeroVoltage, cEnd*0.54+200-zeroVoltage);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  uint16_t* szADCSamples = return_adc_buffer();
  float tc, vDiff;
  for(uint32_t i = 0; i < sampleCount; i+=2){
    vDiff = (zeroVoltage/1000) - adc_to_volts(szADCSamples[i]);
    tc = adc_to_current(szADCSamples[i+1], RTIA);
    printf("%f,%f"EOL, vDiff,tc);
  }
  printf("]");
}
/****************END CYCLIC VOLTAMMETRY**********************/

/****************SQUARE WAVE VOLTAMMETRY***************************/

void runSWV(void){
  setAdcMode(0);
  
  uint8_t swvSensChan = getSensorChannel();
  
  //printf("Zero voltage (0000mV - 9999mV) : ");
  printf("[:ZVI]");
  uint16_t swvZeroVolt = getParameter(4);
  
  printf("[:SVI]");
  //printf("Starting voltage (0000mV - 9999mV) : ");
  uint16_t swvStartVolt = getParameter(4);
  
  //printf("Ending voltage (0000mV - 9999mV) : ");
  printf("[:EVI]");
  uint16_t swvEndVolt = getParameter(4);
  
  printf("[:AMPI]");
  //printf("Squarewave Pk-Pk amplitude (000mV - 999mV) : ");
  uint16_t swvAmp = getParameter(3);
  
  printf("[:STEPI]");
  //printf("Voltage step size between squarewave cycles, in mV");
  uint16_t swvStep = getParameter(3);
  
  printf("[:FREQI]");
  //printf("Squarewave frequency (00000Hz - 99999Hz) : ");
  uint16_t swvFreq = getParameter(5);
  
  printf("[:TEI]");
  //printf("Equilibrium time between 0000s and 9999s : ");
  uint16_t tEquilibrium = getParameter(4);
  
  if(rheostat_available()){
    //printf("Rheostat resistance 0000ohm - 9999ohm);
    printf("[:RRI]");
    uint16_t rheostatRes = getParameter(4);
    uint16_t rheostatInput = rheostat_resistance(rheostatRes);
  }
  
  //printf("Current Limit:\n");
  //printf("0: 4.5mA\n1: 900uA\n2: 180uA\n3: 90uA\n4: 45uA\n5: 22.5uA\n6: 11.25uA\n7: 5.625uA\n");
  printf("[:RTIAI]");
  uint8_t RTIACHOICE = getParameter(2);
  uint32_t RGAIN = LPRTIA_LOOKUP(RTIACHOICE-48); //-48 because an ascii character is passed. 
  
  /*swv ramp setup*/
  AfePwrCfg(AFE_ACTIVE);  //set AFE power mode to active

  LPDacPwrCtrl(swvSensChan,PWR_UP);
  LPDacCfg(swvSensChan,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);

  /*LPTIA REQUIRED TO HAVE DAC OUTPUT*/
  /*power up PA,TIA,no boost, full power*/
  AfeLpTiaPwrDown(swvSensChan,0);
  AfeLpTiaAdvanced(swvSensChan,BANDWIDTH_NORMAL,CURRENT_NOR);
  AfeLpTiaCon(swvSensChan,LPTIA_RLOAD_0,LPTIA_RGAIN_96K,LPTIA_RFILTER_1M); 
  delay_10us(1000);
  
  //Temporary fix to test LPTIA functionality.  Sets up AFE according to example configuration
  AFE_SETUP_LPTIA_LPDAC(swvSensChan);
  AfeLpTiaCon(swvSensChan, LPTIA_RLOAD_10, RGAIN, LPTIA_RFILTER_DISCONNECT);   //temporary re-introduction of configrable gain for testing

  /*RAMP HERE*/
  equilibrium_delay(swvSensChan, swvStartVolt, swvZeroVolt , tEquilibrium);
  sqv_ramp_parameters(swvSensChan, swvZeroVolt, swvStartVolt, swvEndVolt, RGAIN, swvAmp, swvStep, swvFreq);
  /*END RAMP*/

  turn_off_afe_power_things_down();
  printf("[END:SWV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

void sqv_ramp_parameters(uint8_t chan, uint16_t zeroV, uint16_t startV, uint16_t endV, uint32_t RGAIN, uint16_t amplitude, uint16_t step, uint16_t freq){

  uint16_t SETTLING_DELAY = 5;
  uint16_t cBias, cZero;
  uint16_t DACSHIFT = 0;
  
  uint16_t cStart = (startV-200)/0.54-DACSHIFT;
  uint16_t cEnd =(endV-200)/0.54-DACSHIFT;
  int RTIA = LPRTIA_VAL_LOOKUP(RGAIN);
  
  uint16_t delayVal = (50000/freq/3);        //delay required to maintain specified squarewave frequency

  uint16_t amp = (amplitude)/0.54;

  cZero = (zeroV-200)/34.38;
  cBias = cStart;

  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);

  uint16_t inc = 2*step;
  
  //Ramp function goes from negative to positive voltage
  if(startV < endV){
    for (cBias = cStart; cBias < cEnd; cBias = cBias + inc){
      
      //Squarewave low
      LPDacWr(chan, cZero, cBias);
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the starting voltage and current
      szADCSamples[sampleCount]=burstSample(1,chan);
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);
      sampleCount++;
      
      //Squarewave high
      LPDacWr(chan, cZero, cBias+2*amp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);
      sampleCount++;     
    }
  }
  //Ramp function goes from positive to negative voltage
  else{
    for (cBias = cStart; cBias > cEnd; cBias = cBias - inc){
      
      //Squarewave low
      LPDacWr(chan, cZero, cBias);
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the starting voltage and current
      szADCSamples[sampleCount]=burstSample(1,chan);
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);
      sampleCount++;
      
      //Squarewave high
      LPDacWr(chan, cZero, cBias-2*amp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);
      sampleCount++;     
    }
  }
  
  //Open the RE/CE connections to put the sensor in "open circuit" state
  pADI_AFE->LPTIASW0=0x0;
  pADI_AFE->LPDACSW0=0x20;
  
  printSWVResults(cZero, cStart, cEnd, sampleCount, RTIA);
}

void printSWVResults(float cZero, float cStart, float cEnd, int sampleCount, int RTIA){
  float zeroVoltage = 200+(cZero*34.38);
  uint16_t* szADCSamples = return_adc_buffer();
  float v, tc;
  printf("[RANGE:%f,%f]", cStart*0.54+200-zeroVoltage, cEnd*0.54+200-zeroVoltage);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  for(uint32_t i = 0; i < sampleCount; i+=3){
    v = (zeroVoltage/1000) - adc_to_volts(szADCSamples[i]);
    tc = 0-(adc_to_current(szADCSamples[i+1],RTIA)-adc_to_current(szADCSamples[i+2],RTIA));
    printf("%f,%f\n", v, 1.13*tc);
  }
  printf("]");
}
/*************END SQUARE WAVE VOLTAMMETRY**************************/

/*equilibrium delay is in seconds*/
void equilibrium_delay(uint8_t chan, uint16_t start, uint16_t zero, uint16_t time){
  uint16_t DACSHIFT = 0;
  LPDacWr(chan, (zero-200)/34.38, (start-200)/0.54-DACSHIFT);    //Write the DAC to its starting voltage during the quilibrium period
  delay_10us(100000*time);
}