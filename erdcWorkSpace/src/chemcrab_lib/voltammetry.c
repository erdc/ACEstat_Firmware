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
  
  //Convert signed voltages from user input to unsigned voltages for DAC channels
  int relativeVoltages[3] = {cvStartVolt,cvVertexVolt,cvEndVolt};
  uint16_t DACVoltages[4] = {0,0,0,0};
  cvSetVoltages(relativeVoltages, DACVoltages, cvSensChan);
  //Apply equilibrium delay and excitation signals
  cvEquilibriumDelay(cvSensChan, DACVoltages, tEquilibrium);
  cvExcitationSignal(cvSensChan, DACVoltages, RGAIN, sweepRate);

  turn_off_afe_power_things_down();
  printf("[END:CV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

//Picks an ideal VZERO level based on required test range for cyclic voltammetry 
//Added this to reduce likelihood of control-amp saturation at 0v or 3.3v
//relative_voltages = [vStart, vVert, vEnd]
//DACVoltages = [vZero_abs, vStart_abs, vVert_abs, vEnd_abs]
void cvSetVoltages(int relative_voltages[3], uint16_t DACVoltages[4], uint8_t channel){
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
  DACVoltages[0] = vMax - abs(minVal);    //set vZero_abs
  
  //assign absolute voltages to each remaining test parameter based on the calculated vZero level
  DACVoltages[1] = DACVoltages[0] - relative_voltages[0];   //set vStart_abs
  DACVoltages[2] = DACVoltages[0] - relative_voltages[1];   //set vVert_abs
  DACVoltages[3] = DACVoltages[0] - relative_voltages[2];   //set vEnd_abs
  
  //Briefly measure the starting potential to determine an offset to adjust DAC outputs
  int vbiasShift = adjustDAC(DACVoltages[0], DACVoltages[1], relative_voltages[0], channel);
  DACVoltages[1] += vbiasShift;
  DACVoltages[2] += vbiasShift;
  DACVoltages[3] += vbiasShift;
}

/*equilibrium delay is in seconds*/
void cvEquilibriumDelay(uint16_t chan, uint16_t DACVoltages[4], uint16_t time){
  //DACVoltages = [vZero_abs, vStart_abs, vVert_abs, vEnd_abs]
  uint16_t vZero = DACVoltages[0];
  uint16_t vStart = DACVoltages[1];
  LPDacWr(chan, mV_to_DAC(vZero,6), mV_to_DAC(vStart,12));
  delay_10us(100000*time);
}

void cvExcitationSignal(uint16_t chan, uint16_t DACVoltages[4], uint32_t RGAIN, uint16_t sweepRate){   

  //DACVoltages = [vZero_abs, vStart_abs, vVert_abs, vEnd_abs]
  uint16_t vZero = DACVoltages[0];
  uint16_t vStart = DACVoltages[1];
  uint16_t vVertex = DACVoltages[2];
  uint16_t vEnd = DACVoltages[3];
  
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
  
  float vZeroMeasured = 0;
  
  //"upwards" sweep
  if(vStart < vVertex){
    for (cBias = cStart; cBias < cVertex; cBias = cBias + inc){
      LPDacWr(chan, cZero, cBias);        // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);         // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,chan);  //measure V_RE with 16x oversampling
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
        sampleCount++;
      }
    }
    for (cBias = cVertex; cBias > cEnd; cBias = cBias - inc){
      LPDacWr(chan, cZero, cBias);         // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,chan);  //measure V_RE with 16x oversampling
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
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
        szADCSamples[sampleCount]=burstSample(1,chan);  //measure V_RE with 16x oversampling
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
        sampleCount++;
      }
    }
    
    for (cBias = cVertex; cBias < cEnd; cBias = cBias + inc){
      LPDacWr(chan, cZero, cBias);        // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);         // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,chan);  //measure V_RE with 16x oversampling
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
        sampleCount++;
      }
    }
  }
  
  //Manually measure the vZero voltage (in mV) to more accurately calculate dfferential sensor potential
  LPDacWr(chan, cZero, cBias);
  delay_10us(SETTLING_DELAY);
  float vZeroMeas = 1000*adc_to_volts(burstSample(2,chan));
  
  //put the sensor in "open circuit" state
  turn_off_afe_power_things_down();
  printCVResults(cZero,cStart,cVertex,cEnd,sampleCount,RTIA,vZeroMeas);
}

void printCVResults(float cZero, float cStart, float cVertex, float cEnd, int sampleCount, int RTIA, float vZeroMeasured){
  //float vZero = DAC_to_mV(cZero,6);
  float vStart = DAC_to_mV(cStart,12);
  float vVertex = DAC_to_mV(cVertex,12);
  float vEnd = DAC_to_mV(cEnd,12);
  
  uint16_t* szADCSamples = return_adc_buffer();
  printf("[RANGE:%.4f,%.4f,%.4f]", vZeroMeasured-vStart, vZeroMeasured-vVertex, vZeroMeasured-vEnd);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  
  float tc, vDiff;
  for(uint32_t i = 0; i < sampleCount; i+=2){
    vDiff = (vZeroMeasured/1000) - adc_to_volts(szADCSamples[i]);
    tc = adc_to_current(szADCSamples[i+1], RTIA);
    printf("%.4f,%.4f"EOL, vDiff,tc);
  }
  printf("]");
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

  //Convert signed voltages from user input to unsigned voltages for DAC channels
  int relativeVoltages[3] = {swvStartVolt,swvEndVolt,swvAmp};
  uint16_t DACVoltages[3] = {0,0,0};
  swvSetVoltages(relativeVoltages, DACVoltages, swvSensChan);
  //Apply equilibrium delay and excitation signals
  swvEquilibriumDelay(swvSensChan, DACVoltages, swvAmp, tEquilibrium);
  swvExcitationSignal(swvSensChan, DACVoltages, RGAIN, swvAmp, swvStep, swvFreq);

  turn_off_afe_power_things_down();
  printf("[END:SWV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

//Picks an ideal VZERO level based on required test range for square wave voltammetry
//Added this to reduce likelihood of control-amp saturation at 0v or 3.3v
//relative_voltages = [vStart, vEnd, vAmp]
//DACVoltages = [vZero_abs, vStart_abs, vEnd_abs]
void swvSetVoltages(int relative_voltages[3], uint16_t DACVoltages[3], uint8_t channel){
  uint16_t vMax = 2300; //maximum DAC output voltage
  //uint16_t vMin = 200;  //minimum DAC output voltage(accordingg to hardware reference but in practice higher than this???)
  
  //identify the minimum value between vStart and vEnd
  int minVal = relative_voltages[0];
  if(relative_voltages[1] < minVal){
    minVal = relative_voltages[1];
  }
  
  //assign vZero based on the minVal and square wave amplitude
  DACVoltages[0] = vMax - (abs(minVal) + (2*relative_voltages[2]));
  
  if(relative_voltages[0] < 0 && relative_voltages[1] < 0){      //if vStart and vEnd are both less than zero shift downwards further
    DACVoltages[0] = 1000;
  }
  
  //assign absolute voltages to each remaining test parameter based on the calculated vZero level
  DACVoltages[1] = DACVoltages[0] - relative_voltages[0];   //set vStart_abs
  DACVoltages[2] = DACVoltages[0] - relative_voltages[1];   //set vEnd_abs
  
  //Briefly measure the starting potential to determine an offset to adjust DAC outputs
  int vbiasShift = adjustDAC(DACVoltages[0], DACVoltages[1], relative_voltages[0], channel);
  DACVoltages[1] += vbiasShift;
  DACVoltages[2] += vbiasShift;
}

/*equilibrium delay is in seconds*/
void swvEquilibriumDelay(uint16_t chan, uint16_t DACVoltages[3], uint16_t amp, uint16_t time){
  //DACVoltages = [vZero_abs, vStart_abs, vEnd_abs]
  uint16_t vZero = DACVoltages[0];
  uint16_t vStart = DACVoltages[1];
  LPDacWr(chan, mV_to_DAC(vZero,6), mV_to_DAC(vStart,12));    //Write the DAC to its starting voltage during the quilibrium period
  delay_10us(100000*time);
}

void swvExcitationSignal(uint16_t chan, uint16_t DACVoltages[3], uint32_t RGAIN, uint16_t amplitude, uint16_t step, uint16_t freq){
  //DACVoltages = [vZero_abs, vStart_abs, vEnd_abs]
  uint16_t vZero = DACVoltages[0];
  uint16_t vStart = DACVoltages[1];
  uint16_t vEnd = DACVoltages[2];
  
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
      szADCSamples[sampleCount]=burstSample(1,chan);    //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      sampleCount++;
      
      //Squarewave high
      LPDacWr(chan, cZero, cBias+2*cAmp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      sampleCount++;     
    }
  }
  //ramp function is "downwards"
  else{
    for (cBias = cStart; cBias > cEnd; cBias = cBias - inc){
      
      //Squarewave high
      LPDacWr(chan, cZero, cBias);
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the starting voltage and current
      szADCSamples[sampleCount]=burstSample(1,chan);    //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      sampleCount++;
      
      //Squarewave low
      LPDacWr(chan, cZero, cBias-2*cAmp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      sampleCount++;     
    }
  }
  
  //Manually measure the vZero voltage (in mV) to more accurately calculate dfferential sensor potential
  LPDacWr(chan, cZero, cBias);
  delay_10us(SETTLING_DELAY);
  float vZeroMeas = 1000*adc_to_volts(burstSample(2,chan));
  
  //put the sensor in "open circuit" state
  turn_off_afe_power_things_down();
  
  printSWVResults(cZero, cStart, cEnd, sampleCount, RTIA, vZeroMeas);
}

//Added moving average filter for clean data until better filtering is implemented
void printSWVResults(float cZero, float cStart, float cEnd, int sampleCount, int RTIA, float vZeroMeasured){
  //float vZero = DAC_to_mV(cZero,6);
  float vZero = vZeroMeasured;
  float vStart = DAC_to_mV(cStart,12);
  float vEnd = DAC_to_mV(cEnd,12);
  
  printf("[RANGE:%.4f,%.4f,%.4f]", vZero-vStart, vZero-vEnd);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  
  uint16_t* szADCSamples = return_adc_buffer();
  float vDiff, tc;
  
  uint8_t use_mov_avg = 0;
  for(uint16_t i = 0; i < sampleCount; i+=3){
    vDiff = (vZero/1000) - adc_to_volts(szADCSamples[i]);
    
    //Moving average filter for voltammetry data
    if(use_mov_avg){
      int filterWidth = 20;
      tc = voltammetryMovAvg(filterWidth, szADCSamples, i+1, sampleCount, RTIA);
    }
    else{
      tc = adc_to_current(szADCSamples[i+2],RTIA) - adc_to_current(szADCSamples[i+1],RTIA);
    }
    
    printf("%.4f,%.4f\n", vDiff, tc);
  }
  printf("]");
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

  //Convert signed voltages from user input to unsigned voltages for DAC channels
  int relativeVoltages[4] = {cswvStartVolt,cswvVertexVolt,cswvEndVolt,cswvAmp};
  uint16_t DACVoltages[4] = {0,0,0,0};
  cswvSetVoltages(relativeVoltages, DACVoltages, cswvSensChan);
  //Apply equilibrium delay and excitation signals
  cswvEquilibriumDelay(cswvSensChan, DACVoltages, cswvAmp, tEquilibrium);
  cswvExcitationSignal(cswvSensChan, DACVoltages, RGAIN, cswvAmp, cswvStep, cswvFreq);
  /*END RAMP*/

  turn_off_afe_power_things_down();
  printf("[END:CSWV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

//Picks an ideal VZERO level based on required test range for cyclic square wave voltammetry
//relative_voltages = [vStart, vVertex, vEnd, vAmp]
//DACVoltages = [vZero_abs, vStart_abs, vVertex_abs, vEnd_abs]
void cswvSetVoltages(int relative_voltages[4], uint16_t DACVoltages[4], uint8_t channel){
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
  DACVoltages[0] = vMax - (abs(minVal) + (2*relative_voltages[3]));
  
  if(relative_voltages[0] < 0 && relative_voltages[1] < 0){      //if vStart and vEnd are both less than zero shift downwards further
    DACVoltages[0] = 1000;
  }
  
  //assign absolute voltages to each remaining test parameter based on the calculated vZero level
  DACVoltages[1] = DACVoltages[0] - relative_voltages[0];   //set vStart_abs
  DACVoltages[2] = DACVoltages[0] - relative_voltages[1];   //set vVertex_abs
  DACVoltages[3] = DACVoltages[0] - relative_voltages[2];   //set vEnd_abs
  
  //Briefly measure the starting potential to determine an offset to adjust DAC outputs
  int vbiasShift = adjustDAC(DACVoltages[0], DACVoltages[1], relative_voltages[0], channel);
  DACVoltages[1] += vbiasShift;
  DACVoltages[2] += vbiasShift;
  DACVoltages[3] += vbiasShift;
}

void cswvEquilibriumDelay(uint16_t chan, uint16_t DACVoltages[4], uint16_t amp, uint16_t time){
  //DACVoltages = [vZero_abs, vStart_abs, vVertex_abs, vEnd_abs]
  uint16_t vZero = DACVoltages[0];
  uint16_t vStart = DACVoltages[1];
  LPDacWr(chan, mV_to_DAC(vZero,6), mV_to_DAC(vStart,12));    //Write the DAC to its starting voltage during the quilibrium period
  delay_10us(100000*time);
}

void cswvExcitationSignal(uint16_t chan, uint16_t DACVoltages[4], uint32_t RGAIN, uint16_t amplitude, uint16_t step, uint16_t freq){
  //DACVoltages = [vZero_abs, vStart_abs, vVertex_abs, vEnd_abs]
  uint16_t vZero = DACVoltages[0];
  uint16_t vStart = DACVoltages[1];
  uint16_t vVertex = DACVoltages[2];
  uint16_t vEnd = DACVoltages[3];
  
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
      szADCSamples[sampleCount]=burstSample(1,chan);    //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      sampleCount++;
      
      //Squarewave high
      LPDacWr(chan, cZero, cBias+2*cAmp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      sampleCount++;     
    }
    for (cBias = cVertex; cBias > cEnd; cBias = cBias - inc){
      //Squarewave high
      LPDacWr(chan, cZero, cBias);
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the starting voltage and current
      szADCSamples[sampleCount]=burstSample(1,chan);    //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      sampleCount++;
      
      //Squarewave low
      LPDacWr(chan, cZero, cBias-2*cAmp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
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
      szADCSamples[sampleCount]=burstSample(1,chan);    //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      sampleCount++;
      
      //Squarewave low
      LPDacWr(chan, cZero, cBias-2*cAmp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      sampleCount++;     
    }
    for (cBias = cVertex; cBias < cEnd; cBias = cBias + inc){
      //Squarewave low
      LPDacWr(chan, cZero, cBias);
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the starting voltage and current
      szADCSamples[sampleCount]=burstSample(1,chan);    //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      sampleCount++;
      
      //Squarewave high
      LPDacWr(chan, cZero, cBias+2*cAmp);               //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      sampleCount++;     
    }
  }
  
  //Manually measure the vZero voltage (in mV) to more accurately calculate dfferential sensor potential
  LPDacWr(chan, cZero, cBias);
  delay_10us(SETTLING_DELAY);
  float vZeroMeas = 1000*adc_to_volts(burstSample(2,chan));
  
  //put the sensor in "open circuit" state
  turn_off_afe_power_things_down();
  printCSWVResults(cZero, cStart, cVertex, cEnd, sampleCount, RTIA, vZeroMeas);
}

void printCSWVResults(float cZero, float cStart, float cVertex, float cEnd, int sampleCount, int RTIA, float vZeroMeasured){
  //float vZero = DAC_to_mV(cZero,6);
  float vZero = vZeroMeasured;
  float vStart = DAC_to_mV(cStart,12);
  float vVertex = DAC_to_mV(cVertex,12);
  float vEnd = DAC_to_mV(cEnd,12);
  
  printf("[RANGE:%.4f,%.4f,%.4f]", vZero-vStart, vZero-vVertex, vZero-vEnd);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  
  uint16_t* szADCSamples = return_adc_buffer();
  float vDiff, tc;
  for(uint32_t i = 0; i < sampleCount; i+=3){
    vDiff = (vZero/1000) - adc_to_volts(szADCSamples[i]);
    tc = 0-(adc_to_current(szADCSamples[i+1],RTIA)-adc_to_current(szADCSamples[i+2],RTIA));
    printf("%.4f,%.4f\n", vDiff, tc);
  }
  printf("]");
}

/****************END CYCLIC SQUARE WAVE VOLTAMMETRY***************************/

/****************CHRONOAMPEROMETRY***************************/

void runCA(void){
  setAdcMode(0);
  
  int diagnosticMode = 0;       //CA used for testing DAC and ADC accuracies
  
  uint16_t caChan = getSensorChannel();
  
  //printf("Starting voltage between 0000mV - 9999mV : ");
  printf("[:STEPVI]");
  int stepVoltage = getVoltageInput();
  
  uint16_t stepLength = 0;
  uint16_t stepDelay = 0;
  
  if(!diagnosticMode){
    //printf("Step duration between 0000ms - 9999ms : ");
    printf("[:SLI]");
    stepLength = getParameter(4);
    
    //printf("Step delay between 0000ms - 9999ms : ");
    printf("[:SDI]");
    stepDelay = getParameter(4);
  }
  
  //printf("TIA Gain Resistor:\n");
  //printf("2 Digits 00-25\n");
  printf("[:RTIAI]");
  uint8_t RTIACHOICE = getParameter(2);
  uint32_t RGAIN = LPRTIA_LOOKUP(RTIACHOICE); //PASS INT VAL RATHER THAN ASCII
  
  printf("[START:CA]");
  
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
  
  //Convert signed voltages from user input to unsigned voltages for DAC channels
  uint16_t DACVoltages[2] = {0,0};
  caSetVoltages(stepVoltage, DACVoltages, caChan);
  
  //Apply excitation signal
  if(!diagnosticMode){
    caExcitationSignal(caChan, DACVoltages, stepLength, stepDelay, RGAIN, 0);
  }
  if(diagnosticMode){
    caExcitationSignal(caChan, DACVoltages, 1, 0, RGAIN, 1);
  }
  
  turn_off_afe_power_things_down();
  printf("[END:CA]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

void caSetVoltages(int vStep, uint16_t DACVoltages[2], uint8_t channel){
  uint16_t vMax = 2300; //maximum DAC output voltage
  //Set vZero
  if(vStep > 0){
    DACVoltages[0] = vMax;
  }
  else{
    DACVoltages[0] = vMax - abs(vStep) - 500;     //-500 to keep the opamp voltage further from 3.3v
  }
  
  DACVoltages[1] = DACVoltages[0] - vStep;
  
  //Briefly measure the starting potential to determine an offset to adjust DAC outputs
  int vbiasShift = adjustDAC(DACVoltages[0], DACVoltages[1], vStep, channel);
  DACVoltages[1] += vbiasShift;
}

void caExcitationSignal(uint16_t chan, uint16_t DACVoltages[2], uint16_t length, uint16_t delay, uint32_t RGAIN, int diag){
  uint16_t vZero = DACVoltages[0];
  uint16_t vStep = DACVoltages[1];

  //Set CA voltage parameters for DAC input
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
  
  if(!diag){
    //Set sensor voltage to zero and maintain for the delay time
    LPDacWr(chan, cZero, mV_to_DAC(vZero,12));
    delay_10us(100000*delay);
    
    //Set the sensor to the step voltage and record N=samples while holding for the step length
    LPDacWr(chan, cZero, cStep);
    delay_10us(SETTLING_DELAY);
    for(int i=0 ; i<samples ; ++i){
      //Measure the voltage and current
      szADCSamples[sampleCount]=burstSample(1,chan);      //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      sampleCount++;
      delay_10us((int)length/(3*samples*(10E-6)));   /* !!!!!This timing is not accurate, need to improve this!!!!  */
    }
    
    //Set the sensor back to 0V and record N=samples while holding for the step length
    LPDacWr(chan, cZero, mV_to_DAC(vZero,12));
    delay_10us(SETTLING_DELAY);
    for(int i=0 ; i<samples ; ++i){
      //Measure the voltage and current
      szADCSamples[sampleCount]=burstSample(1,chan);      //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      sampleCount++;
      delay_10us((int)length/(3*samples*(10E-6)));
    }
    
    //Manually measure the vZero voltage (in mV) to more accurately calculate dfferential sensor potential
    LPDacWr(chan, cZero, cStep);
    delay_10us(SETTLING_DELAY);
    float vZeroMeas = 1000*adc_to_volts(burstSample(2,chan));
    
    turn_off_afe_power_things_down();
    printCAResults(cZero, cStep, length, RTIA, sampleCount, sample_interval_ms, vZeroMeas);
  }
  
  //DAC/ADC Diagnostic mode, sets constant voltage and prints relevant parameters to terminal
  if(diag){
    LPDacWr(chan, cZero, cStep);
    delay_10us(SETTLING_DELAY);
    for(int i=0 ; i<100 ; ++i){
      //Measure the voltage and current
      int vZERO = burstSample(2,chan);
      int vRE = burstSample(1,chan);      //measure V_RE with 16x oversampling
      int iADC = burstSample(0,chan);      //measure current from LPTIA with 16x oversampling
      printf("%.3f , %.3f, %.3f\n", adc_to_volts(vZERO), adc_to_volts(vRE), adc_to_volts(vZERO)-adc_to_volts(vRE));
      delay_10us(1);
    }
  }
}

void printCAResults(float cZero, float cStep, int length, int RTIA, int sampleCount, float timeStep, float vZeroMeasured){
  //float zeroVoltage = 200+(cZero*34.38);
  float zeroVoltage = vZeroMeasured;
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