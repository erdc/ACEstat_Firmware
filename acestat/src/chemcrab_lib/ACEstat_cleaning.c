#include "ACESTAT_cleaning.h"

/**
Perform a series of CV and CA scans at high scanrates to clean electrodes in acids/bases
*/

/*****************Electrode Cleaning Functions ********************/

void cleaningStep1(void){
  
  /**Base cleaning is a special implementation of CV with pre-defined parameters*/
  set_adc_mode(0);
  
  acestatTest_type cvTest;
  
  set_printing_mode(PRINT_MODE_RAW);
  cvTest.vStart = 350;                           
  cvTest.vVertex = 1350;                           
  cvTest.vEnd = 350;                             
  cvTest.cvSweepRate = 2000;                       
  cvTest.equilibrium_time = 0;                    
  cvTest.rtia = LPRTIA_LOOKUP(1);                       
  cvTest.printing_mode = PRINT_MODE_PROCESSED;
  
  cvTest.adc_data_buffer = return_adc_buffer();
  
  printf("[START:CLEANSTEP1]");
  AFE_SETUP_VOLTAMMETRY(cvTest.sensor_channel, cvTest.rtia);

  /**Convert user inputs into positive voltages and perform CV test */
  cvSetVoltages(&cvTest);                                       
  cvEquilibriumDelay(&cvTest);                                  //apply equilibrium signal 
  cvSignalMeasure(&cvTest);                                     //apply CV signal and measure current response
  
  /**End test and shutdown AFE*/
  printf("[END:CLEANSTEP1]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

void cleaningStep2(void){
  
  /**Redox cleaning step requires two CA scans, followed by two CV scans*/
  
  set_adc_mode(0);
  uint8_t chan = 0;                             //Electrode channel to use for all tests here
  uint16_t test_rtia = LPRTIA_LOOKUP(1);        //Use 1kOhm TIA gain resistor
  
  /**Chronoamperometry scans for Redox cleaning*/
  acestatTest_type caTestOxidation;        
  acestatTest_type caTestReduction;
  
  /**Oxidation step parameters*/
  caTestOxidation.sensor_channel = chan;
  caTestOxidation.caStepMode = 0;
  caTestOxidation.vStart = 2000;
  caTestOxidation.caDuration = 5000;
  caTestOxidation.caDelay = 10;
  caTestOxidation.rtia = test_rtia;
  caTestOxidation.suppress_output = 1;
  
  /**Reduction step parameters*/
  caTestReduction.sensor_channel = chan;
  caTestReduction.caStepMode = 0;
  caTestReduction.vStart = 350;
  caTestReduction.caDuration = 10000;
  caTestReduction.caDelay = 10;
  caTestReduction.rtia = test_rtia;
  caTestReduction.suppress_output = 1;
  

  /**Begin required sequence of steps and scans for Redox cleaning*/
  printf("[START:CLEANSTEP2]");
  
  /**First CA scan, Oxidation step*/
  AFE_SETUP_VOLTAMMETRY(chan, test_rtia);
  caSetVoltages(&caTestOxidation);
  caSignalMeasure(&caTestOxidation);
  
  /**Second CA scan, Reduction step*/
  AFE_SETUP_VOLTAMMETRY(chan, test_rtia);
  caSetVoltages(&caTestReduction);
  caSignalMeasure(&caTestReduction);
  
  printf("[END:CLEANSTEP2]");
  NVIC_SystemReset(); 
  
}

void cleaningStep3(void){
  
  set_adc_mode(0);
  uint8_t chan = 0;                             //Electrode channel to use for all tests here
  uint16_t test_rtia = LPRTIA_LOOKUP(1);        //Use 1kOhm TIA gain resistor
  
  /**A series of sequential CV scans*/
  acestatTest_type cvTest1;        
  acestatTest_type cvTest2;
  
  /**First CV scan parameters*/
  cvTest1.sensor_channel = chan;
  cvTest1.vStart = 350;                           
  cvTest1.vVertex = 1350;                           
  cvTest1.vEnd = 350;                             
  cvTest1.cvSweepRate = 4000;                       
  cvTest1.equilibrium_time = 0;                    
  cvTest1.rtia = test_rtia; 
  
  /**Second CV scan parameters*/
  cvTest2.sensor_channel = chan;
  cvTest2.vStart = 350;                           
  cvTest2.vVertex = 1350;                           
  cvTest2.vEnd = 350;                             
  cvTest2.cvSweepRate = 100;                       
  cvTest2.equilibrium_time = 0;                    
  cvTest2.rtia = test_rtia; 
  
  printf("[START:CLEANSTEP3]");
  
  /**Start first series of CV scans*/
  cvSetVoltages(&cvTest1);
  
  /**Scan 1 repeats 20 times*/
  for(int i=0 ; i<20 ; ++i){
    AFE_SETUP_VOLTAMMETRY(chan, test_rtia);
    cvSignalMeasure(&cvTest1);
  }

  /**Start second series of CV scans*/
  cvSetVoltages(&cvTest2);
  
  /**Scan 2 repeats 4 times*/
  for(int i=0 ; i<4 ; ++i){
    AFE_SETUP_VOLTAMMETRY(chan, test_rtia);
    cvSignalMeasure(&cvTest2);
  }
  
  printf("[END:CLEANSTEP3]");
  NVIC_SystemReset(); 
  
}

void cleaningStep4(void){
  
  set_adc_mode(0);
  uint8_t chan = 0;                             //Electrode channel to use for all tests here
  uint16_t test_rtia = LPRTIA_LOOKUP(1);        //Use 1kOhm TIA gain resistor
  
  acestatTest_type cvTest;        

  cvTest.sensor_channel = chan;
  cvTest.vStart = 200;                           
  cvTest.vVertex = 750;                           
  cvTest.vEnd = 200;                             
  cvTest.cvSweepRate = 100;                       
  cvTest.equilibrium_time = 0;                    
  cvTest.rtia = test_rtia; 
  
  printf("[START:CLEANSTEP4]");
  
  AFE_SETUP_VOLTAMMETRY(chan, test_rtia);
  
  for(int i=0 ; i<4 ; i++){
    cvSetVoltages(&cvTest);
    cvSignalMeasure(&cvTest);
    cvTest.vVertex += 250;                      //add 250mV to the vertex voltage and re-run the test
    
  }
  
  printf("[END:CLEANSTEP4]");
  
}

