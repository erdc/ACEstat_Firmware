/**ERDC custom libraries */
#include "voltammetry.h"

/***********************Cyclic Voltammetry(CV) Functions *************************/
void runCV(void){
  setAdcMode(0);
  
  /**Get user inputs from ACEstat app or command-line interface */
  uint16_t cvSensChan = getSensorChannel();     //parser expects 0 or 1
  printf("[:SVI]");                             
  int cvStartVolt = getVoltageInput();          //parser expects -9999 to +9999 [mV]
  printf("[:VVI]");
  int cvVertexVolt = getVoltageInput();         //parser expects -9999 to +9999 [mV]
  printf("[:EVI]");
  int cvEndVolt = getVoltageInput();            //parser expects -9999 to +9999 [mV]
  printf("[:SRI]");
  uint16_t sweepRate = getParameter(3);         //parser expects 000 to 999 [mV/s]
  printf("[:TEI]");
  uint16_t tEquilibrium = getParameter(4);      //parser expects 0000 to 9999 [s]
  printf("[:RTIAI]");
  uint8_t RTIACHOICE = getParameter(2);         //parser expects 00-25
  uint32_t RGAIN = LPRTIA_LOOKUP(RTIACHOICE);   //PASS INT VAL RATHER THAN ASCII
  printf("[START:CV]");                         //Begin test setup
  
  /**Setup AFE for CV test */
  AfePwrCfg(AFE_ACTIVE);                        //set AFE power mode to active
  LPDacPwrCtrl(cvSensChan,PWR_UP);              //Power up LPDAC on requested sensor_channel
  LPDacCfg(cvSensChan,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);     //config DAC on requested sensor_channel
  AfeLpTiaPwrDown(cvSensChan,0);                //Power up LPTIA on requested sensor_channel
  AfeLpTiaAdvanced(cvSensChan,BANDWIDTH_NORMAL,CURRENT_NOR);
  AfeLpTiaCon(cvSensChan,LPTIA_RLOAD_0,LPTIA_RGAIN_96K,LPTIA_RFILTER_1M); 
  delay_10us(1000);
  AFE_SETUP_LPTIA_LPDAC(cvSensChan);            //Ensure LPTIA/LPDAC registers match required configuration
  AfeLpTiaCon(cvSensChan, LPTIA_RLOAD_100, RGAIN, LPTIA_RFILTER_DISCONNECT);    //Setup LPTIA gain to match user input
  
  /**Convert user inputs into DAC-scale voltages and perform CV test */
  int input_voltages[3] = {cvStartVolt,cvVertexVolt,cvEndVolt}; 
  uint16_t relative_voltages[4] = {0,0,0,0};    //array to hold converted voltages
  cvSetVoltages(input_voltages, relative_voltages, cvSensChan); //convert inputs to DAC-usable voltages
  cvEquilibriumDelay(cvSensChan, relative_voltages, tEquilibrium);      //Apply equilibrium signal 
  cvSignalMeasure(cvSensChan, relative_voltages, RGAIN, sweepRate);  //Apply CV signal and measure current response
  
  /**End test and shutdown AFE*/
  turn_off_afe_power_things_down();
  printf("[END:CV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

void cvSetVoltages(int input_voltages[3], uint16_t relative_voltages[4], uint8_t sensor_channel){
  uint16_t vMax = 2300; //maximum DAC output voltage
  
  /**Identify minimum value of input_voltages */
  int minVal = input_voltages[0];
  for(int i=1 ; i<3 ; ++i){
    if(input_voltages[i] < minVal){
      minVal = input_voltages[i];
    }
  }
 
  relative_voltages[0] = vMax - abs(minVal);    //set vZero based on minVal
 
  /**Description of voltage array elements
  --------------------------------------
  relative_voltages[0] = vZero (unsigned)
  relative_voltages[1] = vStart (unsigned)
  relative_voltages[2] = vVertex (unsigned)
  relative_voltages[3] = vEnd (unsigned)
  --------------------------------------
  input_voltages[0] = vStart (signed)
  input_voltages[1] = vVertex (signed)
  input_voltages[2] = vEnd (signed)
  --------------------------------------
*/
  /**Assign absolute voltages to each remaining test parameter based on the calculated vZero level */
  relative_voltages[1] = relative_voltages[0] - input_voltages[0];   //set vStart_abs
  relative_voltages[2] = relative_voltages[0] - input_voltages[1];   //set vVert_abs
  relative_voltages[3] = relative_voltages[0] - input_voltages[2];   //set vEnd_abs
  
  /**Briefly measure the starting potential to determine an offset to adjust DAC outputs */
  int vbiasShift = adjustDAC(relative_voltages[0], relative_voltages[1], input_voltages[0], sensor_channel);
  relative_voltages[1] += vbiasShift;
  relative_voltages[2] += vbiasShift;
  relative_voltages[3] += vbiasShift;
}

void cvEquilibriumDelay(uint16_t sensor_channel, uint16_t relative_voltages[4], uint16_t equilibrium_time){
  /** Use vZero and vStart from relative_voltages */
  uint16_t vZero = relative_voltages[0];
  uint16_t vStart = relative_voltages[1];
  LPDacWr(sensor_channel, mV_to_DAC(vZero,6), mV_to_DAC(vStart,12));
  delay_10us(100000*equilibrium_time);      //Hold vStart on sensor for equilibrium_time (seconds)
}

void cvSignalMeasure(uint16_t sensor_channel, uint16_t relative_voltages[4], uint32_t RGAIN, uint16_t scanrate){   
  /** give names to elements of relative_voltages */
  uint16_t vZero = relative_voltages[0];
  uint16_t vStart = relative_voltages[1];
  uint16_t vVertex = relative_voltages[2];
  uint16_t vEnd = relative_voltages[3];
  
  /**Setup CV timing parameters */
  uint16_t SETTLING_DELAY = 5;
  GptCfgVoltammetry(scanrate); //configure general-purpose digital timer to use chosen scanrate
  
  /**Convert voltages to 6 or 12 bit DAC-scale depending on sensor_channel */
  uint16_t cStart = mV_to_DAC(vStart,12);       //cStart on 12-bit sensor_channel
  uint16_t cVertex = mV_to_DAC(vVertex,12);     //cVertex on 12-bit sensor_channel
  uint16_t cEnd = mV_to_DAC(vEnd,12);           //cEnd on 12-bit sensor_channel
  uint16_t cZero = mV_to_DAC(vZero,6);          //cZero on 6-bit sensor_channel
  uint16_t cBias = cStart;                      //cBias to increment voltage on 12-bit sensor_channel  
  uint16_t inc = 1;                             //DAC step increment.  Step size is inc*0.537mV
  
  /**Initialize ADC parameters */
  int RTIA = LPRTIA_VAL_LOOKUP(RGAIN);
  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer(); //szAdcSamples array stores measured data
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);          //begin ADC conversion
  float vZeroMeasured = 0;
  
  /**Condition if CV ramp is moving "downwards" relative to vZero*/
  if(vStart < vVertex){
    /** Increase cBias until cBias=cVertex */
    for (cBias = cStart; cBias < cVertex; cBias = cBias + inc){
      LPDacWr(sensor_channel, cZero, cBias);              //Set 6-bit and 12-bit DAC channels
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      GptWaitForFlag();                         //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                         //Only store ADC data for every other DAC increment to save space
        szADCSamples[sampleCount]=burstSample(1,sensor_channel);  //measure VRE with 16x oversampling
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,sensor_channel);  //measure current from LPTIA with 16x oversampling
        sampleCount++;
      }
    }
    /** Decrease cBias until cBias=cEnd */
    for (cBias = cVertex; cBias > cEnd; cBias = cBias - inc){
      LPDacWr(sensor_channel, cZero, cBias);              //Set 6-bit and 12-bit DAC channels
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      GptWaitForFlag();                         //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                         //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,sensor_channel);  //measure V_RE with 16x oversampling
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,sensor_channel);  //measure current from LPTIA with 16x oversampling
        sampleCount++;
      }
    }
  }
  
  /**Condition if CV ramp is moving "upwards" relative to vZero*/
  else{
    /** Decrease cBias until cBias=cVertex */
    for (cBias = cStart; cBias > cVertex; cBias = cBias - inc){
      LPDacWr(sensor_channel, cZero, cBias);              //Set 6-bit and 12-bit DAC channels
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      GptWaitForFlag();                         //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                         //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,sensor_channel);  //measure V_RE with 16x oversampling
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,sensor_channel);  //measure current from LPTIA with 16x oversampling
        sampleCount++;
      }
    }
    /** Increase cBias until cBias=cEnd */
    for (cBias = cVertex; cBias < cEnd; cBias = cBias + inc){
      LPDacWr(sensor_channel, cZero, cBias);              //Set 6-bit and 12-bit DAC channels
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      GptWaitForFlag();                         //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                         //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1,sensor_channel);  //measure V_RE with 16x oversampling
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0,sensor_channel);  //measure current from LPTIA with 16x oversampling
        sampleCount++;
      }
    }
  }
  
  /**Manually measure 6-bit DAC channel (in mV) to more accurately calculate dfferential sensor potential */
  LPDacWr(sensor_channel, cZero, cBias);
  delay_10us(SETTLING_DELAY);
  float vZeroMeas = 1000*adc_to_volts(burstSample(2,sensor_channel));
  
  /**Put the sensor in "open circuit" state */
  turn_off_afe_power_things_down();
  /**Print test results from SzAdcSamples to terminal */
  printCVResults(cZero,cStart,cVertex,cEnd,sampleCount,RTIA,vZeroMeas);
}

void printCVResults(float cZero, float cStart, float cVertex, float cEnd, int sampleCount, int RTIA, float vZeroMeasured){
  /**Convert DAC-scale values to voltages in mV*/
  float vStart = DAC_to_mV(cStart,12);
  float vVertex = DAC_to_mV(cVertex,12);
  float vEnd = DAC_to_mV(cEnd,12);
  
  /**Get szAdcSamples and print test parameters/metadata*/
  uint16_t* szADCSamples = return_adc_buffer();
  printf("[RANGE:%.4f,%.4f,%.4f]", vZeroMeasured-vStart, vZeroMeasured-vVertex, vZeroMeasured-vEnd);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  
  /**Print test data line-by-line to terminal*/
  float tc, vDiff;
  for(uint32_t i = 0; i < sampleCount; i+=2){
    vDiff = (vZeroMeasured/1000) - adc_to_volts(szADCSamples[i]);       //sensor potential defined relative to vZero
    tc = adc_to_current(szADCSamples[i+1], RTIA);
    printf("%.4f,%.4f"EOL, vDiff,tc);
  }
  printf("]");
}

/****************End Cyclic Voltammetry Functions**********************/

/****************Square Wave Voltammetry Functions***************************/

void runSWV(void){
  setAdcMode(0);
  
  /**Get SWV user inputs from ACEstat app or command-line interface */
  uint8_t swvSensChan = getSensorChannel();     //parser expects 0 or 1
  printf("[:SVI]");
  int swvStartVolt = getVoltageInput();         //parser expects -9999 to +9999 mV
  printf("[:EVI]");
  int swvEndVolt = getVoltageInput();           //parser expects -9999 to +9999 mV
  printf("[:AMPI]");
  uint16_t swvAmp = getParameter(3);            //parser expects 000 to 999 mV
  printf("[:STEPI]");
  uint16_t swvStep = getParameter(3);           //parser expects 000 to 999 mV
  printf("[:FREQI]");
  uint16_t swvFreq = getParameter(5);           //parser expects 00000 to 99999 Hz
  printf("[:TEI]");
  uint16_t tEquilibrium = getParameter(4);      //parser expects 0000 to 9999 seconds
  printf("[:RTIAI]");
  uint8_t RTIACHOICE = getParameter(2);         //parser expects 00-25 (check LPRTIA_LOOKUP for table of values)
  uint32_t RGAIN = LPRTIA_LOOKUP(RTIACHOICE-48);
  printf("[START:SWV]");                        //begin SWV test
  
  /**Setup AFE for SWV test*/
  AfePwrCfg(AFE_ACTIVE);                        //set AFE power mode to active
  LPDacPwrCtrl(swvSensChan,PWR_UP);             //power up LPDAC
  LPDacCfg(swvSensChan,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);    //config PLDAC on requested sensor_channel
  AfeLpTiaPwrDown(swvSensChan,0);               //power up LPTIA
  AfeLpTiaAdvanced(swvSensChan,BANDWIDTH_NORMAL,CURRENT_NOR);
  AfeLpTiaCon(swvSensChan,LPTIA_RLOAD_0,LPTIA_RGAIN_96K,LPTIA_RFILTER_1M); 
  delay_10us(1000);
  AFE_SETUP_LPTIA_LPDAC(swvSensChan);           //ensurethat LPTIA/LPDAC configs match required setup for SWV
  AfeLpTiaCon(swvSensChan, LPTIA_RLOAD_10, RGAIN, LPTIA_RFILTER_DISCONNECT);   //set LPTIA gain to match user input

  /**Convert user inputs into DAC-scale voltages and perform SWV test */
  int input_voltages[3] = {swvStartVolt,swvEndVolt,swvAmp};
  uint16_t relative_voltages[3] = {0,0,0};
  swvSetVoltages(input_voltages, relative_voltages, swvSensChan);
  swvEquilibriumDelay(swvSensChan, relative_voltages, swvAmp, tEquilibrium);
  swvSignalMeasure(swvSensChan, relative_voltages, RGAIN, swvAmp, swvStep, swvFreq);

  /**End test and shutdown AFE*/
  turn_off_afe_power_things_down();
  printf("[END:SWV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

void swvSetVoltages(int input_voltages[3], uint16_t relative_voltages[3], uint8_t sensor_channel){
  uint16_t vMax = 2300; //maximum DAC output voltage

  /**Identify the minimum value between vStart and vEnd*/
  int minVal = input_voltages[0];
  if(input_voltages[1] < minVal){
    minVal = input_voltages[1];
  }
  
  /**Assign vZero based on the minVal and square wave amplitude*/
  relative_voltages[0] = vMax - (abs(minVal) + (2*input_voltages[2]));
  if(input_voltages[0] < 0 && input_voltages[1] < 0){      //if vStart and vEnd are both less than zero shift downwards further
    relative_voltages[0] = 1000;
  }
  
  /**Description of voltage array elements
  --------------------------------------
  relative_voltages[0] = vZero (unsigned)
  relative_voltages[1] = vStart (unsigned)
  relative_voltages[2] = vEnd (unsigned)
  --------------------------------------
  input_voltages[0] = vStart (signed)
  input_voltages[1] = vEnd (signed)
  input_voltages[2] = vAmp (unsigned)
  --------------------------------------
  */
  
  /**Assign relative voltages to each remaining test parameter based on the calculated vZero level*/
  relative_voltages[1] = relative_voltages[0] - input_voltages[0];   //set vStart_abs
  relative_voltages[2] = relative_voltages[0] - input_voltages[1];   //set vEnd_abs
  
  /**Briefly measure the starting potential to determine an offset to adjust DAC outputs*/
  int vbiasShift = adjustDAC(relative_voltages[0], relative_voltages[1], input_voltages[0], sensor_channel);
  relative_voltages[1] += vbiasShift;
  relative_voltages[2] += vbiasShift;
}

void swvEquilibriumDelay(uint16_t sensor_channel, uint16_t relative_voltages[3], uint16_t amp, uint16_t equilibrium_time){
  /** Use vZero and vStart from relative_voltages */
  uint16_t vZero = relative_voltages[0];
  uint16_t vStart = relative_voltages[1];
  LPDacWr(sensor_channel, mV_to_DAC(vZero,6), mV_to_DAC(vStart,12));    
  delay_10us(100000*equilibrium_time);                      //hold vStart on the sensor for time (seconds)
}

void swvSignalMeasure(uint16_t sensor_channel, uint16_t relative_voltages[3], uint32_t RGAIN, uint16_t amplitude, uint16_t cycle_step_size, uint16_t freq){
  /**Giive names to elements of relative_voltages*/
  uint16_t vZero = relative_voltages[0];
  uint16_t vStart = relative_voltages[1];
  uint16_t vEnd = relative_voltages[2];
  
  /**Convert relative voltages to DAC inputs*/
  uint16_t cStart = mV_to_DAC(vStart,12);       //vStart on 12-bit DAC channel
  uint16_t cEnd = mV_to_DAC(vEnd,12);           //vEnd on 12-bit DAC channel        
  uint16_t cZero = mV_to_DAC(vZero,6);          //vZero on 6-bit DAC channel
  uint16_t cBias = cStart;                      //cBias on 12-bit DAC channel
  uint16_t cAmp = (int)((amplitude)/0.537);
  uint16_t inc = 2*cycle_step_size;             //DAC bit is 0.537mV, x2 to make inc ~1mV
  
  /**Square wave timing parameters*/
  uint16_t SETTLING_DELAY = 5;
  uint16_t delayVal = (50000/freq/3);           //delay required to maintain specified squarewave frequency
  
  /**Initialize ADC parameters*/
  int RTIA = LPRTIA_VAL_LOOKUP(RGAIN);
  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  /**Condition if SWV baseline ramp is moving "downwards" relative to vZero*/
  if(vStart < vEnd){
    
    /** Increase cBias until cBias=cEnd */
    for (cBias = cStart; cBias < cEnd; cBias = cBias + inc){
      
      /**Squarewave Low*/
      LPDacWr(sensor_channel, cZero, cBias);
      delay_10us(SETTLING_DELAY);               // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      szADCSamples[sampleCount]=burstSample(1,sensor_channel);    //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,sensor_channel);    //measure current from LPTIA with 16x oversampling
      sampleCount++;
      
      /**Squarewave high*/
      LPDacWr(sensor_channel, cZero, cBias+2*cAmp);       //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      szADCSamples[sampleCount]=burstSample(0,sensor_channel);    //measure current from LPTIA with 16x oversampling
      sampleCount++;     
    }
  }
  /**Condition if SWV baseline ramp is moving "upwards" relative to vZero*/
  else{
    
    /** Decrease cBias until cBias=cEnd */
    for (cBias = cStart; cBias > cEnd; cBias = cBias - inc){
      
      /**Squarewave high*/
      LPDacWr(sensor_channel, cZero, cBias);
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      szADCSamples[sampleCount]=burstSample(1,sensor_channel);    //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,sensor_channel);    //measure current from LPTIA with 16x oversampling
      sampleCount++;
      
      /**Squarewave Low*/
      LPDacWr(sensor_channel, cZero, cBias-2*cAmp);       //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      szADCSamples[sampleCount]=burstSample(0,sensor_channel);    //measure current from LPTIA with 16x oversampling
      sampleCount++;     
    }
  }
  
  /**Manually measure the vZero voltage (in mV) to more accurately calculate differential sensor potential*/
  LPDacWr(sensor_channel, cZero, cBias);
  delay_10us(SETTLING_DELAY);
  float vZeroMeas = 1000*adc_to_volts(burstSample(2,sensor_channel));
  
  /**Put the sensor in "open circuit" state*/
  turn_off_afe_power_things_down();
  /**Print SWV test results to terminal*/
  printSWVResults(cZero, cStart, cEnd, sampleCount, RTIA, vZeroMeas);
}

void printSWVResults(float cZero, float cStart, float cEnd, int sampleCount, int RTIA, float vZeroMeasured){

  float vZero = vZeroMeasured;
  float vStart = DAC_to_mV(cStart,12);
  float vEnd = DAC_to_mV(cEnd,12);
  
  /**Print test parameters/metadata*/
  printf("[RANGE:%.4f,%.4f,%.4f]", vZero-vStart, vZero-vEnd);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  
  uint16_t* szADCSamples = return_adc_buffer();
  float vDiff, tc;
  
  uint8_t use_mov_avg = 1;
  for(uint16_t i = 0; i < sampleCount; i+=3){
    vDiff = (vZero/1000) - adc_to_volts(szADCSamples[i]);
    
    /**Moving average filter for SWV data*/
    if(use_mov_avg){
      int filterWidth = 20;
      tc = voltammetryMovAvg(filterWidth, szADCSamples, i+1, sampleCount, RTIA);
    }
    else{
      tc = (adc_to_current(szADCSamples[i+2],RTIA) - adc_to_current(szADCSamples[i+1],RTIA));
    }
    
    printf("%.4f,%.4f\n", vDiff, 0.92*tc);
  }
  printf("]");
}

/*************END SQUARE WAVE VOLTAMMETRY**************************/

/****************CYCLIC SQUARE WAVE VOLTAMMETRY***************************/
void runCSWV(void){
  setAdcMode(0);
  
  /**Get CSWV user inputs from ACEstat app or command-line interface */
  uint8_t cswvSensChan = getSensorChannel();    //parser expects 0 or 1
  printf("[:SVI]");
  int cswvStartVolt = getVoltageInput();        //parser expects -9999 to +9999 mV
  printf("[:VVI]");
  int cswvVertexVolt = getVoltageInput();       //parser expects -9999 to +9999 mV
  printf("[:EVI]");
  int cswvEndVolt = getVoltageInput();          //parser expects -9999 to +9999 mV
  printf("[:AMPI]");
  uint16_t cswvAmp = getParameter(3);           //parser expects 000 to 999 mV
  printf("[:STEPI]");
  uint16_t cswvStep = getParameter(3);          //parser expects 000 to 999 mV
  printf("[:FREQI]");
  uint16_t cswvFreq = getParameter(5);          //parser expects 00000 to 99999 Hz
  printf("[:TEI]");
  uint16_t tEquilibrium = getParameter(4);      //parser expects 0000 to 9999 s
  printf("[:RTIAI]");
  uint8_t RTIACHOICE = getParameter(2);         //parser expects 00-25 (check LPRTIA_LOOKUP for table of values)
  uint32_t RGAIN = LPRTIA_LOOKUP(RTIACHOICE-48); 
  printf("[START:CSWV]");                       //begin CSWV
  
  /**Setup AFE for CSWV test */
  AfePwrCfg(AFE_ACTIVE);                        //set AFE power mode to active
  LPDacPwrCtrl(cswvSensChan,PWR_UP);            //power up LPDAC
  LPDacCfg(cswvSensChan,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);   //configure DAC 12/6 bit channels
  AfeLpTiaPwrDown(cswvSensChan,0);              //power up LPTIA
  AfeLpTiaAdvanced(cswvSensChan,BANDWIDTH_NORMAL,CURRENT_NOR);  //
  AfeLpTiaCon(cswvSensChan,LPTIA_RLOAD_0,LPTIA_RGAIN_96K,LPTIA_RFILTER_1M);
  delay_10us(1000);
  AFE_SETUP_LPTIA_LPDAC(cswvSensChan);          //ensure LPTIA/LPDAC configs match required setup for CSWV
  AfeLpTiaCon(cswvSensChan, LPTIA_RLOAD_10, RGAIN, LPTIA_RFILTER_DISCONNECT);   //enable user-configurable TIA gain resistor

  /**Convert signed voltages from user input to unsigned voltages for DAC channels*/
  int relativeVoltages[4] = {cswvStartVolt,cswvVertexVolt,cswvEndVolt,cswvAmp};
  uint16_t relative_voltages[4] = {0,0,0,0};
  cswvSetVoltages(relativeVoltages, relative_voltages, cswvSensChan);
  
  /**Apply equilibrium delay and excitation signals*/
  cswvEquilibriumDelay(cswvSensChan, relative_voltages, cswvAmp, tEquilibrium);
  cswvSignalMeasure(cswvSensChan, relative_voltages, RGAIN, cswvAmp, cswvStep, cswvFreq);

  /**Turn off AFE after test completion*/
  turn_off_afe_power_things_down();
  printf("[END:CSWV]");
  NVIC_SystemReset();                           //ARM DIGITAL SOFTWARE RESET
}

void cswvSetVoltages(int input_voltages[4], uint16_t relative_voltages[4], uint8_t sensor_channel){
  uint16_t vMax = 2300;                         //maximum DAC output voltage
  
  /**Identify the minimum value in input_voltages*/
  int minVal = input_voltages[0];
  for(int i=1 ; i<3 ; ++i){
    if(input_voltages[i] < minVal){
      minVal = input_voltages[i];
    }
  }
  /**Assign vZero based on the minVal and square wave amplitude*/
  relative_voltages[0] = vMax - (abs(minVal) + (2*input_voltages[3]));
  
  if(input_voltages[0] < 0 && input_voltages[1] < 0){      //if vStart and vEnd are both less than zero shift downwards further
    relative_voltages[0] = 1000;
  }
  
  /**Description of voltage array elements
  ---------relative_voltages-----------
  relative_voltages[0] = vZero (unsigned)
  relative_voltages[1] = vStart (unsigned)
  relative_voltages[2] = vVertex (unsigned)
  relative_voltages[3] = vEnd (unsigned)
  ---------input_voltages---------------
  input_voltages[0] = vStart (signed)
  input_voltages[1] = vVertex (signed)
  input_voltages[2] = vEnd (signed)
  input_voltages[3] = vAmp (unsigned)
  --------------------------------------
  */
  
  /**Assign absolute voltages to each remaining test parameter based on the calculated vZero level*/
  relative_voltages[1] = relative_voltages[0] - input_voltages[0];   //set vStart_abs
  relative_voltages[2] = relative_voltages[0] - input_voltages[1];   //set vVertex_abs
  relative_voltages[3] = relative_voltages[0] - input_voltages[2];   //set vEnd_abs
  
  /**Briefly measure the starting potential to determine an offset to adjust DAC outputs*/
  int vbiasShift = adjustDAC(relative_voltages[0], relative_voltages[1], input_voltages[0], sensor_channel);
  relative_voltages[1] += vbiasShift;
  relative_voltages[2] += vbiasShift;
  relative_voltages[3] += vbiasShift;
}

void cswvEquilibriumDelay(uint16_t sensor_channel, uint16_t relative_voltages[4], uint16_t amplitude, uint16_t equilibrium_time){
  /** Use vZero and vStart from relative_voltages */
  uint16_t vZero = relative_voltages[0];
  uint16_t vStart = relative_voltages[1];
  LPDacWr(sensor_channel, mV_to_DAC(vZero,6), mV_to_DAC(vStart,12));    //Write the DAC to its starting voltage during the equilibrium period
  delay_10us(100000*equilibrium_time);                                              
}

void cswvSignalMeasure(uint16_t sensor_channel, uint16_t relative_voltages[4], uint32_t RGAIN, uint16_t amplitude, uint16_t cycle_step_size, uint16_t freq){
  /**Give names to elements of relative_voltages*/
  uint16_t vZero = relative_voltages[0];
  uint16_t vStart = relative_voltages[1];
  uint16_t vVertex = relative_voltages[2];
  uint16_t vEnd = relative_voltages[3];
  
  /**Convert test voltages to DAC inputs*/
  uint16_t cStart = mV_to_DAC(vStart,12);       //vStart on 12-bit channel
  uint16_t cVertex = mV_to_DAC(vVertex,12);     //vVertex on 12-bit channel
  uint16_t cEnd = mV_to_DAC(vEnd,12);           //vEnd on 12-bit channel
  uint16_t cZero = mV_to_DAC(vZero,6);          //vZero on 6-bit channel
  uint16_t cBias = cStart;                      //cBias on 12-bit channel
  uint16_t cAmp = (int)((amplitude)/0.537);     //amplitude converted to 12-bit scale
  uint16_t inc = 2*cycle_step_size;                        //1 DAC bit is 0.537mV, x2 to make increment (~1mV)x step_size
  
  /**Square wave timing parameters*/
  uint16_t SETTLING_DELAY = 5;
  uint16_t delayVal = (50000/freq/3);           //delay required to maintain specified squarewave frequency

  /**Initialize ADC parameters*/
  int RTIA = LPRTIA_VAL_LOOKUP(RGAIN);
  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  /**Condition if CSWV ramp is moving "downwards" relative to vZero*/
  if(vStart < vVertex){
    /**Increase cBias until cBias = cVertex*/
    for (cBias = cStart; cBias < cVertex; cBias = cBias + inc){
      /**Squarewave low*/
      LPDacWr(sensor_channel, cZero, cBias);
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      szADCSamples[sampleCount]=burstSample(1,sensor_channel);  //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,sensor_channel);  //measure current from LPTIA with 16x oversampling
      sampleCount++;
      
      /**Squarewave high*/
      LPDacWr(sensor_channel, cZero, cBias+2*cAmp);     //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      szADCSamples[sampleCount]=burstSample(0,sensor_channel);  //measure current from LPTIA with 16x oversampling
      sampleCount++;     
    }
    /**Decrease cBias until cBias = cEnd*/
    for (cBias = cVertex; cBias > cEnd; cBias = cBias - inc){
      /**Squarewave high*/
      LPDacWr(sensor_channel, cZero, cBias);
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      szADCSamples[sampleCount]=burstSample(1,sensor_channel);  //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,sensor_channel);  //measure current from LPTIA with 16x oversampling
      sampleCount++;
      
      /**Squarewave low*/
      LPDacWr(sensor_channel, cZero, cBias-2*cAmp);     //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      szADCSamples[sampleCount]=burstSample(0,sensor_channel);  //measure current from LPTIA with 16x oversampling
      sampleCount++;     
    }
  }
  
  /**Condition if CSWV ramp is moving "upwards" relative to vZero*/
  else{
    /**Decrease cBias until cBias = cVertex*/
    for (cBias = cStart; cBias > cVertex; cBias = cBias - inc){
 
      /**Squarewave high*/
      LPDacWr(sensor_channel, cZero, cBias);
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      szADCSamples[sampleCount]=burstSample(1,sensor_channel);  //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,sensor_channel);  //measure current from LPTIA with 16x oversampling
      sampleCount++;
      
      /**Squarewave low*/
      LPDacWr(sensor_channel, cZero, cBias-2*cAmp);     //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      szADCSamples[sampleCount]=burstSample(0,sensor_channel);  //measure current from LPTIA with 16x oversampling
      sampleCount++;   
    }
    /**Increase cBias until cBias = cEnd*/
    for (cBias = cVertex; cBias < cEnd; cBias = cBias + inc){
      /**Squarewave low*/
      LPDacWr(sensor_channel, cZero, cBias);
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      szADCSamples[sampleCount]=burstSample(1,sensor_channel);  //measure V_RE with 16x oversampling
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0,sensor_channel);  //measure current from LPTIA with 16x oversampling
      sampleCount++;
      
      /**Squarewave high*/
      LPDacWr(sensor_channel, cZero, cBias+2*cAmp);     //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      szADCSamples[sampleCount]=burstSample(0,sensor_channel);  //measure current from LPTIA with 16x oversampling
      sampleCount++;     
    }
  }
  
  /**Manually measure the vZero voltage (in mV) to more accurately calculate dfferential sensor potential*/
  LPDacWr(sensor_channel, cZero, cBias);
  delay_10us(SETTLING_DELAY);
  float vZeroMeas = 1000*adc_to_volts(burstSample(2,sensor_channel));
  
  /**Put the sensor in "open circuit" state and print test results*/
  turn_off_afe_power_things_down();
  printCSWVResults(cZero, cStart, cVertex, cEnd, sampleCount, RTIA, vZeroMeas);
}

void printCSWVResults(float cZero, float cStart, float cVertex, float cEnd, int sampleCount, int RTIA, float vZeroMeasured){
  
  /**Convert DAC-scale voltages back to millivolts*/
  float vZero = vZeroMeasured;
  float vStart = DAC_to_mV(cStart,12);
  float vVertex = DAC_to_mV(cVertex,12);
  float vEnd = DAC_to_mV(cEnd,12);
  
  /**Print test parameters/metadata*/
  printf("[RANGE:%.4f,%.4f,%.4f]", vZero-vStart, vZero-vVertex, vZero-vEnd);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  
  /**Print test data from szADCSamples*/
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
  uint16_t caChan = getSensorChannel();         //parser expects 0 or 1
  printf("[:STEPVI]");
  int stepVoltage = getVoltageInput();          //parser expects -9999 to +9999 mV
  printf("[:STEPLI]");
  uint16_t stepLength = getParameter(5);        //parser expects 00000 to 99999 ms
  printf("[:STEPDI]");
  uint16_t stepDelay = getParameter(5);         //parser expects 00000 to 99999 ms
  printf("[:RTIAI]");
  uint8_t RTIACHOICE = getParameter(2);         //parser expects 00-25 (check LPRTIA_LOOKUP for table of values)
  uint32_t RGAIN = LPRTIA_LOOKUP(RTIACHOICE);   //PASS INT VAL RATHER THAN ASCII
  printf("[START:CA]");
  
  /**Configure AFE for chronoamperometry*/
  AfePwrCfg(AFE_ACTIVE);                        //set AFE power mode to active
  LPDacPwrCtrl(caChan,PWR_UP);
  LPDacCfg(caChan,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
  AfeLpTiaPwrDown(caChan,0);
  AfeLpTiaAdvanced(caChan,BANDWIDTH_NORMAL,CURRENT_NOR);
  AfeLpTiaCon(caChan,LPTIA_RLOAD_0,LPTIA_RGAIN_96K,LPTIA_RFILTER_1M); 
  delay_10us(1000);
  AFE_SETUP_LPTIA_LPDAC(caChan);                //double check that registers match required configs for CA
  AfeLpTiaCon(caChan, LPTIA_RLOAD_100, RGAIN, LPTIA_RFILTER_DISCONNECT);
  
  /**Convert signed voltages from user input to unsigned voltages for DAC channels*/
  uint16_t relative_voltages[2] = {0,0};
  caSetVoltages(stepVoltage, relative_voltages, caChan);
  
  /**Apply CA step signal*/
  caSignalMeasure(caChan, relative_voltages, stepLength, stepDelay, RGAIN);
  
  /**Turn off AFE and reset board*/
  turn_off_afe_power_things_down();
  printf("[END:CA]");
  NVIC_SystemReset();                           //ARM DIGITAL SOFTWARE RESET
}

void caSetVoltages(int vStep, uint16_t relative_voltages[2], uint8_t sensor_channel){
  uint16_t vMax = 2300;                         //maximum DAC output voltage
  
  /**Set vZero*/
  if(vStep > 0){
    relative_voltages[0] = vMax;
  }
  else{
    relative_voltages[0] = vMax - abs(vStep) - 500;     //-500 to keep the opamp voltage further from 3.3v rail
  }
  
  relative_voltages[1] = relative_voltages[0] - vStep;  //set step voltage based on vZero
  
  /**Briefly measure the starting potential to determine an offset to adjust DAC outputs*/
  int vbiasShift = adjustDAC(relative_voltages[0], relative_voltages[1], vStep, sensor_channel);
  relative_voltages[1] += vbiasShift;
}

void caSignalMeasure(uint16_t sensor_channel, uint16_t relative_voltages[2], uint16_t length, uint16_t delay, uint32_t RGAIN){
  
  /**Give names to the elements in relative_voltages*/
  uint16_t vZero = relative_voltages[0];
  uint16_t vStep = relative_voltages[1];

  /**Convert CA voltages to DAC scale*/
  uint16_t cZero = mV_to_DAC(vZero,6);          //cZero on 6-bit channel                       
  uint16_t cStep = mV_to_DAC(vStep, 12);        //cStep on 12-bit channel            
  
  /**CA timing parameters*/
  uint16_t SETTLING_DELAY = 5;
  uint16_t samples = 500;
  float sample_interval_ms = (1000*length)/samples;
  
  /**Initialize ADC parameters*/
  int RTIA = LPRTIA_VAL_LOOKUP(RGAIN);
  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  /**Set sensor voltage to zero and maintain for the delay time*/
  LPDacWr(sensor_channel, cZero, mV_to_DAC(vZero,12));
  delay_10us(100000*delay);
  
  /**Set the sensor to the step voltage and record N=samples while holding for the step length*/
  LPDacWr(sensor_channel, cZero, cStep);
  delay_10us(SETTLING_DELAY);
  for(int i=0 ; i<samples ; ++i){
    
    /**Measure the voltage and current*/
    szADCSamples[sampleCount]=burstSample(1,sensor_channel);      //measure V_RE with 16x oversampling
    sampleCount++;
    szADCSamples[sampleCount]=burstSample(0,sensor_channel);      //measure current from LPTIA with 16x oversampling
    sampleCount++;
    delay_10us((int)length/(3*samples*(10E-6)));        /* !!!!!This timing is not accurate, need to improve this!!!!  */
  }
  
  /**Set the sensor back to 0V and record N=samples while holding for the step length*/
  LPDacWr(sensor_channel, cZero, mV_to_DAC(vZero,12));
  delay_10us(SETTLING_DELAY);
  for(int i=0 ; i<samples ; ++i){
    /**Measure the voltage and current*/
    szADCSamples[sampleCount]=burstSample(1,sensor_channel);      //measure V_RE with 16x oversampling
    sampleCount++;
    szADCSamples[sampleCount]=burstSample(0,sensor_channel);      //measure current from LPTIA with 16x oversampling
    sampleCount++;
    delay_10us((int)length/(3*samples*(10E-6)));        /* !!!!!This timing is not accurate, need to improve this!!!!  */
  }
  
  /**Manually measure the vZero voltage (in mV) to more accurately calculate dfferential sensor potential*/
  LPDacWr(sensor_channel, cZero, cStep);
  delay_10us(SETTLING_DELAY);
  float vZeroMeas = 1000*adc_to_volts(burstSample(2,sensor_channel));
  
  /**Turn of the AFE and print test data*/
  turn_off_afe_power_things_down();
  printCAResults(cZero, cStep, length, RTIA, sampleCount, sample_interval_ms, vZeroMeas);
}

void printCAResults(float cZero, float cStep, int length, int RTIA, int sampleCount, float timeStep, float vZeroMeasured){
  float zeroVoltage = vZeroMeasured;
  uint16_t* szADCSamples = return_adc_buffer();
  float tc;
  
  /**Print test metadata*/
  printf("[STEP:%f]", (cStep*0.537+200-zeroVoltage)*-1);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  
  /**Print test data from szADCSamples*/
  int index = 0;
  for(uint32_t i = 0; i < sampleCount; i+=2){
    //v = (zeroVoltage/1000) - adc_to_volts(szADCSamples[i]);   //Later, may want to plot measured voltages as well as current vs. time
    tc = adc_to_current(szADCSamples[i+1],RTIA);
    printf("%f,%f\n", index*timeStep, tc);              //chronoamperometry plotted vs.time instead of voltage
    ++index;
  }
  printf("]");
}

/****************END CHRONOAMPEROMETRY***************************/