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
  uint16_t vMin = 200;  //minimum DAC output voltage(accordingg to hardware reference but in practice higher than this???)
  
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
  
  uint16_t SETTLING_DELAY = 5;
  uint16_t DACSHIFT = 40;
  uint16_t cBias, cZero;
  GptCfgVoltammetry(sweepRate); //configure general-purpose digital timer to use chosen sweeprate
  uint16_t cStart = ((vStart-200)/0.54)-DACSHIFT;
  uint16_t cVertex = ((vVertex-200)/0.54)-DACSHIFT;
  uint16_t cEnd =((vEnd-200)/0.54)-DACSHIFT;
  int RTIA = LPRTIA_VAL_LOOKUP(RGAIN);
  
  cZero = (vZero-200)/34.38;
  cBias = cStart;
  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  //DAC step increment.  Step size is roughly inc*0.54mV
  uint16_t inc = 1;
  
  //Sweep starts at a negative voltage
  if(vStart < vVertex){
    for (cBias = cStart; cBias < cVertex; cBias = cBias + inc){
      LPDacWr(chan, cZero, cBias);        // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);         // allow LPDAC to settle
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
  printf("[RANGE:%f,%f,%f]", (cStart*0.54+200-zeroVoltage)*-1, (cVertex*0.54+200-zeroVoltage)*-1, (cEnd*0.54+200-zeroVoltage)*-1);
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
  uint16_t vVertex = abs_voltages[2];
  uint16_t vEnd = abs_voltages[3];
  
  uint16_t DACSHIFT = 40;
  LPDacWr(chan, (vZero-200)/34.38, (vStart-200)/0.54-DACSHIFT);    //Write the DAC to its starting voltage during the quilibrium period
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
  sqv_ramp_parameters(swvSensChan, swvStartVolt, swvEndVolt, RGAIN, swvAmp, swvStep, swvFreq);
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
  uint16_t vMin = 200;  //minimum DAC output voltage(accordingg to hardware reference but in practice higher than this???)
  
  //identify the minimum value between vStart and vEnd
  int minVal = relative_voltages[0];
  if(relative_voltages[1] < minVal){
    minVal = relative_voltages[1];
  }
  
  //assign vZero based on the minVal and square wave amplitude
  if(relative_voltages[0] < relative_voltages[1]){
    absolute_voltages[0] = vMax - (abs(minVal));    //set vZero_abs
  }
  else{
    absolute_voltages[0] = vMax - (abs(minVal) + relative_voltages[2]);    //set vZero_abs with buffer for square wave amplitude
  }
  
  if(relative_voltages[0] < 0 && relative_voltages[1] < 0){      //if vStart and vEnd are both less than zero shift downwards further
    absolute_voltages[0] = 1000;
  }
  
  //assign absolute voltages to each remaining test parameter based on the calculated vZero level
  absolute_voltages[1] = absolute_voltages[0] - relative_voltages[0];   //set vStart_abs
  absolute_voltages[2] = absolute_voltages[0] - relative_voltages[1];   //set vEnd_abs
}

void sqv_ramp_parameters(uint16_t chan, int startV, int endV, uint32_t RGAIN, uint16_t amplitude, uint16_t step, uint16_t freq){
  
  //Use set_SWV_voltages to get absolute voltages from relative voltage inputs
  uint16_t abs_voltages[3] = {0, 0, 0};
  int rel_voltages[3] = {startV, endV, amplitude};
  set_SWV_voltages(rel_voltages, abs_voltages);
  
  //absolute_voltages = [vZero_abs, vStart_abs, vEnd_abs]
  uint16_t vZero = abs_voltages[0];
  uint16_t vStart = abs_voltages[1];
  uint16_t vEnd = abs_voltages[2];

  uint16_t SETTLING_DELAY = 5;
  uint16_t cBias, cZero;
  uint16_t DACSHIFT = 40;
  
  uint16_t cStart = (vStart-200)/0.54-DACSHIFT;
  uint16_t cEnd =(vEnd-200)/0.54-DACSHIFT;
  int RTIA = LPRTIA_VAL_LOOKUP(RGAIN);
  
  uint16_t delayVal = (50000/freq/3);        //delay required to maintain specified squarewave frequency

  uint16_t amp = (amplitude)/0.54;
  
  cZero = (vZero-200)/34.38;
  cBias = cStart;

  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);

  uint16_t inc = 2*step;
  
  //Ramp function goes from negative to positive voltage
  if(vStart < vEnd){
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
  printf("[RANGE:%f,%f]", (cStart*0.54+200-zeroVoltage)*-1, (cEnd*0.54+200-zeroVoltage)*-1);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  for(uint32_t i = 0; i < sampleCount; i+=3){
    v = (zeroVoltage/1000) - adc_to_volts(szADCSamples[i]);
    tc = 0-(adc_to_current(szADCSamples[i+1],RTIA)-adc_to_current(szADCSamples[i+2],RTIA));
    printf("%f,%f\n", v, 1.13*tc);
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
  uint16_t vEnd = abs_voltages[2];

  uint16_t DACSHIFT = 40;
  LPDacWr(chan, (vZero-200)/34.38, (vStart-200)/0.54-DACSHIFT);    //Write the DAC to its starting voltage during the quilibrium period
  delay_10us(100000*time);
}

/*************END SQUARE WAVE VOLTAMMETRY**************************/



