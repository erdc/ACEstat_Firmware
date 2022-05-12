#ifndef voltammetry_H
#define voltammetry_H

/**Analog Devices ADuCM355 Reference Libraries */
#include "ADuCM355.h"
#include "ClkLib.h"
#include "UrtLib.h"
#include "GptLib.h"
#include "AfeAdcLib.h"
#include "AfeWdtLib.h"
#include "DioLib.h"
#include "RstLib.h"
#include "AfeTiaLib.h"
#include "PwrLib.h"
#include "AfeDacLib.h"

/**Standard Libraries */
#include <stdio.h>
#include <math.h>

/**ERDC custom libraries */
#include "craabUtil.h"

/***************** ACEstat Test Type Struct ********************/

/**Stores parameters and configuration for non-EIS test types*/
typedef struct {
  
  /**Common variables across all test types*/
  char* test_type;                      //"CV", "SWV", "CSWV", "CA", "LSV", "OCP", etc...
  uint16_t equilibrium_time;            //time in seconds that starting voltage is held before test begins, no data collected during this time
  uint16_t sensor_channel;               //0 or 1 corresponding to ACEstat electrode channels
  uint16_t* adc_data_buffer;            //pointer to externally-defined adc buffer array
  uint16_t rtia;                        //rtia lookup table selection value
  uint16_t sample_count;                //number of datapoints collected so far for this test
  
  /**ADuCM355 uses a differential voltage to create negative potentials, with 'zero' applied to the working electrode*/
  /**Ex: [vStart_diff, vEnd_diff, vZero] = [2200, 1200, 1700] creates a -500mV to +500mV sweep when measured from the working electrode to reference electrode*/
  uint16_t vStart_diff;                 //starting voltage for sweep, applied to reference electrode.  _diff tag indicates that this is relative to vZero
  uint16_t vEnd_diff;                   //ending voltage for sweep, applied to reference electrode.  _diff tag indicates that this is relative to vZero      
  uint16_t vZero;                       //sets the relative zero voltage at the working electrode
  int vStart;                           //starting voltage relative to zero.  Ex: vStart = vZero - vStart_diff
  int vEnd;                             //ending voltage relative to zero
  uint16_t cZero;                       //zero voltage on DAC scale (usually 6-bit)
  uint16_t cStart;                      //starting voltage on DAC scale (usually 12-bit)
  uint16_t cEnd;                        //ending voltage on DAC scale (usually 12-bit)
  uint16_t vZeroMeasured;               //directly measured for more accurate readings
  
  /**Cyclic voltammetry variables*/
  uint16_t vVertex_diff;                //CV and CSWV use additional vertex point to define 'triangle' shaped sweep
  uint16_t cvSweepRate;                 //sweep rate in mV/s for CV sweep
  int vVertex;                          //vertex voltage relative to zero
  uint16_t cVertex;                     //vertex voltage on DAC scale (usually 12-bit)
  
  /**Square wave voltammetry variables*/
  uint16_t swvFrequency;                //sqaure wave frequency in Hz
  uint16_t swvAmplitude;                //square wave amplitude in mV
  uint16_t swvStepSize;                 //step size between squarewave cycles in mV
  uint16_t cAmplitude;                  //square wave amplitude on 12-bit DAC scale
  
  /**Cyclic square wave voltammetry combines CV and SWV, has no unique parameters*/
  
  /**Chronoamperometry parameters*/
  uint8_t caStepMode;                   //0 to measure response to 0->vStart only, 1 to measure 0->vStart and vStart->0 responses
  uint16_t caDuration;                  //duration to hold vStart after intial step, and 0 volts after secondary step if caStepMode==1
  uint16_t caDelay;                     //delay prior to initial step to hold 0 volts
  
  /**Open circuit potentiometry*/
  uint16_t ocpDuration;                 //time in ms to measure potential
  uint16_t ocpSamplingFreqiency;        //sampling frequency in Hz
  
  /**Filtering parameters*/
  uint8_t use_mov_avg;                  //0 or 1, use moving average filter
  uint8_t window_width;                 //width of moving average filter window
  
}acestatTest_type;

/*****************Cyclic Voltammetry(CV) Functions ********************/

/**
  *@brief       runCV: performs setup and carries out electrochemical test/measurement on 3-electrode sensor
  *@param       debug_mode: 0 to run in normal mode, 1 to run a quick test with pre-defined parameters
  *@retval      none
*/
void runCV(int debug_mode);

/**
  *@brief       cvSetVoltages: converts +/- voltages(relative to zero) to voltages referenced to bias level (vZero)
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void cvSetVoltages(acestatTest_type *testParams);
/**
  *@brief       cvEquilibriumDelay: holds the electrode potential at (vZero-vStart) for a set duration
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void cvEquilibriumDelay(acestatTest_type *testParams);
/**
  *@brief       cvSignalMeasure: apply CV signal to electrode and measure current response.  Stores test data in SzADCsamples
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void cvSignalMeasure(acestatTest_type *testParams);
/**
  *@brief       printCVResults: prints measured voltage and current from CV test using printf()
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void printCVResults(acestatTest_type *testParams);

/*****************Square Wave Voltammetry(SWV) Functions ********************/

/**
  *@brief       runSWV: performs setup and carries out electrochemical test/measurement on 3-electrode sensor
  *@param       none
  *@retval      none
*/
void runSWV(void);

/**
  *@brief       swvSetVoltages: converts +/- voltages(relative to zero) to voltages referenced to bias level (vZero).
  *             also uses vAmp to avoid maxing-out DAC range
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void swvSetVoltages(acestatTest_type *testParams);
/**
  *@brief       swvEquilibriumDelay: holds the electrode potential at (vZero-vStart) for a set duration
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void swvEquilibriumDelay(acestatTest_type *testParams);
/**
  *@brief       swvSignalMeasure: apply SWV signal to electrode and measure current response
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void swvSignalMeasure(acestatTest_type *testParams);
/**
  *@brief       printSWVResults: prints measured voltage and current from SWV test using printf()
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void printSWVResults(acestatTest_type *testParams);

/*****************Cyclic Square Wave Voltammetry(CSWV) Functions ********************/


/**
  *@brief       runCSWV: performs setup and carries out electrochemical test/measurement on 3-electrode sensor
  *@param       none
  *@retval      none
*/
void runCSWV(void);

/**
  *@brief       cswvSetVoltages: converts +/- voltages(relative to zero) to voltages referenced to bias level (vZero).
  *             also uses vAmp to avoid maxing-out DAC range
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void cswvSetVoltages(acestatTest_type *testParams);
/**
  *@brief       cswvEquilibriumDelay: holds the electrode potential at (vZero-vStart) for a set duration
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void cswvEquilibriumDelay(acestatTest_type *testParams);
/**
  *@brief       cswvSignalMeasure: apply CSWV signal to electrode and measure current response
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void cswvSignalMeasure(acestatTest_type *testParams);
/**
  *@brief       printCSWVResults: prints measured voltage and current from CSWV test using printf()
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void printCSWVResults(acestatTest_type *testParamss);

/*****************Chrono-Amperometry(CA) Functions ********************/

/**
  *@brief       runCA: performs setup and carries out electrochemical test/measurement on 3-electrode sensor
  *@param       none
  *@retval      none
*/
void runCA(void);

/**
  *@brief       caSetVoltages: converts +/- voltages(relative to zero) to voltages referenced to bias level (vZero).
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void caSetVoltages(acestatTest_type *testParams);

/**
  *@brief       caSignalMeasure: apply CA signal to electrode and measure current response
  *@param       testParams: pointer to acestatTest_type struct containing test parameters and config
  *@retval      none
*/
void caSignalMeasure(acestatTest_type *testParams);

/*****************Open-Circuit Potentiometry(OCP) Functions ********************/

/**
  *@brief       runOCP: performs setup and carries out electrochemical test/measurement on analog input pins
  *@param       none
  *@retval      none
*/
void runOCP(void);

#endif
