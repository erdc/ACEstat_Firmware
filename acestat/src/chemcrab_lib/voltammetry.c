/**ERDC custom libraries */
#include "voltammetry.h"

/***********************Cyclic Voltammetry(CV) Functions *************************/
void runCV(int debug_mode){
  set_adc_mode(0);
  
  acestatTest_type cvTest;
  
  /**Pre-defined parameters to run quick diagrnostic tests*/
  cvTest.sensor_channel = 0;                      //parser expects 0 or 1
  cvTest.vStart = -100;                           //parser expects -9999 to +9999 [mV]
  cvTest.vVertex = 100;                           //parser expects -9999 to +9999 [mV]
  cvTest.vEnd = -100;                             //parser expects -9999 to +9999 [mV]
  cvTest.cvSweepRate = 200;                       //parser expects 000 to 999 [mV/s]
  cvTest.equilibrium_time = 1;                    //parser expects 0000 to 9999 [s]
  cvTest.rtia = LPRTIA_LOOKUP(1);      //PASS INT VAL RATHER THAN ASCII
  
  /**If getting user inputs for test parameters*/
  if(!debug_mode){
    /**Get user inputs from ACEstat app or command-line interface */
    cvTest.sensor_channel = get_sensor_channel();                 //parser expects 0 or 1
    printf("[:SVI]");                             
    cvTest.vStart = get_voltage_input();                          //parser expects -9999 to +9999 [mV]
    printf("[:VVI]");
    cvTest.vVertex = get_voltage_input();                         //parser expects -9999 to +9999 [mV]
    printf("[:EVI]");
    cvTest.vEnd = get_voltage_input();                            //parser expects -9999 to +9999 [mV]
    printf("[:SRI]");
    cvTest.cvSweepRate = get_parameter(3);                        //parser expects 000 to 999 [mV/s]
    printf("[:TEI]");
    cvTest.equilibrium_time = get_parameter(4);                   //parser expects 0000 to 9999 [s]
    printf("[:RTIAI]");                    
    cvTest.rtia = LPRTIA_LOOKUP(get_parameter(2));     //parser expects 00-25
  }

  printf("[START:CV]");                                         //Begin test setup
  
  /**Setup AFE for CV test */
  AFE_SETUP_VOLTAMMETRY(cvTest.sensor_channel, cvTest.rtia);

  /**Convert user inputs into positive voltages and perform CV test */
  cvSetVoltages(&cvTest);                                       
  cvEquilibriumDelay(&cvTest);                                  //apply equilibrium signal 
  cvSignalMeasure(&cvTest);                                     //apply CV signal and measure current response
  
  /**End test and shutdown AFE*/
  printf("[END:CV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

void cvSetVoltages(acestatTest_type *testParams){
  uint16_t vMax = 2300;                         //maximum DAC output voltage
  
  /**Identify minimum value of of the three test voltages(start, vertex, end */
  int minVal = testParams->vStart;
  if(testParams->vVertex < minVal){minVal=testParams->vVertex;}
  if(testParams->vEnd < minVal){minVal=testParams->vEnd;}

  testParams->vZero = vMax - abs(minVal);       //set vZero based on minVal

  /**Assign absolute voltages to each remaining test parameter based on the calculated vZero level */
  testParams->vStart_diff = testParams->vZero - testParams->vStart;
  testParams->vVertex_diff = testParams->vZero - testParams->vVertex;
  testParams->vEnd_diff = testParams->vZero - testParams->vEnd;
  
  /**Briefly measure the starting potential to determine an offset to adjust DAC outputs */
  int vbiasShift = adjust_DAC(testParams->vZero, testParams->vStart_diff, testParams->vStart, testParams->sensor_channel);
  testParams->vStart_diff += vbiasShift;
  testParams->vVertex_diff += vbiasShift;
  testParams->vEnd_diff += vbiasShift;
}

void cvEquilibriumDelay(acestatTest_type *testParams){
  /** Use vZero and vStart from relative_voltages */
  uint16_t vZero = testParams->vZero;
  uint16_t vStart = testParams->vStart_diff;
  LPDacWr(testParams->sensor_channel, mV_to_DAC(vZero,6), mV_to_DAC(vStart,12));
  
  /**Use GPT0 to measure time and hold the sensor voltage for the equilibrium time*/
  gpt_config_simple();                                  //setup GPT0 with 39.4us period, increments timer_ctr by 1 every 39.4us
  reset_timer_ctr();                                    //reset the timer counter just in case
  float current_time = 0;   
  /**Hold the starting voltage while the current time is less than equilibrium time */
  while(current_time < testParams->equilibrium_time){
    current_time = (float)get_timer_ctr()*2.52/1000;    //current time in seconds, 2.52/1000 conversion ratio from reference manual
  }
  reset_timer_ctr();                                    //reset the timer counter after equilibrium time has expired
}

void cvSignalMeasure(acestatTest_type *testParams){ 
  
  /**Setup CV timing parameters */
  uint16_t SETTLING_DELAY = 5;
  gpt_config_scanrate(testParams->cvSweepRate);         //configure general-purpose digital timer to use chosen scanrate
  
  /**Convert voltages to 6 or 12 bit DAC-scale depending on sensor_channel */
  testParams->cStart = mV_to_DAC(testParams->vStart_diff,12);           //cStart on 12-bit DAC cahnnel
  testParams->cVertex = mV_to_DAC(testParams->vVertex_diff,12);         //cVertex on 12-bit DAC channel
  testParams->cEnd = mV_to_DAC(testParams->vEnd_diff,12);               //cEnd on 12-bit DAC channel
  testParams->cZero = mV_to_DAC(testParams->vZero,6);                   //cZero on 6-bit DAC channel
  uint16_t cBias = testParams->cStart;                                              //cBias to increment voltage on 12-bit DAC channel  
  uint16_t inc = 1;                                                     //DAC step increment.  Step size is inc*0.537mV
  
  /**Initialize ADC parameters */
  testParams->sample_count = 0;
  testParams->adc_data_buffer = return_adc_buffer();                    //szAdcSamples array stores measured data
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);                                  //begin ADC conversion
  testParams->vZeroMeasured = 0;                                        //Will measure this later to get accurate diff voltages
  
  /**Condition if CV ramp is moving "downwards" relative to vZero*/
  if(testParams->vStart_diff < testParams->vVertex_diff){
    /** Increase cBias until cBias=cVertex */
    for (cBias = testParams->cStart; cBias < testParams->cVertex; cBias = cBias + inc){
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias);    //Set 6-bit and 12-bit DAC channels
      delay_10us(SETTLING_DELAY);                                       //allow LPDAC to settle
      gpt_wait_for_flag();                                              //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                                                 //Only store ADC data for every other DAC increment to save space
        testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_VRE,testParams->sensor_channel,16);  //measure VRE with 16x oversampling
        testParams->sample_count++;
        testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
        testParams->sample_count++;
      }
    }
    
    /** Decrease cBias until cBias=cEnd */
    for (cBias = testParams->cVertex; cBias > testParams->cEnd; cBias = cBias - inc){
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias);                            //Set 6-bit and 12-bit DAC channels
      delay_10us(SETTLING_DELAY);                                       //allow LPDAC to settle
      gpt_wait_for_flag();                                              //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                                                 //Only store ADC data for every other DAC increment
        testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_VRE,testParams->sensor_channel,16);  //measure VRE with 16x oversampling
        testParams->sample_count++;
        testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
        testParams->sample_count++;
      }
    }
  }
  
  /**Condition if CV ramp is moving "upwards" relative to vZero*/
  else{
    /** Decrease cBias until cBias=cVertex */
    for (cBias = testParams->cStart; cBias > testParams->cVertex; cBias = cBias - inc){
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias);    //Set 6-bit and 12-bit DAC channels
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      gpt_wait_for_flag();                         //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                         //Only store ADC data for every other DAC increment
        testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_VRE,testParams->sensor_channel,16);  //measure VRE with 16x oversampling
        testParams->sample_count++;
        testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
        testParams->sample_count++;
      }
    }
    /** Increase cBias until cBias=cEnd */
    for (cBias = testParams->cVertex; cBias < testParams->cEnd; cBias = cBias + inc){
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias);    //Set 6-bit and 12-bit DAC channels
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      gpt_wait_for_flag();                         //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                         //Only store ADC data for every other DAC increment
        testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_VRE,testParams->sensor_channel,16);  //measure VRE with 16x oversampling
        testParams->sample_count++;
        testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
        testParams->sample_count++;
      }
    }
  }
  
  /**Manually measure 6-bit DAC channel (in mV) to more accurately calculate dfferential sensor potential */
  LPDacWr(testParams->sensor_channel, testParams->cZero, cBias);
  delay_10us(SETTLING_DELAY);
  testParams->vZeroMeasured = oversample_adc(MODE_VZERO,testParams->sensor_channel,16);
  
  /**Put the sensor in "open circuit" state */
  turn_off_afe_power_things_down();
  
  /**Print test results from SzAdcSamples to terminal */
  printCVResults(testParams);
}

void printCVResults(acestatTest_type *testParams){
  
  printf("[RANGE:%.4f,%.4f,%.4f]", testParams->vStart, testParams->vVertex, testParams->vEnd);
  printf("[RGAIN:%i][RESULTS:", testParams->rtia);
  
  /**Print test data line-by-line to terminal*/
  float tc, vDiff;
  for(uint32_t i = 0; i < testParams->sample_count; i+=2){
    
    /**Printing in processed mode*/
    if(get_printing_mode() == PRINT_MODE_PROCESSED){
      vDiff = adc_to_voltage(testParams->vZeroMeasured) - adc_to_voltage(testParams->adc_data_buffer[i]);
      tc = adc_to_current(testParams->adc_data_buffer[i+1], testParams->rtia);
      printf("%.4f,%.4f"EOL, vDiff,tc);
    }
    
    /**Printing in raw ADC mode*/
    else{
      printf("%i,%i"EOL, testParams->vZeroMeasured-testParams->adc_data_buffer[i], testParams->adc_data_buffer[i+1]);
    }
  }
  printf("]");
}

/****************End Cyclic Voltammetry Functions**********************/

/****************Square Wave Voltammetry Functions***************************/

void runSWV(void){
  set_adc_mode(0);
  
  acestatTest_type swvTest;
  
  /**Get SWV user inputs from ACEstat app or command-line interface */
  swvTest.sensor_channel = get_sensor_channel();                        //parser expects 0 or 1
  printf("[:SVI]");
  swvTest.vStart = get_voltage_input();                                 //parser expects -9999 to +9999 mV
  printf("[:EVI]");
  swvTest.vEnd = get_voltage_input();                                   //parser expects -9999 to +9999 mV
  printf("[:AMPI]");
  swvTest.swvAmplitude = get_parameter(3);                              //parser expects 000 to 999 mV
  printf("[:STEPI]");
  swvTest.swvStepSize = get_parameter(3);                               //parser expects 000 to 999 mV
  printf("[:FREQI]");
  swvTest.swvFrequency = get_parameter(5);                              //parser expects 00000 to 99999 Hz
  printf("[:TEI]");
  swvTest.equilibrium_time = get_parameter(4);                          //parser expects 0000 to 9999 seconds
  printf("[:RTIAI]");      
  swvTest.rtia = LPRTIA_LOOKUP(get_parameter(2)-48);        //parser expects 00-25 
  printf("[START:SWV]");                                                //begin SWV test
  
  /**Setup AFE for SWV test*/
  AFE_SETUP_VOLTAMMETRY(swvTest.sensor_channel, swvTest.rtia);

  /**Convert user inputs into DAC-scale voltages and perform SWV test */
  swvSetVoltages(&swvTest);
  swvEquilibriumDelay(&swvTest);
  swvSignalMeasure(&swvTest);

  /**End test and shutdown AFE*/
  printf("[END:SWV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

void swvSetVoltages(acestatTest_type *testParams){
  uint16_t vMax = 2300;                                                 //maximum DAC output voltage

  /**Identify the minimum value between vStart and vEnd*/
  int minVal = testParams->vStart;
  if(testParams->vEnd < minVal){minVal = testParams->vEnd;}
  
  /**Assign vZero based on the minVal and square wave amplitude*/
  testParams->vZero = vMax - (abs(minVal) + (2*testParams->swvAmplitude));
  if(testParams->vStart < 0 && testParams->vEnd < 0){
    testParams->vZero = 1000;                                           //shift vZero further down if vStart and vEnd < 0
  }

  /**Assign relative voltages to each remaining test parameter based on the calculated vZero level*/
  testParams->vStart_diff = testParams->vZero - testParams->vStart;     //set vStart_diff
  testParams->vEnd_diff = testParams->vZero - testParams->vEnd;         //set vEnd_diff
  
  /**Briefly measure the starting potential to determine an offset to adjust DAC outputs*/
  int vbiasShift = adjust_DAC(testParams->vZero, testParams->vStart_diff, testParams->vStart, testParams->sensor_channel);
  testParams->vStart_diff += vbiasShift;
  testParams->vEnd_diff += vbiasShift;
}

void swvEquilibriumDelay(acestatTest_type *testParams){

  LPDacWr(testParams->sensor_channel, mV_to_DAC(testParams->vZero,6), mV_to_DAC(testParams->vStart,12));    
  
  /**Use GPT0 to measure time and hold the sensor voltage for the equilibrium time*/
  gpt_config_simple();                                          //setup GPT0 with 39.4us period, increments timer_ctr by 1 every 39.4us
  reset_timer_ctr();                                            //reset the timer counter just in case
  float current_time = 0;   
  /**Hold the starting voltage while the current time is less than equilibrium time */
  while(current_time < testParams->equilibrium_time){
    current_time = (float)get_timer_ctr()*2.52/1000;            //current time in seconds, 2.52/1000 conversion ratio from reference manual
  }
  reset_timer_ctr();                                            //reset the timer counter after equilibrium time has expired
}

void swvSignalMeasure(acestatTest_type *testParams){
  
  /**Convert relative voltages to DAC inputs*/
  testParams->cStart = mV_to_DAC(testParams->vStart_diff,12);           //vStart on 12-bit DAC channel
  testParams->cEnd = mV_to_DAC(testParams->vEnd_diff,12);               //vEnd on 12-bit DAC channel        
  testParams->cZero = mV_to_DAC(testParams->vZero,6);                   //vZero on 6-bit DAC channel
  testParams->cAmplitude = (int)((testParams->swvAmplitude)/0.537);     //convert amplitude to 12-bit DAC scale
  uint16_t cBias = testParams->cStart;                                  //cBias on 12-bit DAC channel
  uint16_t inc = 2*testParams->swvStepSize;                             //DAC bit is 0.537mV/bit, x2 to make inc ~1mV
  
  /**Square wave timing parameters*/
  uint16_t SETTLING_DELAY = 5;
  uint16_t delayVal = (50000/testParams->swvFrequency/3);       //delay required to maintain specified squarewave frequency
  
  /**Initialize ADC parameters*/
  testParams->sample_count = 0;
  testParams->adc_data_buffer = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  /**Condition if SWV baseline ramp is moving "downwards" relative to vZero*/
  if(testParams->vStart < testParams->vEnd){
    
    /** Increase cBias until cBias=cEnd */
    for (cBias = testParams->cStart; cBias < testParams->cEnd; cBias = cBias + inc){
      
      /**Squarewave Low*/
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias);
      delay_10us(SETTLING_DELAY);                                       // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);                              //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_VRE,testParams->sensor_channel,16);  //measure VRE with 16x oversampling
      testParams->sample_count++;
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
      testParams->sample_count++;
      
      /**Squarewave high*/
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias+2*testParams->cAmplitude);       //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                                       //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);                              //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
      testParams->sample_count++; 
    }
  }
  /**Condition if SWV baseline ramp is moving "upwards" relative to vZero*/
  else{
    
    /** Decrease cBias until cBias=cEnd */
    for (cBias = testParams->cStart; cBias > testParams->cEnd; cBias = cBias - inc){
      
      /**Squarewave high*/
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias);
      delay_10us(SETTLING_DELAY);                                       //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);                              //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_VRE,testParams->sensor_channel,16);  //measure VRE with 16x oversampling
      testParams->sample_count++;
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
      testParams->sample_count++;
      
      /**Squarewave Low*/
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias-2*testParams->cAmplitude);       //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                                       //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);                              //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
      testParams->sample_count++;     
    }
  }
  
  /**Manually measure the vZero voltage (in mV) to more accurately calculate differential sensor potential*/
  LPDacWr(testParams->sensor_channel, testParams->cZero, cBias);
  delay_10us(SETTLING_DELAY);
  testParams->vZeroMeasured = oversample_adc(MODE_VZERO,testParams->sensor_channel,16);
  
  /**Put the sensor in "open circuit" state*/
  turn_off_afe_power_things_down();
  /**Print SWV test results to terminal*/
  printSWVResults(testParams);
}

void printSWVResults(acestatTest_type *testParams){  
  
  /**Print test parameters/metadata*/
  printf("[RANGE:%.4f,%.4f,%.4f]", testParams->vStart, testParams->vEnd);
  printf("[RGAIN:%i][RESULTS:", testParams->rtia);
  
  float vDiff, tc;
  
  uint8_t use_mov_avg = 1;
  for(uint16_t i = 0; i < testParams->sample_count; i+=3){
    
    if(get_printing_mode() == PRINT_MODE_PROCESSED){
      vDiff = adc_to_voltage(testParams->vZeroMeasured) - adc_to_voltage(testParams->adc_data_buffer[i]);
      
      /**Moving average filter for SWV data*/
      if(use_mov_avg){
        int filterWidth = 20;
        tc = swv_mov_avg(filterWidth, testParams->adc_data_buffer, i+1, testParams->sample_count, testParams->rtia);
      }
      else{
        tc = (adc_to_current(testParams->adc_data_buffer[i+2], testParams->rtia) - adc_to_current(testParams->adc_data_buffer[i+1], testParams->rtia));
      }
      printf("%.4f,%.4f"EOL, vDiff, 0.92*tc);
    }
    else{
      printf("%i,%i"EOL, testParams->vZeroMeasured-testParams->adc_data_buffer[i], testParams->adc_data_buffer[i+2] - testParams->adc_data_buffer[i+1]);
    }  
  }
  printf("]");
}

/*************END SQUARE WAVE VOLTAMMETRY**************************/

/****************CYCLIC SQUARE WAVE VOLTAMMETRY***************************/
void runCSWV(void){
  set_adc_mode(0);
  
  acestatTest_type cswvTest;
  
  /**Get CSWV user inputs from ACEstat app or command-line interface */
  cswvTest.sensor_channel = get_sensor_channel();    //parser expects 0 or 1
  printf("[:SVI]");
  cswvTest.vStart = get_voltage_input();                //parser expects -9999 to +9999 mV
  printf("[:VVI]");
  cswvTest.vVertex = get_voltage_input();               //parser expects -9999 to +9999 mV
  printf("[:EVI]");
  cswvTest.vEnd = get_voltage_input();                  //parser expects -9999 to +9999 mV
  printf("[:AMPI]");
  cswvTest.swvAmplitude = get_parameter(3);             //parser expects 000 to 999 mV
  printf("[:STEPI]");
  cswvTest.swvStepSize = get_parameter(3);              //parser expects 000 to 999 mV
  printf("[:FREQI]");
  cswvTest.swvFrequency = get_parameter(5);             //parser expects 00000 to 99999 Hz
  printf("[:TEI]");
  cswvTest.equilibrium_time = get_parameter(4);         //parser expects 0000 to 9999 s
  printf("[:RTIAI]");
  cswvTest.rtia = LPRTIA_LOOKUP(get_parameter(2)-48); 
  printf("[START:CSWV]");                               //begin CSWV
  
  /**Setup AFE for CSWV test */
  AFE_SETUP_VOLTAMMETRY(cswvTest.sensor_channel, cswvTest.rtia);
  
  /**Apply equilibrium delay and excitation signals*/
  cswvSetVoltages(&cswvTest);
  cswvEquilibriumDelay(&cswvTest);
  cswvSignalMeasure(&cswvTest);

  /**Turn off AFE after test completion*/
  printf("[END:CSWV]");
  NVIC_SystemReset();                           //ARM DIGITAL SOFTWARE RESET
}

void cswvSetVoltages(acestatTest_type *testParams){
  uint16_t vMax = 2300;                         //maximum DAC output voltage
  
  /**Identify the minimum value in input_voltages*/
  /**Identify minimum value of of the three test voltages(start, vertex, end */
  int minVal = testParams->vStart;
  if(testParams->vVertex < minVal){minVal=testParams->vVertex;}
  if(testParams->vEnd < minVal){minVal=testParams->vEnd;}
  
  /**Assign vZero based on the minVal and square wave amplitude*/
  testParams->vZero = vMax - (abs(minVal) + (2*testParams->swvAmplitude));

  /**Assign absolute voltages to each remaining test parameter based on the calculated vZero level*/
  testParams->vStart_diff = testParams->vZero - testParams->vStart;
  testParams->vVertex_diff = testParams->vZero - testParams->vVertex;
  testParams->vEnd_diff = testParams->vZero - testParams->vEnd;
  
  /**Briefly measure the starting potential to determine an offset to adjust DAC outputs*/
  int vbiasShift = adjust_DAC(testParams->vZero, testParams->vStart_diff, testParams->vStart, testParams->sensor_channel);
  testParams->vStart_diff += vbiasShift;
  testParams->vVertex_diff += vbiasShift;
  testParams->vEnd_diff += vbiasShift;
}

void cswvEquilibriumDelay(acestatTest_type *testParams){
  /** Use vZero and vStart from relative_voltages */
  LPDacWr(testParams->sensor_channel, mV_to_DAC(testParams->vZero,6), mV_to_DAC(testParams->vStart_diff,12));    //Write the DAC to its starting voltage during the equilibrium period
  
  /**Use GPT0 to measure time and hold the sensor voltage for the equilibrium time*/
  gpt_config_simple();                                  //setup GPT0 with 39.4us period, increments timer_ctr by 1 every 39.4us
  reset_timer_ctr();                                    //reset the timer counter just in case
  float current_time = 0;   
  /**Hold the starting voltage while the current time is less than equilibrium time */
  while(current_time < testParams->equilibrium_time){
    current_time = (float)get_timer_ctr()*2.52/1000;    //current time in seconds, 2.52/1000 conversion ratio from reference manual
  }
  reset_timer_ctr();                                    //reset the timer counter after equilibrium time has expired
}

void cswvSignalMeasure(acestatTest_type *testParams){
  
  /**Convert test voltages to DAC inputs*/
  testParams->cStart = mV_to_DAC(testParams->vStart_diff,12);   //vStart on 12-bit channel
  testParams->cVertex = mV_to_DAC(testParams->vVertex_diff,12); //vVertex on 12-bit channel
  testParams->cEnd = mV_to_DAC(testParams->vEnd_diff,12);       //vEnd on 12-bit channel
  testParams->cZero = mV_to_DAC(testParams->vZero,6);           //vZero on 6-bit channel
  uint16_t cBias = testParams->cStart;                       //cBias on 12-bit channel
  testParams->cAmplitude = (int)((testParams->swvAmplitude)/0.537);   //amplitude converted to 12-bit scale
  uint16_t inc = 2*testParams->swvStepSize;                     //1 DAC bit is 0.537mV, x2 to make increment (~1mV)x step_size
  
  /**Square wave timing parameters*/
  uint16_t SETTLING_DELAY = 5;
  uint16_t delayVal = (50000/testParams->swvFrequency/3);       //delay required to maintain specified squarewave frequency
  
  /**Initialize ADC parameters*/
  testParams->sample_count = 0;
  testParams->adc_data_buffer = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  /**Condition if CSWV ramp is moving "downwards" relative to vZero*/
  if(testParams->vStart_diff < testParams->vVertex_diff){
    /**Increase cBias until cBias = cVertex*/
    for (cBias = testParams->cStart; cBias < testParams->cVertex; cBias = cBias + inc){
      /**Squarewave low*/
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias);
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_VRE,testParams->sensor_channel,16);  //measure VRE with 16x oversampling
      testParams->sample_count++;
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
      testParams->sample_count++;
      
      /**Squarewave high*/
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias+2*testParams->swvAmplitude);     //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
      testParams->sample_count++;    
    }
    /**Decrease cBias until cBias = cEnd*/
    for (cBias = testParams->cVertex; cBias > testParams->cEnd; cBias = cBias - inc){
      /**Squarewave high*/
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias);
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_VRE,testParams->sensor_channel,16);  //measure VRE with 16x oversampling
      testParams->sample_count++;
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
      testParams->sample_count++;
      
      /**Squarewave low*/
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias-2*testParams->swvAmplitude);     //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
      testParams->sample_count++; 
    }
  }
  
  /**Condition if CSWV ramp is moving "upwards" relative to vZero*/
  else{
    /**Decrease cBias until cBias = cVertex*/
    for (cBias = testParams->cStart; cBias > testParams->cVertex; cBias = cBias - inc){
 
      /**Squarewave high*/
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias);
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_VRE,testParams->sensor_channel,16);  //measure VRE with 16x oversampling
      testParams->sample_count++;
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
      testParams->sample_count++;
      
      /**Squarewave low*/
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias-2*testParams->swvAmplitude);     //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
      testParams->sample_count++;  
    }
    /**Increase cBias until cBias = cEnd*/
    for (cBias = testParams->cVertex; cBias < testParams->cEnd; cBias = cBias + inc){
      /**Squarewave low*/
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias);
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_VRE,testParams->sensor_channel,16);  //measure VRE with 16x oversampling
      testParams->sample_count++;
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
      testParams->sample_count++;
      
      /**Squarewave high*/
      LPDacWr(testParams->sensor_channel, testParams->cZero, cBias+2*testParams->swvAmplitude);     //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      testParams->adc_data_buffer[testParams->sample_count]=oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);  //measure current from LPTIA with 16x oversampling
      testParams->sample_count++;   
    }
  }
  
  /**Manually measure the vZero voltage (in mV) to more accurately calculate dfferential sensor potential*/
  LPDacWr(testParams->sensor_channel, testParams->cZero, cBias);
  delay_10us(SETTLING_DELAY);
  testParams->vZeroMeasured = oversample_adc(MODE_VZERO,testParams->sensor_channel,16);
  
  /**Put the sensor in "open circuit" state and print test results*/
  turn_off_afe_power_things_down();
  printCSWVResults(testParams);
}

void printCSWVResults(acestatTest_type *testParams){
  
  /**Print test parameters/metadata*/
  printf("[RANGE:%.4f,%.4f,%.4f]", testParams->vZero-testParams->vStart_diff, testParams->vZero-testParams->vVertex_diff, testParams->vZero-testParams->vEnd_diff);
  printf("[RGAIN:%i][RESULTS:", testParams->rtia);

  float vDiff, tc;
  
  uint8_t use_mov_avg = 1;
  for(uint16_t i = 0; i < testParams->sample_count; i+=3){
    
    if(get_printing_mode() == PRINT_MODE_PROCESSED){
      vDiff = (testParams->vZero/1000) - adc_to_voltage(testParams->adc_data_buffer[i]);
      
      /**Moving average filter for SWV data*/
      if(use_mov_avg){
        int filterWidth = 20;
        tc = swv_mov_avg(filterWidth, testParams->adc_data_buffer, i+1, testParams->sample_count, testParams->rtia);
      }
      
      else{
        tc = (adc_to_current(testParams->adc_data_buffer[i+2],testParams->rtia) - adc_to_current(testParams->adc_data_buffer[i+1],testParams->rtia));
      }
      
      printf("%.4f,%.4f"EOL, vDiff, 0.92*tc);
      
    }
    else{
      printf("%i,%i"EOL, testParams->vZeroMeasured-testParams->adc_data_buffer[i], testParams->adc_data_buffer[i+2] - testParams->adc_data_buffer[i+1]);
    }  
  }
  printf("]");
}


/****************END CYCLIC SQUARE WAVE VOLTAMMETRY***************************/

/****************CHRONOAMPEROMETRY***************************/

void runCA(void){
  set_adc_mode(0);
  
  acestatTest_type caTest;
  
  caTest.sensor_channel = get_sensor_channel();                 //parser expects 0 or 1
  printf("[:STEPVI]");
  caTest.vStart = get_voltage_input();                          //parser expects -9999 to +9999 mV
  printf("[:STEPLI]");
  caTest.caDuration = get_parameter(5);                         //parser expects 00000 to 99999 ms
  printf("[:STEPDI]");
  caTest.caDelay = get_parameter(5);                             //parser expects 00000 to 99999 ms
  printf("[:RTIAI]");
  caTest.rtia = LPRTIA_LOOKUP(get_parameter(2));                //PASS INT VAL RATHER THAN ASCII
  printf("[START:CA]");
  
  /**Configure AFE for chronoamperometry*/
  AFE_SETUP_VOLTAMMETRY(caTest.sensor_channel, caTest.rtia);
  
  /**Convert signed voltages from user input to unsigned voltages for DAC channels*/
  caSetVoltages(&caTest);
  
  /**Apply CA step signal*/
  caSignalMeasure(&caTest);
  
  /**Turn off AFE and reset board*/
  printf("[END:CA]");
  NVIC_SystemReset();                                                   //ARM DIGITAL SOFTWARE RESET
}

void caSetVoltages(acestatTest_type *testParams){
  uint16_t vMax = 2300;                                                 //maximum DAC output voltage
  
  /**Set vZero*/
  if(testParams->vStart > 0){
    testParams->vZero = vMax;
  }
  else{
    testParams->vZero = vMax - abs(testParams->vStart) - 500;           //-500 to keep the potentiostat amp voltage further from 3.3v rail
  }
  
  testParams->vStart_diff = testParams->vZero - testParams->vStart;     //set step voltage based on vZero
  
  /**Briefly measure the starting potential to determine an offset to adjust DAC outputs*/
  int vbiasShift = adjust_DAC(testParams->vZero, testParams->vStart_diff, testParams->vStart, testParams->sensor_channel);
  testParams->vStart_diff += vbiasShift;
}

void caSignalMeasure(acestatTest_type *testParams){
  
  /**Convert CA voltages to DAC scale*/
  testParams->cZero = mV_to_DAC(testParams->vZero,6);           //cZero on 6-bit channel                       
  testParams->cStart = mV_to_DAC(testParams->vStart_diff, 12);   //cStep on 12-bit channel            
  
  /**CA timing parameters*/
  uint16_t SETTLING_DELAY = 5;
  float signal_length = (float)testParams->caDuration;          //signal length as float
  signal_length = signal_length/1000;                           //in seconds
  float delay_length = (float)testParams->caDelay;              //delay length as float
  delay_length = delay_length/1000;                             //in seconds
  
  /**Initialize ADC parameters*/
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  testParams->sample_count = 0;
  
  /**Set sensor voltage to zero and maintain for the delay time*/
  LPDacWr(testParams->sensor_channel, mV_to_DAC(testParams->vZero,6), mV_to_DAC(testParams->vZero,12));
  gpt_config_simple();                          //setup GPT0 with 39.4us period, increments timer_ctr by 1 every 39.4us
  reset_timer_ctr();                            //reset the timer counter just in case
  float current_time = 0;   
  while(current_time < delay_length){
    current_time = ((float)get_timer_ctr())*2.52/1000;        //current time in seconds, 2.52/1000 conversion ratio from reference manual
  }
  reset_timer_ctr();                            //reset the timer counter after equilibrium time has expired
  
  /**Set the sensor to the step voltage*/
  LPDacWr(testParams->sensor_channel, testParams->cZero, testParams->cStart);
  delay_10us(SETTLING_DELAY);
  reset_timer_ctr();                            //reset the GPT0 counter to time the main signal
  current_time = 0;                             //reset current time
  
  /**Set the sensor to the test voltage for step_duration*/
  while(current_time < signal_length){
    
    current_time = ((float)get_timer_ctr())*2.52/1000;
    
    uint16_t current = oversample_adc(MODE_LPTIA,testParams->sensor_channel,16);

    printf("%.3f,%.3f\n" , current_time, adc_to_current(current, testParams->rtia));
    
    delay_10us(5000);                           //delay to avoid collecting too much data
  }
  
  /**Manually measure the vZero voltage (in mV) to more accurately calculate dfferential sensor potential*/
  LPDacWr(testParams->sensor_channel, testParams->cZero, testParams->cStart);
  delay_10us(SETTLING_DELAY);
  testParams->vZeroMeasured = 1000*adc_to_voltage(oversample_adc(MODE_VZERO,testParams->sensor_channel,16));
  
  /**Turn of the AFE and print test data*/
  LPDacWr(testParams->sensor_channel, testParams->cZero, mV_to_DAC(testParams->vZero, 12));

}
/****************END CHRONOAMPEROMETRY***************************/

/****************OPEN-CIRCUIT POTENTIOMETRY***************************/

void runOCP(){
  
}
