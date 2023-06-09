#include "ACEstat_impulse.h"



/**   
This is effectively a modified implementation of chronoamperometry.
Delivers an impulse signal (a very short, high-amplitude CA signal),
but continues to emasure the current reponse for a time after the
pulse ends.
*/

void impulseResponse(void){
  
  set_adc_mode(0);
  
  /**Pulse setup*/
  acestatTest_type caTest;
  caTest.sensor_channel = 0;            //chan 0
  caTest.vStart = 2000;                 //2V
  caTest.caDuration = 10;               //10ms
  caTest.caDelay = 1000;                //1000ms
  caTest.rtia = LPRTIA_LOOKUP(1);       //RGAIN = 1kOhm       
  caTest.printing_mode = 1;             //print calculated currents
  caTest.suppress_output = 1;           //don't print data during the pulse
  
  /**Configure AFE for chronoamperometry*/
  AFE_SETUP_VOLTAMMETRY(caTest.sensor_channel, caTest.rtia);  
  
  /**Convert signed voltages from user input to unsigned voltages for DAC channels*/
  caSetVoltages(&caTest);
  
  /**Apply impulse signal*/
  caSignalMeasure(&caTest);
  
  
  
  
}