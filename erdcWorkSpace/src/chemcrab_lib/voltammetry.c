#include "voltammetry.h"

/***************CYCLIC VOLTAMMETRY**************/
void runCV(void){
  setAdcMode(0);
  
  uint16_t cvSensChan = getSensorChannel();
  
  //printf("Starting voltage between 0000mV - 9999mV : ");
  printf("[:SVI]");
  int cvStartVolt = getVoltageInput();
  
  //printf("Vertex voltage between 0000mV - 9999mV : ");
  printf("[:VVI]");
  int cvVertexVolt = getVoltageInput();
  
  //printf("Ending voltage between 0000mV - 9999mV : ");
  printf("[:EVI]");
  int cvEndVolt = getVoltageInput();
  
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
  
  printf("[START:CV]");
  
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
  equilibrium_delay_CV(cvSensChan, cvStartVolt, cvVertexVolt, cvEndVolt, tEquilibrium);
  cv_ramp_parameters(cvSensChan, cvStartVolt, cvVertexVolt, cvEndVolt, RGAIN, sweepRate);
  /*END RAMP*/

  turn_off_afe_power_things_down();
  printf("[END:CV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

//Picks an ideal VZERO level based on required test range for cyclic voltammetry 
//Added this to reduce likelihood of control-amp saturation at 0v or 3.3v
//relative_voltages = [vStart, vVert, vEnd]
//absolute_voltages = [vZero_abs, vStart_abs, vVert_abs, vEnd_abs]
void set_CV_voltages(int relative_voltages[3], uint16_t absolute_voltages[4]){
  uint16_t vMax = 2300; //maximum DAC output voltage
  //uint16_t vMin = 200;  //minimum DAC output voltage(accordingg to hardware reference but in practice higher than this???)
  
  //identify the minimum value in relative_voltages
  int minVal = relative_voltages[0];
  for(int i=1 ; i<3 ; ++i){
    if(relative_voltages[i] < minVal){
      minVal = relative_voltages[i];
    }
  }
  
  //assign vZero based on the minVal
  absolute_voltages[0] = vMax - abs(minVal);    //set vZero_abs
  
  //assign absolute voltages to each remaining test parameter based on the calculated vZero level
  absolute_voltages[1] = absolute_voltages[0] - relative_voltages[0];   //set vStart_abs
  absolute_voltages[2] = absolute_voltages[0] - relative_voltages[1];   //set vVert_abs
  absolute_voltages[3] = absolute_voltages[0] - relative_voltages[2];   //set vEnd_abs
  
}

void cv_ramp_parameters(uint16_t chan, int startV, int vertexV, int endV, uint32_t RGAIN, uint16_t sweepRate){   
  
  //Use set_CV_voltages to get absolute voltages from relative voltage inputs
  uint16_t abs_voltages[4] = {0, 0, 0, 0};
  int rel_voltages[3] = {startV, vertexV, endV};
  set_CV_voltages(rel_voltages, abs_voltages);
  
  //absolute_voltages = [vZero_abs, vStart_abs, vVert_abs, vEnd_abs]
  uint16_t vZero = abs_voltages[0];
  uint16_t vStart = abs_voltages[1];
  uint16_t vVertex = abs_voltages[2];
  uint16_t vEnd = abs_voltages[3];
  
  //Setup timing parameters
  uint16_t SETTLING_DELAY = 5;
  GptCfgVoltammetry(sweepRate); //configure general-purpose digital timer to use chosen sweeprate
  
  //Convert test voltages to DAC inputs
  uint16_t cStart = mV_to_DAC(vStart,12);
  uint16_t cVertex = mV_to_DAC(vVertex,12);
  uint16_t cEnd = mV_to_DAC(vEnd,12);
  uint16_t cZero = mV_to_DAC(vZero,6);
  uint16_t cBias = cStart;
  uint16_t inc = 1;     //DAC step increment.  Step size is inc*0.537mV
  
  //Initialize ADC parameters
  int RTIA = LPRTIA_VAL_LOOKUP(RGAIN);
  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  //"upwards" sweep
  if(vStart < vVertex){
    for (cBias = cStart; cBias < cVertex; cBias = cBias + inc){
      LPDacWr(chan, cZero, cBias);        // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);         // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,chan);  //measure V_RE with 32x oversampling
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
        sampleCount++;
      }
    }
    for (cBias = cVertex; cBias > cEnd; cBias = cBias - inc){
      LPDacWr(chan, cZero, cBias);         // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,chan);  //measure V_RE with 32x oversampling
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
        sampleCount++;
      }
    }
  }
  
  //"downwards" sweep
  else{
    for (cBias = cStart; cBias > cVertex; cBias = cBias - inc){
      LPDacWr(chan, cZero, cBias);        // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);         // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,chan);  //measure V_RE with 32x oversampling
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
        sampleCount++;
      }
    }
    
    for (cBias = cVertex; cBias < cEnd; cBias = cBias + inc){
      LPDacWr(chan, cZero, cBias);        // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);         // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,chan);  //measure V_RE with 32x oversampling
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
        sampleCount++;
      }
    }
  }

  //put the sensor in "open circuit" state
  turn_off_afe_power_things_down();
  printCVResults(cZero,cStart,cVertex,cEnd,sampleCount,RTIA);
}

void printCVResults(float cZero, float cStart, float cVertex, float cEnd, int sampleCount, int RTIA){
  float zeroVoltage = 200+(cZero*34.38);
  printf("[RANGE:%f,%f,%f]", (cStart*0.537+200-zeroVoltage)*-1, (cVertex*0.54+200-zeroVoltage)*-1, (cEnd*0.537+200-zeroVoltage)*-1);
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

/*equilibrium delay is in seconds*/
void equilibrium_delay_CV(uint16_t chan, int startV, int vertexV, int endV, uint16_t time){
  
  //Use set_CV_voltages to get absolute voltages from relative voltage inputs
  uint16_t abs_voltages[4] = {0, 0, 0, 0};
  int rel_voltages[3] = {startV, vertexV, endV};
  set_CV_voltages(rel_voltages, abs_voltages);
  //absolute_voltages = [vZero_abs, vStart_abs, vVert_abs, vEnd_abs]
  uint16_t vZero = abs_voltages[0];
  uint16_t vStart = abs_voltages[1];
  
  LPDacWr(chan, mV_to_DAC(vZero,6) , mV_to_DAC(vStart,12));    //Write the DAC to its starting voltage during the quilibrium period
  delay_10us(100000*time);
}
/****************END CYCLIC VOLTAMMETRY**********************/

/****************SQUARE WAVE VOLTAMMETRY***************************/

void runSWV(void){
  setAdcMode(0);
  
  uint8_t swvSensChan = getSensorChannel();
  
  //printf("Starting voltage between 0000mV - 9999mV : ");
  printf("[:SVI]");
  int swvStartVolt = getVoltageInput();
  
  //printf("Ending voltage between 0000mV - 9999mV : ");
  printf("[:EVI]");
  int swvEndVolt = getVoltageInput();
  
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
  
  printf("[START:SWV]");
  
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
  equilibrium_delay_SWV(swvSensChan, swvStartVolt, swvEndVolt, swvAmp, tEquilibrium);
  swv_ramp_parameters(swvSensChan, swvStartVolt, swvEndVolt, RGAIN, swvAmp, swvStep, swvFreq);
  /*END RAMP*/

  turn_off_afe_power_things_down();
  printf("[END:SWV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

//Picks an ideal VZERO level based on required test range for square wave voltammetry
//Added this to reduce likelihood of control-amp saturation at 0v or 3.3v
//relative_voltages = [vStart, vEnd, vAmp]
//absolute_voltages = [vZero_abs, vStart_abs, vEnd_abs]
void set_SWV_voltages(int relative_voltages[3], uint16_t absolute_voltages[3]){
  uint16_t vMax = 2300; //maximum DAC output voltage
  //uint16_t vMin = 200;  //minimum DAC output voltage(accordingg to hardware reference but in practice higher than this???)
  
  //identify the minimum value between vStart and vEnd
  int minVal = relative_voltages[0];
  if(relative_voltages[1] < minVal){
    minVal = relative_voltages[1];
  }
  
  //assign vZero based on the minVal and square wave amplitude
  absolute_voltages[0] = vMax - (abs(minVal) + (2*relative_voltages[2]));
  
  if(relative_voltages[0] < 0 && relative_voltages[1] < 0){      //if vStart and vEnd are both less than zero shift downwards further
    absolute_voltages[0] = 1000;
  }
  
  //assign absolute voltages to each remaining test parameter based on the calculated vZero level
  absolute_voltages[1] = absolute_voltages[0] - relative_voltages[0];   //set vStart_abs
  absolute_voltages[2] = absolute_voltages[0] - relative_voltages[1];   //set vEnd_abs
}

void swv_ramp_parameters(uint16_t chan, int startV, int endV, uint32_t RGAIN, uint16_t amplitude, uint16_t step, uint16_t freq){
  
  //Use set_SWV_voltages to get absolute voltages from relative voltage inputs
  uint16_t abs_voltages[3] = {0, 0, 0};
  int rel_voltages[3] = {startV, endV, amplitude};
  set_SWV_voltages(rel_voltages, abs_voltages);
  
  //absolute_voltages = [vZero_abs, vStart_abs, vEnd_abs]
  uint16_t vZero = abs_voltages[0];
  uint16_t vStart = abs_voltages[1];
  uint16_t vEnd = abs_voltages[2];
  
  //Convert test voltages to DAC inputs
  uint16_t cStart = mV_to_DAC(vStart,12);
  uint16_t cEnd = mV_to_DAC(vEnd,12);
  uint16_t cZero = mV_to_DAC(vZero,6);
  uint16_t cBias = cStart;
  uint16_t cAmp = (int)((amplitude)/0.537);
  uint16_t inc = 2*step;        //DAC bit is 0.537mV, x2 to make inc ~1mV

  //Square wave timing parameters
  uint16_t SETTLING_DELAY = 5;
  uint16_t delayVal = (50000/freq/3);        //delay required to maintain specified squarewave frequency

  //Initialize ADC parameters
  int RTIA = LPRTIA_VAL_LOOKUP(RGAIN);
  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  //ramp function is "upwards"
  if(vStart < vEnd){
    for (cBias = cStart; cBias < cEnd; cBias = cBias + inc){
      
      //Squarewave low
      LPDacWr(chan, cZero, cBias);
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the starting voltage and current
      szADCSamples[sampleCount]=burstSample(1,chan);    //measure V_RE with 32x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
      sampleCount++;
      
      //Squarewave high
      LPDacWr(chan, cZero, cBias+2*cAmp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
      sampleCount++;     
    }
  }
  //ramp function is "downwards"
  else{
    for (cBias = cStart; cBias > cEnd; cBias = cBias - inc){
      
      //Squarewave low
      LPDacWr(chan, cZero, cBias);
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the starting voltage and current
      szADCSamples[sampleCount]=burstSample(1,chan);    //measure V_RE with 32x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
      sampleCount++;
      
      //Squarewave high
      LPDacWr(chan, cZero, cBias-2*cAmp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
      sampleCount++;     
    }
  }
  
  //put the sensor in "open circuit" state
  turn_off_afe_power_things_down();
  
  printSWVResults(cZero, cStart, cEnd, sampleCount, RTIA);
}

//Added moving average filter for clean data until better filtering is implemented
void printSWVResults(float cZero, float cStart, float cEnd, int sampleCount, int RTIA){
  float zeroVoltage = 200+(cZero*34.38);
  uint16_t* szADCSamples = return_adc_buffer();
  float v, tc;
  printf("[RANGE:%f,%f]", (cStart*0.537+200-zeroVoltage)*-1, (cEnd*0.537+200-zeroVoltage)*-1);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  
  float arr[20] = {0};        //declare arrays to hold previous current measurements
  float newarr[20] = {0};
  uint8_t use_mov_avg = 1;
  
  //Initialize arr[] to the first N values in szADCSamples instead of zero
  for(uint16_t i = 0; i < 60; i+=3){
    arr[(int)(i/3)] = adc_to_current(szADCSamples[i+2],RTIA) - adc_to_current(szADCSamples[i+1],RTIA);
  }
  
  for(uint16_t i = 0; i < sampleCount; i+=3){
    v = (zeroVoltage/1000) - adc_to_volts(szADCSamples[i]);
    tc = adc_to_current(szADCSamples[i+2],RTIA) - adc_to_current(szADCSamples[i+1],RTIA);
    
    //Moving average filter for voltammetry data
    if(use_mov_avg){
      tc = voltammetryMovAvg(arr, newarr, tc, 20);
    }
    
    printf("%f,%f\n", v, tc);
  }
  printf("]");
}

/*equilibrium delay is in seconds*/
void equilibrium_delay_SWV(uint16_t chan, int startV, int endV, uint16_t amp, uint16_t time){
  
  //Use set_CV_voltages to get absolute voltages from relative voltage inputs
  uint16_t abs_voltages[3] = {0, 0, 0};
  int rel_voltages[3] = {startV, endV, amp};
  set_SWV_voltages(rel_voltages, abs_voltages);
  //absolute_voltages = [vZero_abs, vStart_abs, vEnd_abs]
  uint16_t vZero = abs_voltages[0];
  uint16_t vStart = abs_voltages[1];

  LPDacWr(chan, mV_to_DAC(vZero,6), mV_to_DAC(vStart,12));    //Write the DAC to its starting voltage during the quilibrium period
  delay_10us(100000*time);
}

/*************END SQUARE WAVE VOLTAMMETRY**************************/

/****************CYCLIC SQUARE WAVE VOLTAMMETRY***************************/
void runCSWV(void){
  setAdcMode(0);
  
  uint8_t cswvSensChan = getSensorChannel();
  
  //printf("Starting voltage between 0000mV - 9999mV : ");
  printf("[:SVI]");
  int cswvStartVolt = getVoltageInput();
  
  //printf("Vertex voltage between 0000mV - 9999mV : ");
  printf("[:VVI]");
  int cswvVertexVolt = getVoltageInput();
  
  //printf("Ending voltage between 0000mV - 9999mV : ");
  printf("[:EVI]");
  int cswvEndVolt = getVoltageInput();
  
  printf("[:AMPI]");
  //printf("Squarewave Pk-Pk amplitude (000mV - 999mV) : ");
  uint16_t cswvAmp = getParameter(3);
  
  printf("[:STEPI]");
  //printf("Voltage step size between squarewave cycles, in mV");
  uint16_t cswvStep = getParameter(3);
  
  printf("[:FREQI]");
  //printf("Squarewave frequency (00000Hz - 99999Hz) : ");
  uint16_t cswvFreq = getParameter(5);
  
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
  
  printf("[START:CSWV]");
  
  /*cswv ramp setup*/
  AfePwrCfg(AFE_ACTIVE);  //set AFE power mode to active

  LPDacPwrCtrl(cswvSensChan,PWR_UP);
  LPDacCfg(cswvSensChan,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);

  /*LPTIA REQUIRED TO HAVE DAC OUTPUT*/
  /*power up PA,TIA,no boost, full power*/
  AfeLpTiaPwrDown(cswvSensChan,0);
  AfeLpTiaAdvanced(cswvSensChan,BANDWIDTH_NORMAL,CURRENT_NOR);
  AfeLpTiaCon(cswvSensChan,LPTIA_RLOAD_0,LPTIA_RGAIN_96K,LPTIA_RFILTER_1M); 
  delay_10us(1000);
  
  //Temporary fix to test LPTIA functionality.  Sets up AFE according to example configuration
  AFE_SETUP_LPTIA_LPDAC(cswvSensChan);
  AfeLpTiaCon(cswvSensChan, LPTIA_RLOAD_10, RGAIN, LPTIA_RFILTER_DISCONNECT);   //temporary re-introduction of configrable gain for testing

  /*RAMP HERE*/
  equilibrium_delay_CSWV(cswvSensChan, cswvStartVolt, cswvVertexVolt, cswvEndVolt, cswvAmp, tEquilibrium);
  cswv_ramp_parameters(cswvSensChan, cswvStartVolt, cswvVertexVolt, cswvEndVolt, RGAIN, cswvAmp, cswvStep, cswvFreq);
  /*END RAMP*/

  turn_off_afe_power_things_down();
  printf("[END:CSWV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

//Picks an ideal VZERO level based on required test range for cyclic square wave voltammetry
//relative_voltages = [vStart, vVertex, vEnd, vAmp]
//absolute_voltages = [vZero_abs, vStart_abs, vVertex_abs, vEnd_abs]
void set_CSWV_voltages(int relative_voltages[4], uint16_t absolute_voltages[4]){
  uint16_t vMax = 2300; //maximum DAC output voltage
  //uint16_t vMin = 200;  //minimum DAC output voltage(according to hardware reference but in reality higher than this???)
  
  //identify the minimum value in relative_voltages
  int minVal = relative_voltages[0];
  for(int i=1 ; i<3 ; ++i){
    if(relative_voltages[i] < minVal){
      minVal = relative_voltages[i];
    }
  }
  //assign vZero based on the minVal and square wave amplitude
  absolute_voltages[0] = vMax - (abs(minVal) + (2*relative_voltages[3]));
  
  if(relative_voltages[0] < 0 && relative_voltages[1] < 0){      //if vStart and vEnd are both less than zero shift downwards further
    absolute_voltages[0] = 1000;
  }
  
  //assign absolute voltages to each remaining test parameter based on the calculated vZero level
  absolute_voltages[1] = absolute_voltages[0] - relative_voltages[0];   //set vStart_abs
  absolute_voltages[2] = absolute_voltages[0] - relative_voltages[1];   //set vVertex_abs
  absolute_voltages[3] = absolute_voltages[0] - relative_voltages[2];   //set vEnd_abs
}

void cswv_ramp_parameters(uint16_t chan, int startV, int vertexV, int endV, uint32_t RGAIN, uint16_t amplitude, uint16_t step, uint16_t freq){
  
  //Use set_CSWV_voltages to get absolute voltages from relative voltage inputs
  uint16_t abs_voltages[4] = {0, 0, 0, 0};
  int rel_voltages[4] = {startV, vertexV, endV, amplitude};
  set_CSWV_voltages(rel_voltages, abs_voltages);
  
  //absolute_voltages = [vZero_abs, vStart_abs, vVertex_abs, vEnd_abs]
  uint16_t vZero = abs_voltages[0];
  uint16_t vStart = abs_voltages[1];
  uint16_t vVertex = abs_voltages[2];
  uint16_t vEnd = abs_voltages[3];
  
  //Convert test voltages to DAC inputs
  uint16_t cStart = mV_to_DAC(vStart,12);
  uint16_t cVertex = mV_to_DAC(vVertex,12);
  uint16_t cEnd = mV_to_DAC(vEnd,12);
  uint16_t cZero = mV_to_DAC(vZero,6);
  uint16_t cBias = cStart;
  uint16_t cAmp = (int)((amplitude)/0.537);
  uint16_t inc = 2*step;        //DAC bit is 0.537mV, x2 to make inc ~1mV

  //Square wave timing parameters
  uint16_t SETTLING_DELAY = 5;
  uint16_t delayVal = (50000/freq/3);        //delay required to maintain specified squarewave frequency

  //Initialize ADC parameters
  int RTIA = LPRTIA_VAL_LOOKUP(RGAIN);
  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  //ramp function is "upwards"
  if(vStart < vVertex){
    for (cBias = cStart; cBias < cVertex; cBias = cBias + inc){
      //Squarewave low
      LPDacWr(chan, cZero, cBias);
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the starting voltage and current
      szADCSamples[sampleCount]=burstSample(1,chan);    //measure V_RE with 32x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
      sampleCount++;
      
      //Squarewave high
      LPDacWr(chan, cZero, cBias+2*cAmp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
      sampleCount++;     
    }
    for (cBias = cVertex; cBias > cEnd; cBias = cBias - inc){
      //Squarewave high
      LPDacWr(chan, cZero, cBias);
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the starting voltage and current
      szADCSamples[sampleCount]=burstSample(1,chan);    //measure V_RE with 32x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
      sampleCount++;
      
      //Squarewave low
      LPDacWr(chan, cZero, cBias-2*cAmp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
      sampleCount++;     
    }
  }
  
  //ramp function is "downwards"
  else{
    for (cBias = cStart; cBias > cVertex; cBias = cBias - inc){
      
      //Squarewave high
      LPDacWr(chan, cZero, cBias);
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the starting voltage and current
      szADCSamples[sampleCount]=burstSample(1,chan);    //measure V_RE with 32x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
      sampleCount++;
      
      //Squarewave low
      LPDacWr(chan, cZero, cBias-2*cAmp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
      sampleCount++;     
    }
    for (cBias = cVertex; cBias < cEnd; cBias = cBias + inc){
      //Squarewave low
      LPDacWr(chan, cZero, cBias);
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the starting voltage and current
      szADCSamples[sampleCount]=burstSample(1,chan);    //measure V_RE with 32x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
      sampleCount++;
      
      //Squarewave high
      LPDacWr(chan, cZero, cBias+2*cAmp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
      sampleCount++;     
    }
  }
  
  //put the sensor in "open circuit" state
  turn_off_afe_power_things_down();
  printCSWVResults(cZero, cStart, cVertex, cEnd, sampleCount, RTIA);
}

void printCSWVResults(float cZero, float cStart, float cVertex, float cEnd, int sampleCount, int RTIA){
  float zeroVoltage = 200+(cZero*34.38);
  uint16_t* szADCSamples = return_adc_buffer();
  float v, tc;
  printf("[RANGE:%f,%f,%f]", (cStart*0.537+200-zeroVoltage)*-1, (cVertex*0.537+200-zeroVoltage)*-1, (cEnd*0.537+200-zeroVoltage)*-1);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  for(uint32_t i = 0; i < sampleCount; i+=3){
    v = (zeroVoltage/1000) - adc_to_volts(szADCSamples[i]);
    tc = 0-(adc_to_current(szADCSamples[i+1],RTIA)-adc_to_current(szADCSamples[i+2],RTIA));
    printf("%f,%f\n", v, tc);
  }
  printf("]");
}
void equilibrium_delay_CSWV(uint16_t chan, int startV, int vertexV, int endV, uint16_t amp, uint16_t time){
  
  //Use set_CSWV_voltages to get absolute voltages from relative voltage inputs
  uint16_t abs_voltages[4] = {0, 0, 0, 0};
  int rel_voltages[4] = {startV, vertexV, endV, amp};
  set_CSWV_voltages(rel_voltages, abs_voltages);
  //absolute_voltages = [vZero_abs, vStart_abs, vVertex_abs, vEnd_abs]
  uint16_t vZero = abs_voltages[0];
  uint16_t vStart = abs_voltages[1];

  LPDacWr(chan, mV_to_DAC(vZero,6), mV_to_DAC(vStart,12));    //Write the DAC to its starting voltage during the quilibrium period
  delay_10us(100000*time);
}
/****************END CYCLIC SQUARE WAVE VOLTAMMETRY***************************/

/****************CHRONOAMPEROMETRY***************************/

void runCA(void){
  setAdcMode(0);
  
  uint16_t caChan = getSensorChannel();
  
  //printf("Starting voltage between 0000mV - 9999mV : ");
  printf("[:STEPVI]");
  int stepVoltage = getVoltageInput();
  
  //printf("Step duration between 0000ms - 9999ms : ");
  printf("[:SLI]");
  uint16_t stepLength = getParameter(4);
  
  //printf("Step delay between 0000ms - 9999ms : ");
  printf("[:SDI]");
  uint16_t stepDelay = getParameter(4);
  
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
  
  printf("[START:CA]");
  
  /*cv ramp setup*/
  AfePwrCfg(AFE_ACTIVE);  //set AFE power mode to active

  LPDacPwrCtrl(caChan,PWR_UP);
  LPDacCfg(caChan,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);

  /*LPTIA REQUIRED TO HAVE DAC OUTPUT*/
  /*power up PA,TIA,no boost, full power*/
  AfeLpTiaPwrDown(caChan,0);
  AfeLpTiaAdvanced(caChan,BANDWIDTH_NORMAL,CURRENT_NOR);
  AfeLpTiaCon(caChan,LPTIA_RLOAD_0,LPTIA_RGAIN_96K,LPTIA_RFILTER_1M); 
  delay_10us(1000);
  
  //Temporary fix to test LPTIA functionality.  Sets up AFE according to example configuration
  AFE_SETUP_LPTIA_LPDAC(caChan);
  AfeLpTiaCon(caChan, LPTIA_RLOAD_100, RGAIN, LPTIA_RFILTER_DISCONNECT);
  
  ca_step_parameters(caChan, stepVoltage, stepLength, stepDelay, RGAIN);
  
  turn_off_afe_power_things_down();
  printf("[END:CA]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

void set_ca_voltages(int vStep, uint16_t absolute_voltages[2]){
  uint16_t vMax = 2300; //maximum DAC output voltage
  //Set vZero
  if(vStep > 0){
    absolute_voltages[0] = vMax;
  }
  else{
    absolute_voltages[0] = vMax - abs(vStep) - 500;     //-500 to keep the opamp voltage further from 3.3v
  }
  
  absolute_voltages[1] = absolute_voltages[0] - vStep;
}

void ca_step_parameters(uint16_t chan, int stepV, uint16_t length, uint16_t delay, uint32_t RGAIN){
  
  //Convert relative voltages from inputs to absolute voltages for differential DAC 
  uint16_t absolute_voltages[2] = {0, 0};
  set_ca_voltages(stepV, absolute_voltages);
  uint16_t vZero = absolute_voltages[0];
  uint16_t vStep = absolute_voltages[1];

  //Set p CA voltage parameters for DAC input
  uint16_t cZero = mV_to_DAC(vZero,6);
  uint16_t cStep = mV_to_DAC(vStep, 12);
  
  //CA timing parameters
  uint16_t SETTLING_DELAY = 5;
  uint16_t samples = 500;
  float sample_interval_ms = (1000*length)/samples;
  
  //Initialize ADC parameters
  int RTIA = LPRTIA_VAL_LOOKUP(RGAIN);
  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  //Set sensor voltage to zero and maintain for the delay time
  LPDacWr(chan, cZero, mV_to_DAC(vZero,12));
  delay_10us(100000*delay);
  
  //Set the sensor to the step voltage and record N=samples while holding for the step length
  LPDacWr(chan, cZero, cStep);
  delay_10us(SETTLING_DELAY);
  for(int i=0 ; i<samples ; ++i){
    //Measure the voltage and current
    szADCSamples[sampleCount]=burstSample(1,chan);      //measure V_RE with 32x oversampling
    sampleCount++;
    szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
    sampleCount++;
    delay_10us((int)length/(3*samples*(10E-6)));   /* !!!!!This timing is not accurate, need to improve this!!!!  */
  }
  
  //Set the sensor back to 0V and record N=samples while holding for the step length
  LPDacWr(chan, cZero, mV_to_DAC(vZero,12));
  delay_10us(SETTLING_DELAY);
  for(int i=0 ; i<samples ; ++i){
    //Measure the voltage and current
    szADCSamples[sampleCount]=burstSample(1,chan);      //measure V_RE with 32x oversampling
    sampleCount++;
    szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 32x oversampling
    sampleCount++;
    delay_10us((int)length/(3*samples*(10E-6)));
  }
  printCAResults(cZero, cStep, length, RTIA, sampleCount, sample_interval_ms);
}

void printCAResults(float cZero, float cStep, int length, int RTIA, int sampleCount, float timeStep){
  float zeroVoltage = 200+(cZero*34.38);
  uint16_t* szADCSamples = return_adc_buffer();
  float tc;
  printf("[STEP:%f]", (cStep*0.537+200-zeroVoltage)*-1);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  int index = 0;
  for(uint32_t i = 0; i < sampleCount; i+=2){
    //v = (zeroVoltage/1000) - adc_to_volts(szADCSamples[i]);   //Later, may want to plot measured voltages as well as current vs. time
    tc = adc_to_current(szADCSamples[i+1],RTIA);
    printf("%f,%f\n", index*timeStep, tc);       //chronoamperometry plotted vs.time instead of voltage
    ++index;
  }
  printf("]");
}

/****************END CHRONOAMPEROMETRY***************************/