#include "ACEstat_voltammetry.h"
#include "ACEstat_misc.h"

/***********************Cyclic Voltammetry(CV) Functions *************************/
void runCV(int debug_mode){
  set_adc_mode(0);
  
  acestatTest_type cvTest;
  
  /**Pre-defined parameters to run quick diagnostic tests*/
  set_printing_mode(PRINT_MODE_RAW);
  cvTest.sensor_channel = 0;                      //parser expects 0 or 1
  cvTest.vStart = -400;                           //parser expects -9999 to +9999 [mV]
  cvTest.vVertex = 400;                           //parser expects -9999 to +9999 [mV]
  cvTest.vEnd = -400;                             //parser expects -9999 to +9999 [mV]
  cvTest.cvSweepRate = 400;                       //parser expects 000 to 999 [mV/s]
  cvTest.equilibrium_time = 1;                    //parser expects 0000 to 9999 [s]
  cvTest.rtia = LPRTIA_LOOKUP(1);                       //PASS INT VAL RATHER THAN ASCII
  cvTest.printing_mode = PRINT_MODE_PROCESSED;
  
  /**If getting user inputs for test parameters*/
  if(!debug_mode){
    /**Get user inputs from ACEstat app or command-line interface */
    cvTest.sensor_channel = get_sensor_channel();                 //parser expects 0 or 1
    printf("[:SVI]");                             
    cvTest.vStart = get_parameter();                          //parser expects -9999 to +9999 [mV]
    printf("[:VVI]");
    cvTest.vVertex = get_parameter();                         //parser expects -9999 to +9999 [mV]
    printf("[:EVI]");
    cvTest.vEnd = get_parameter();                            //parser expects -9999 to +9999 [mV]
    printf("[:SRI]");
    cvTest.cvSweepRate = get_parameter();                        //parser expects 000 to 999 [mV/s]
    printf("[:TEI]");
    cvTest.equilibrium_time = get_parameter();                   //parser expects 0000 to 9999 [s]
    printf("[:RTIAI]");                    
    cvTest.rtia = LPRTIA_LOOKUP(get_parameter()-48);             //parser expects 00-25
    
    /**Get printing mode, 0 for raw ADC values, 1 for processed values*/
    printf("[:PMI]");
    cvTest.printing_mode = get_parameter();
  }
  
  cvTest.adc_data_buffer = return_adc_buffer();

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

void cvSetVoltages(acestatTest_type *tPar){
  uint16_t vMax = 2300;                         //maximum DAC output voltage
  
  /**Identify minimum value of of the three test voltages(start, vertex, end */
  int minVal = tPar->vStart;
  if(tPar->vVertex < minVal){minVal=tPar->vVertex;}
  if(tPar->vEnd < minVal){minVal=tPar->vEnd;}

  tPar->vZero = vMax - abs(minVal);       //set vZero based on minVal

  /**Assign absolute voltages to each remaining test parameter based on the calculated vZero level */
  tPar->vStart_diff = tPar->vZero - tPar->vStart;
  tPar->vVertex_diff = tPar->vZero - tPar->vVertex;
  tPar->vEnd_diff = tPar->vZero - tPar->vEnd;
  
  /**Briefly measure the starting potential to determine an offset to adjust DAC outputs */
  int vbiasShift = adjust_DAC(tPar->vZero, tPar->vStart_diff, tPar->vStart, tPar->sensor_channel);
  tPar->vStart_diff += vbiasShift;
  tPar->vVertex_diff += vbiasShift;
  tPar->vEnd_diff += vbiasShift;
}

void cvEquilibriumDelay(acestatTest_type *tPar){
  
  /** Use vZero and vStart from relative_voltages */
  uint16_t vZero = tPar->vZero;
  uint16_t vStart = tPar->vStart_diff;
  LPDacWr(tPar->sensor_channel, mV_to_DAC(vZero,6), mV_to_DAC(vStart,12));
  
  /**Use GPT0 to measure time and hold the sensor voltage for the equilibrium time*/
  gpt_config_simple();                                  //setup GPT0 with 39.4us period, increments timer_ctr by 1 every 39.4us
  reset_timer_ctr();                                    //reset the timer counter just in case
  float current_time = 0;   
  /**Hold the starting voltage while the current time is less than equilibrium time */
  while(current_time < tPar->equilibrium_time){
    current_time = (float)get_timer_ctr()*2.52/1000;    //current time in seconds, 2.52/1000 conversion ratio from reference manual
  }
  reset_timer_ctr();                                    //reset the timer counter after equilibrium time has expired
}

void cvSignalMeasure(acestatTest_type *tPar){
  
  /**Setup CV timing parameters */
  uint16_t SETTLING_DELAY = 5;
  gpt_config_scanrate(tPar->cvSweepRate);         //configure general-purpose digital timer to use chosen scanrate
  
  /**Convert voltages to 6 or 12 bit DAC-scale depending on sensor_channel */
  tPar->cStart = mV_to_DAC(tPar->vStart_diff,12);           //cStart on 12-bit DAC cahnnel
  tPar->cVertex = mV_to_DAC(tPar->vVertex_diff,12);         //cVertex on 12-bit DAC channel
  tPar->cEnd = mV_to_DAC(tPar->vEnd_diff,12);               //cEnd on 12-bit DAC channel
  tPar->cZero = mV_to_DAC(tPar->vZero,6);                   //cZero on 6-bit DAC channel
  uint16_t cBias = tPar->cStart;                            //cBias to increment voltage on 12-bit DAC channel  
  uint16_t inc = 1;                                         //DAC step increment.  Step size is inc*0.537mV
  
//  /**Double check that RLOAD=0ohms for voltammetry*/
//  pADI_AFE->LPTIACON0 &= ~(SHORT_RLOAD);
//  pADI_AFE->LPTIACON1 &= ~(SHORT_RLOAD);
  
  /**Initialize ADC parameters */
  tPar->sample_count = 0;
  tPar->adc_data_buffer = return_adc_buffer();                    //szAdcSamples array stores measured data
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);                            //begin ADC conversion
  tPar->vZeroMeasured = 0;                                        //Will measure this later to get accurate diff voltages
  
  /**Condition if CV ramp is moving "downwards" relative to vZero*/
  if(tPar->vStart_diff < tPar->vVertex_diff){
    /** Increase cBias until cBias=cVertex */
    for (cBias = tPar->cStart; cBias < tPar->cVertex; cBias = cBias + inc){
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias);    //Set 6-bit and 12-bit DAC channels
      delay_10us(SETTLING_DELAY);                                 //allow LPDAC to settle
      gpt_wait_for_flag();                                        //GPT delay to maintain voltage sweeprate
      
      if(!(cBias%SKIP_RATE)){                                                 //Only store data every SKIP_RATE increments of the DAC to save time/memory to save space
        tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_VRE,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure VRE with 16x oversampling
        tPar->sample_count++;
        tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
        tPar->sample_count++;
      }
    }
    
    /** Decrease cBias until cBias=cEnd */
    for (cBias = tPar->cVertex; cBias > tPar->cEnd; cBias = cBias - inc){
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias);                            //Set 6-bit and 12-bit DAC channels
      delay_10us(SETTLING_DELAY);                                       //allow LPDAC to settle
      gpt_wait_for_flag();                                              //GPT delay to maintain voltage sweeprate
      
      if(!(cBias%SKIP_RATE)){                                                 //Only store data every SKIP_RATE increments of the DAC to save time/memory
        tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_VRE,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure VRE with 16x oversampling
        tPar->sample_count++;
        tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
        tPar->sample_count++;
      }
    }
  }
  
  /**Condition if CV ramp is moving "upwards" relative to vZero*/
  else{
    /** Decrease cBias until cBias=cVertex */
    for (cBias = tPar->cStart; cBias > tPar->cVertex; cBias = cBias - inc){
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias);    //Set 6-bit and 12-bit DAC channels
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      gpt_wait_for_flag();                         //GPT delay to maintain voltage sweeprate
      
      if(!(cBias%SKIP_RATE)){                         //Only store data every SKIP_RATE increments of the DAC to save time/memory
        tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_VRE,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure VRE with 16x oversampling
        tPar->sample_count++;
        tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
        tPar->sample_count++;
      }
    }
    /** Increase cBias until cBias=cEnd */
    for (cBias = tPar->cVertex; cBias < tPar->cEnd; cBias = cBias + inc){
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias);    //Set 6-bit and 12-bit DAC channels
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      gpt_wait_for_flag();                         //GPT delay to maintain voltage sweeprate
      
      if(!(cBias%SKIP_RATE)){                   //Only store data every SKIP_RATE increments of the DAC to save time/memory
        tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_VRE,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure VRE with 16x oversampling
        tPar->sample_count++;
        tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
        tPar->sample_count++;
      }
    }
  }
  
  /**Manually measure 6-bit DAC channel (in mV) to more accurately calculate dfferential sensor potential */
  LPDacWr(tPar->sensor_channel, tPar->cZero, cBias);
  delay_10us(SETTLING_DELAY);
  tPar->vZeroMeasured = oversample_adc(MODE_VZERO,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);
  
  /**Put the sensor in "open circuit" state */
  turn_off_afe_power_things_down();
  
  /**Print test results from SzAdcSamples to terminal */
  printCVResults(tPar);
}

void printCVResults(acestatTest_type *tPar){
  
  printf("[RANGE:%i,%i,%i]", tPar->vStart, tPar->vVertex, tPar->vEnd);
  printf("[RGAIN:%i][RESULTS:\n", LPRTIA_VAL_LOOKUP(LPRTIA_VAL_LOOKUP(tPar->rtia)));
  
  /**Print test data line-by-line to terminal*/
  float tc, vDiff;
  for(uint32_t i = 0; i < tPar->sample_count; i+=2){
    
    /**Printing in processed mode, conversions may be out of date with app conversions*/
    if(tPar->printing_mode == PRINT_MODE_PROCESSED){
      vDiff = adc_to_voltage(tPar->vZeroMeasured) - adc_to_voltage(tPar->adc_data_buffer[i]);
      tc = adc_to_current(tPar->adc_data_buffer[i+1], LPRTIA_VAL_LOOKUP(LPRTIA_VAL_LOOKUP(tPar->rtia)));
      printf("%.4f,%.4f"EOL, vDiff,tc);
    }
    
    /**Printing in raw ADC mode*/
    else{
      printf("%i,%i,%i"EOL, tPar->vZeroMeasured, tPar->adc_data_buffer[i], tPar->adc_data_buffer[i+1]);
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
  swvTest.vStart = get_parameter();                                 //parser expects -9999 to +9999 mV
  printf("[:EVI]");
  swvTest.vEnd = get_parameter();                                   //parser expects -9999 to +9999 mV
  printf("[:AMPI]");
  swvTest.swvAmplitude = get_parameter();                              //parser expects 000 to 999 mV
  printf("[:STEPI]");
  swvTest.swvStepSize = get_parameter();                               //parser expects 000 to 999 mV
  printf("[:FREQI]");
  swvTest.swvFrequency = get_parameter();                              //parser expects 00000 to 99999 Hz
  printf("[:TEI]");
  swvTest.equilibrium_time = get_parameter();                          //parser expects 0000 to 9999 seconds
  printf("[:RTIAI]");      
  swvTest.rtia = LPRTIA_LOOKUP(get_parameter()-48);        //parser expects 00-25 
  
  /**Get printing mode, 0 for raw ADC values, 1 for processed values*/
  printf("[:PMI]");
  swvTest.printing_mode = get_parameter(1);
  
  /**Setup AFE for SWV test*/
  AFE_SETUP_VOLTAMMETRY(swvTest.sensor_channel, swvTest.rtia);
  
  printf("[START:SWV]");                                                //begin SWV test

  /**Convert user inputs into DAC-scale voltages and perform SWV test */
  swvSetVoltages(&swvTest);
  swvEquilibriumDelay(&swvTest);
  swvSignalMeasure(&swvTest);

  /**End test and shutdown AFE*/
  printf("[END:SWV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

void swvSetVoltages(acestatTest_type *tPar){
  uint16_t vMax = 2300;                                                 //maximum DAC output voltage

  /**Identify the minimum value between vStart and vEnd*/
  int minVal = tPar->vStart;
  if(tPar->vEnd < minVal){minVal = tPar->vEnd;}
  
  /**Assign vZero based on the minVal and square wave amplitude*/
  tPar->vZero = vMax - (abs(minVal) + (2*tPar->swvAmplitude));
  if(tPar->vStart < 0 && tPar->vEnd < 0){
    tPar->vZero = 1000;                                           //shift vZero further down if vStart and vEnd < 0
  }
  
  /**Assign relative voltages to each remaining test parameter based on the calculated vZero level*/
  tPar->vStart_diff = tPar->vZero - tPar->vStart;     //set vStart_diff
  tPar->vEnd_diff = tPar->vZero - tPar->vEnd;         //set vEnd_diff
  
  /**Briefly measure the starting potential to determine an offset to adjust DAC outputs*/
  int vbiasShift = adjust_DAC(tPar->vZero, tPar->vStart_diff, tPar->vStart, tPar->sensor_channel);
  tPar->vStart_diff += vbiasShift;
  tPar->vEnd_diff += vbiasShift;
}

void swvEquilibriumDelay(acestatTest_type *tPar){

  LPDacWr(tPar->sensor_channel, mV_to_DAC(tPar->vZero,6), mV_to_DAC(tPar->vStart_diff,12));    
  
  /**Use GPT0 to measure time and hold the sensor voltage for the equilibrium time*/
  gpt_config_simple();                                          //setup GPT0 with 39.4us period, increments timer_ctr by 1 every 39.4us
  reset_timer_ctr();                                            //reset the timer counter just in case
  float current_time = 0;   
  /**Hold the starting voltage while the current time is less than equilibrium time */
  while(current_time < tPar->equilibrium_time){
    current_time = (float)get_timer_ctr()*2.52/1000;            //current time in seconds, 2.52/1000 conversion ratio from reference manual
  }
  reset_timer_ctr();                                            //reset the timer counter after equilibrium time has expired
}

void swvSignalMeasure(acestatTest_type *tPar){
  
  /**Convert relative voltages to DAC inputs*/
  tPar->cStart = mV_to_DAC(tPar->vStart_diff,12);           //vStart on 12-bit DAC channel
  tPar->cEnd = mV_to_DAC(tPar->vEnd_diff,12);               //vEnd on 12-bit DAC channel        
  tPar->cZero = mV_to_DAC(tPar->vZero,6);                   //vZero on 6-bit DAC channel
  tPar->cAmplitude = (int)((tPar->swvAmplitude)/0.537);     //convert amplitude to 12-bit DAC scale
  uint16_t cBias = tPar->cStart;                                  //cBias on 12-bit DAC channel
  uint16_t inc = 2*tPar->swvStepSize;                             //DAC bit is 0.537mV/bit, x2 to make inc ~1mV
  
  /**Square wave timing parameters*/
  uint16_t SETTLING_DELAY = 5;
  uint16_t delayVal = (50000/tPar->swvFrequency/3);       //delay required to maintain specified squarewave frequency
  
  /**Initialize ADC parameters*/
  tPar->sample_count = 0;
  tPar->adc_data_buffer = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  /**Condition if SWV baseline ramp is moving "downwards" relative to vZero*/
  if(tPar->vStart_diff < tPar->vEnd_diff){
    
    /** Increase cBias until cBias=cEnd */
    for (cBias = tPar->cStart; cBias < tPar->cEnd; cBias = cBias + inc){
      /**Squarewave Low*/
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias);
      delay_10us(SETTLING_DELAY);                                       // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);                              //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_VRE,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure VRE with 16x oversampling
      tPar->sample_count++;
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
      tPar->sample_count++;
      
      /**Squarewave high*/
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias+2*tPar->cAmplitude);       //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                                       //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);                              //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
      tPar->sample_count++; 
    }
  }
  /**Condition if SWV baseline ramp is moving "upwards" relative to vZero*/
  else{
    
    /** Decrease cBias until cBias=cEnd */
    for (cBias = tPar->cStart; cBias > tPar->cEnd; cBias = cBias - inc){
      
      /**Squarewave high*/
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias);
      delay_10us(SETTLING_DELAY);                                       //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);                              //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_VRE,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure VRE with 16x oversampling
      tPar->sample_count++;
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
      tPar->sample_count++;
      
      /**Squarewave Low*/
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias-2*tPar->cAmplitude);       //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);                                       //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);                              //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
      tPar->sample_count++;     
    }
  }
  
  /**Manually measure the vZero voltage (in mV) to more accurately calculate differential sensor potential*/
  LPDacWr(tPar->sensor_channel, tPar->cZero, cBias);
  delay_10us(SETTLING_DELAY);
  tPar->vZeroMeasured = oversample_adc(MODE_VZERO,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);
  
  /**Put the sensor in "open circuit" state*/
  turn_off_afe_power_things_down();
  /**Print SWV test results to terminal*/
  printSWVResults(tPar);
}

void printSWVResults(acestatTest_type *tPar){
  
  /**Print test parameters/metadata*/
  printf("[RANGE:%i,%i]", tPar->vStart, tPar->vEnd);
  printf("[RGAIN:%i][RESULTS:\n", LPRTIA_VAL_LOOKUP(LPRTIA_VAL_LOOKUP(tPar->rtia)));
  
  float vDiff, tc;
  
  uint8_t use_mov_avg = 1;
  for(uint16_t i = 0; i < tPar->sample_count; i+=3){
    
    if(tPar->printing_mode == PRINT_MODE_PROCESSED){
      vDiff = adc_to_voltage(tPar->vZeroMeasured) - adc_to_voltage(tPar->adc_data_buffer[i]);
      
      /**Moving average filter for SWV data*/
      if(use_mov_avg){
        int filterWidth = 20;
        tc = swv_mov_avg(filterWidth, tPar->adc_data_buffer, i+1, tPar->sample_count, LPRTIA_VAL_LOOKUP(tPar->rtia));
      }
      else{
        tc = (adc_to_current(tPar->adc_data_buffer[i+2], LPRTIA_VAL_LOOKUP(LPRTIA_VAL_LOOKUP(tPar->rtia))) - adc_to_current(tPar->adc_data_buffer[i+1], LPRTIA_VAL_LOOKUP(tPar->rtia)));
      }
      printf("%.4f,%.4f"EOL, vDiff, 0.92*tc);
    }
    else{
      printf("%i,%i,%i,%i"EOL, tPar->vZeroMeasured, tPar->adc_data_buffer[i], tPar->adc_data_buffer[i+1], tPar->adc_data_buffer[i+2]);
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
  cswvTest.vStart = get_parameter();                //parser expects -9999 to +9999 mV
  printf("[:VVI]");
  cswvTest.vVertex = get_parameter();               //parser expects -9999 to +9999 mV
  printf("[:EVI]");
  cswvTest.vEnd = get_parameter();                  //parser expects -9999 to +9999 mV
  printf("[:AMPI]");
  cswvTest.swvAmplitude = get_parameter();             //parser expects 000 to 999 mV
  printf("[:STEPI]");
  cswvTest.swvStepSize = get_parameter();              //parser expects 000 to 999 mV
  printf("[:FREQI]");
  cswvTest.swvFrequency = get_parameter();             //parser expects 00000 to 99999 Hz
  printf("[:TEI]");
  cswvTest.equilibrium_time = get_parameter();         //parser expects 0000 to 9999 s
  printf("[:RTIAI]");
  cswvTest.rtia = LPRTIA_LOOKUP(get_parameter()-48); 
  
  /**Get printing mode, 0 for raw ADC values, 1 for processed values*/
  printf("[:PMI]");
  cswvTest.printing_mode = get_parameter(1);
  
  /**Setup AFE for CSWV test */
  AFE_SETUP_VOLTAMMETRY(cswvTest.sensor_channel, cswvTest.rtia);
  
  printf("[START:CSWV]");                               //begin CSWV
  
  /**Apply equilibrium delay and excitation signals*/
  cswvSetVoltages(&cswvTest);
  cswvEquilibriumDelay(&cswvTest);
  cswvSignalMeasure(&cswvTest);

  /**Turn off AFE after test completion*/
  printf("[END:CSWV]");
  NVIC_SystemReset();                           //ARM DIGITAL SOFTWARE RESET
}

void cswvSetVoltages(acestatTest_type *tPar){
  uint16_t vMax = 2300;                         //maximum DAC output voltage
  
  /**Identify the minimum value in input_voltages*/
  /**Identify minimum value of of the three test voltages(start, vertex, end */
  int minVal = tPar->vStart;
  if(tPar->vVertex < minVal){minVal=tPar->vVertex;}
  if(tPar->vEnd < minVal){minVal=tPar->vEnd;}
  
  /**Assign vZero based on the minVal and square wave amplitude*/
  tPar->vZero = vMax - (abs(minVal) + (2*tPar->swvAmplitude));

  /**Assign absolute voltages to each remaining test parameter based on the calculated vZero level*/
  tPar->vStart_diff = tPar->vZero - tPar->vStart;
  tPar->vVertex_diff = tPar->vZero - tPar->vVertex;
  tPar->vEnd_diff = tPar->vZero - tPar->vEnd;
  
  /**Briefly measure the starting potential to determine an offset to adjust DAC outputs*/
  int vbiasShift = adjust_DAC(tPar->vZero, tPar->vStart_diff, tPar->vStart, tPar->sensor_channel);
  tPar->vStart_diff += vbiasShift;
  tPar->vVertex_diff += vbiasShift;
  tPar->vEnd_diff += vbiasShift;
}

void cswvEquilibriumDelay(acestatTest_type *tPar){
  /** Use vZero and vStart from relative_voltages */
  LPDacWr(tPar->sensor_channel, mV_to_DAC(tPar->vZero,6), mV_to_DAC(tPar->vStart_diff,12));    //Write the DAC to its starting voltage during the equilibrium period
  
  /**Use GPT0 to measure time and hold the sensor voltage for the equilibrium time*/
  gpt_config_simple();                                  //setup GPT0 with 39.4us period, increments timer_ctr by 1 every 39.4us
  reset_timer_ctr();                                    //reset the timer counter just in case
  float current_time = 0;   
  /**Hold the starting voltage while the current time is less than equilibrium time */
  while(current_time < tPar->equilibrium_time){
    current_time = (float)get_timer_ctr()*2.52/1000;    //current time in seconds, 2.52/1000 conversion ratio from reference manual
  }
  reset_timer_ctr();                                    //reset the timer counter after equilibrium time has expired
}

void cswvSignalMeasure(acestatTest_type *tPar){
  
  /**Convert test voltages to DAC inputs*/
  tPar->cStart = mV_to_DAC(tPar->vStart_diff,12);   //vStart on 12-bit channel
  tPar->cVertex = mV_to_DAC(tPar->vVertex_diff,12); //vVertex on 12-bit channel
  tPar->cEnd = mV_to_DAC(tPar->vEnd_diff,12);       //vEnd on 12-bit channel
  tPar->cZero = mV_to_DAC(tPar->vZero,6);           //vZero on 6-bit channel
  uint16_t cBias = tPar->cStart;                       //cBias on 12-bit channel
  tPar->cAmplitude = (int)((tPar->swvAmplitude)/0.537);   //amplitude converted to 12-bit scale
  uint16_t inc = 2*tPar->swvStepSize;                     //1 DAC bit is 0.537mV, x2 to make increment (~1mV)x step_size
  
  /**Square wave timing parameters*/
  uint16_t SETTLING_DELAY = 5;
  uint16_t delayVal = (50000/tPar->swvFrequency/3);       //delay required to maintain specified squarewave frequency
  
  /**Initialize ADC parameters*/
  tPar->sample_count = 0;
  tPar->adc_data_buffer = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  /**Condition if CSWV ramp is moving "downwards" relative to vZero*/
  if(tPar->vStart_diff < tPar->vVertex_diff){
    /**Increase cBias until cBias = cVertex*/
    for (cBias = tPar->cStart; cBias < tPar->cVertex; cBias = cBias + inc){
      /**Squarewave low*/
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias);
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_VRE,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure VRE with 16x oversampling
      tPar->sample_count++;
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
      tPar->sample_count++;
      
      /**Squarewave high*/
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias+2*tPar->cAmplitude);     //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
      tPar->sample_count++;    
    }
    /**Decrease cBias until cBias = cEnd*/
    for (cBias = tPar->cVertex; cBias > tPar->cEnd; cBias = cBias - inc){
      /**Squarewave high*/
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias);
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_VRE,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure VRE with 16x oversampling
      tPar->sample_count++;
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
      tPar->sample_count++;
      
      /**Squarewave low*/
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias-2*tPar->cAmplitude);     //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
      tPar->sample_count++; 
    }
  }
  
  /**Condition if CSWV ramp is moving "upwards" relative to vZero*/
  else{
    /**Decrease cBias until cBias = cVertex*/
    for (cBias = tPar->cStart; cBias > tPar->cVertex; cBias = cBias - inc){
 
      /**Squarewave high*/
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias);
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_VRE,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure VRE with 16x oversampling
      tPar->sample_count++;
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
      tPar->sample_count++;
      
      /**Squarewave low*/
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias-2*tPar->cAmplitude);     //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
      tPar->sample_count++;  
    }
    /**Increase cBias until cBias = cEnd*/
    for (cBias = tPar->cVertex; cBias < tPar->cEnd; cBias = cBias + inc){
      /**Squarewave low*/
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias);
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the baseline voltage and first current for this cycle*/
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_VRE,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure VRE with 16x oversampling
      tPar->sample_count++;
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
      tPar->sample_count++;
      
      /**Squarewave high*/
      LPDacWr(tPar->sensor_channel, tPar->cZero, cBias+2*tPar->cAmplitude);     //Squarewave peak, voltage = cBias+2*amp
      delay_10us(SETTLING_DELAY);               //allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);      //holding delay to maintain squarewave frequency
      
      /**Measure the second current for this cycle*/
      tPar->adc_data_buffer[tPar->sample_count]=oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);  //measure current from LPTIA with 16x oversampling
      tPar->sample_count++;   
    }
  }
  
  /**Manually measure the vZero voltage (in mV) to more accurately calculate dfferential sensor potential*/
  LPDacWr(tPar->sensor_channel, tPar->cZero, cBias);
  delay_10us(SETTLING_DELAY);
  tPar->vZeroMeasured = oversample_adc(MODE_VZERO,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);
  
  /**Put the sensor in "open circuit" state and print test results*/
  turn_off_afe_power_things_down();
  printCSWVResults(tPar);
}

void printCSWVResults(acestatTest_type *tPar){
  
  /**Print test parameters/metadata*/
  printf("[RANGE:%i,%i,%i]", tPar->vZero-tPar->vStart_diff, tPar->vZero-tPar->vVertex_diff, tPar->vZero-tPar->vEnd_diff);
  printf("[RGAIN:%i][RESULTS:\n", LPRTIA_VAL_LOOKUP(LPRTIA_VAL_LOOKUP(tPar->rtia)));
  
  float vDiff, tc;
  uint8_t use_mov_avg = 1;
  
  for(uint16_t i = 0; i < tPar->sample_count; i+=3){
    
    if(tPar->printing_mode == PRINT_MODE_PROCESSED){
      vDiff = adc_to_voltage(tPar->vZeroMeasured) - adc_to_voltage(tPar->adc_data_buffer[i]);
      
      /**Moving average filter for SWV data*/
      if(use_mov_avg){
        int filterWidth = 20;
        tc = swv_mov_avg(filterWidth, tPar->adc_data_buffer, i+1, tPar->sample_count, LPRTIA_VAL_LOOKUP(tPar->rtia));
      }
      else{
        tc = (adc_to_current(tPar->adc_data_buffer[i+2], LPRTIA_VAL_LOOKUP(LPRTIA_VAL_LOOKUP(tPar->rtia))) - adc_to_current(tPar->adc_data_buffer[i+1], LPRTIA_VAL_LOOKUP(tPar->rtia)));
      }
      printf("%.4f,%.4f"EOL, vDiff, 0.92*tc);
    }
    else{
      printf("%i,%i,%i,%i"EOL, tPar->vZeroMeasured, tPar->adc_data_buffer[i], tPar->adc_data_buffer[i+1], tPar->adc_data_buffer[i+2]);
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
  caTest.vStart = get_parameter();                          //parser expects -9999 to +9999 mV
  printf("[:STEPLI]");
  caTest.caDuration = get_parameter();                         //parser expects 00000 to 99999 ms
  printf("[:STEPDI]");
  caTest.caDelay = get_parameter();                             //parser expects 00000 to 99999 ms
  printf("[:RTIAI]");
  caTest.rtia = LPRTIA_LOOKUP(get_parameter());                //PASS INT VAL RATHER THAN ASCII
  
  /**Get printing mode, 0 for raw ADC values, 1 for processed values*/
  printf("[:PMI]");
  caTest.printing_mode = get_parameter(1);
  
  /**Configure AFE for chronoamperometry*/
  AFE_SETUP_VOLTAMMETRY(caTest.sensor_channel, caTest.rtia);
  
  printf("[START:CA]");
  
  /**Convert signed voltages from user input to unsigned voltages for DAC channels*/
  caSetVoltages(&caTest);
  
  /**Apply CA step signal*/
  caSignalMeasure(&caTest);
  
  /**Turn off AFE and reset board*/
  printf("[END:CA]");
  NVIC_SystemReset();                                                   //ARM DIGITAL SOFTWARE RESET
}

void caSetVoltages(acestatTest_type *tPar){
  uint16_t vMax = 2300;                                                 //maximum DAC output voltage
  
  /**Set vZero*/
  if(tPar->vStart > 0){
    tPar->vZero = vMax;
  }
  else{
    tPar->vZero = vMax - abs(tPar->vStart) - 500;           //-500 to keep the potentiostat amp voltage further from 3.3v rail
  }
  
  tPar->vStart_diff = tPar->vZero - tPar->vStart;     //set step voltage based on vZero
  
  /**Briefly measure the starting potential to determine an offset to adjust DAC outputs*/
  int vbiasShift = adjust_DAC(tPar->vZero, tPar->vStart_diff, tPar->vStart, tPar->sensor_channel);
  tPar->vStart_diff += vbiasShift;
}

void caSignalMeasure(acestatTest_type *tPar){
  
  /**Convert CA voltages to DAC scale*/
  tPar->cZero = mV_to_DAC(tPar->vZero,6);           //cZero on 6-bit channel                       
  tPar->cStart = mV_to_DAC(tPar->vStart_diff, 12);   //cStep on 12-bit channel            
  
  /**CA timing parameters*/
  uint16_t SETTLING_DELAY = 5;
  float signal_length = (float)tPar->caDuration;          //signal length as float
  signal_length = signal_length/1000;                           //in seconds
  float delay_length = (float)tPar->caDelay;              //delay length as float
  delay_length = delay_length/1000;                             //in seconds
  
  /**Initialize ADC parameters*/
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  tPar->sample_count = 0;
  
  /**Set sensor voltage to zero and maintain for the delay time*/
  LPDacWr(tPar->sensor_channel, mV_to_DAC(tPar->vZero,6), mV_to_DAC(tPar->vZero,12));
  gpt_config_simple();                          //setup GPT0 with 39.4us period, increments timer_ctr by 1 every 39.4us
  reset_timer_ctr();                            //reset the timer counter just in case
  float current_time = 0;   
  while(current_time < delay_length){
    current_time = ((float)get_timer_ctr())*2.52/1000;        //current time in seconds, 2.52/1000 conversion ratio from reference manual
  }
  reset_timer_ctr();                            //reset the timer counter after equilibrium time has expired
  
  /**Set the sensor to the step voltage*/
  LPDacWr(tPar->sensor_channel, tPar->cZero, tPar->cStart);
  delay_10us(SETTLING_DELAY);
  reset_timer_ctr();                            //reset the GPT0 counter to time the main signal
  current_time = 0;                             //reset current time
  
  /**Set the sensor to the test voltage for step_duration*/
  printf("[RESULTS:\n");
  while(current_time < signal_length){
    
    current_time = ((float)get_timer_ctr())*2.52/1000;
    
    uint16_t current = oversample_adc(MODE_LPTIA,tPar->sensor_channel,ADC_OVERSAMPLE_RATE);
    
    if(tPar->printing_mode == PRINT_MODE_PROCESSED){
      printf("%.3f,%.3f\n" , current_time, adc_to_current(current, LPRTIA_VAL_LOOKUP(tPar->rtia)));
    }
    else{
      printf("%i,%\n", current_time, current);
    }
    
    delay_10us(5000);                           //delay to avoid collecting too much data
  }
  
  /**Manually measure the vZero voltage (in mV) to more accurately calculate dfferential sensor potential*/
  LPDacWr(tPar->sensor_channel, tPar->cZero, tPar->cStart);
  delay_10us(SETTLING_DELAY);
  tPar->vZeroMeasured = 1000*adc_to_voltage(oversample_adc(MODE_VZERO,tPar->sensor_channel,ADC_OVERSAMPLE_RATE));
  
  /**Turn of the AFE and print test data*/
  LPDacWr(tPar->sensor_channel, tPar->cZero, mV_to_DAC(tPar->vZero, 12));

}
/****************END CHRONOAMPEROMETRY***************************/

/****************OPEN-CIRCUIT POTENTIOMETRY***************************/

void runOCP(){
  
  set_adc_mode(0);
  
  acestatTest_type ocpTest;
  
  /**Get measurement duration parameter (in seconds) from UART*/
  printf("[:MDI]");                    
  ocpTest.ocpDuration = (float)get_parameter();
  
  /**Get printing mode, 0 for raw ADC values, 1 for processed values*/
  printf("[:PMI]");
  ocpTest.printing_mode = get_parameter();
  
  /**Configure AFE for potential measurement*/
  AFE_SETUP_VOLTAMMETRY(CHAN0, LPRTIA_LOOKUP(1));
  
  /**Setup simple timer for measuring test duration*/
  gpt_config_simple();
  
  /**More simple setup*/
  //printf("Time[s],OCP[mV]");
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);                          //begin adc conversion
  delay_10us(50);
  float current_time=0;
  reset_timer_ctr();
  
  /**Manually configure ADC/MUX settings*/
  adc_voltage_setup_AIN(ANALOG_CHAN0);
  
  float diff_voltage = 0;
  
  /**Manual Config*/
  AfeSysCfg(ENUM_AFE_PMBW_LP,ENUM_AFE_PMBW_BW50);
  AfeAdcPgaCfg(GNPGA_1,0);
  
  /**Manual ADC mux setup for testing signal quality*/
  AfeAdcChan(MUXSELP_VSE0,MUXSELN_AIN0);
  
  AfeAdcChopEn(1);
  AfeAdcIntCfg(BITM_AFE_ADCINTIEN_ADCRDYIEN);
  NVIC_EnableIRQ(AFE_ADC_IRQn);
  AfeAdcPwrUp(BITM_AFE_AFECON_ADCEN);
  AfeAdcFiltCfg(SINC3OSR_5,SINC2OSR_178,LFPBYPEN_BYP,ADCSAMPLERATE_800K);
  pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
  delay_10us(5);
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);                          //begin adc conversion
  delay_10us(50);
  reset_adc_flag();
  
  printf("\n[START:OCP]");
  
  printf("[RESULTS:\n");
  
  /**Measure potential across electrodes for the duration of the test*/
  while(current_time < ocpTest.ocpDuration){
    current_time = ((float)get_timer_ctr())*2.52/1000;          //current time in seconds, 2.52/1000 conversion ratio from reference manual

    //diff_voltage = oversample_adc(MODE_AIN, ANALOG_CHAN0, ADC_OVERSAMPLE_RATE);
    while(!adcRdy){}
    diff_voltage = get_adc_val();
    reset_adc_flag();
    
    if(ocpTest.printing_mode==PRINT_MODE_RAW){
      printf("%.3f,%i\n", current_time, (int)diff_voltage);     //print the ADCDAT register value(16-bit int)
    }
    
    if(ocpTest.printing_mode==PRINT_MODE_PROCESSED){
      diff_voltage = (diff_voltage-32237)/17.8;                 //convert ADCDAT value to float voltage equivalent
      printf("%.3f,%.3f\n", current_time, diff_voltage);        //print voltage
    }
    
    /**Delay to prevent collection of too much data*/
    delay_10us(1000);                                           //TODO: REPLACE WITH SAMPLING RATE PARAMETER
  }
  reset_timer_ctr();                                            //reset the timer counter after measurement ends
}
