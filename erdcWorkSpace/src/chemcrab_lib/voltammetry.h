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

/*****************Cyclic Voltammetry(CV) Functions ********************/

/**
  *@brief       runCV: performs setup and carries out electrochemical test/measurement on 3-electrode sensor
  *@param       none
  *@retval      none
*/
void runCV(void);

/**
  *@brief       cvSetVoltages: converts +/- voltages(relative to zero) to voltages referenced to bias level (vZero)
  *@param       input_voltages: +/- voltages, {vStart, vVertex, vEnd}
  *@param       relative_voltages: voltages relative to vZero bias, {vZero, vStart, vVertex, vEnd}
  *@param       channel: sensor channel, 0 or 1
  *@retval      none
*/
void cvSetVoltages(int input_voltages[3], 
                   uint16_t relative_voltages[4], 
                   uint8_t sensor_channel);
/**
  *@brief       cvEquilibriumDelay: holds the electrode potential at (vZero-vStart) for a set duration
  *             Ex: input_voltages = {-400, +400, -400} ---->   relative_voltages = {1800, 1400, 2200, 1400}
  *@param       relative_voltages: voltages relative to vZero bias, {vZero, vStart, vVertex, vEnd}
  *@param       sensor_channel: 0 or 1
  *@param       equilibrium_time: duration to hold voltage at (vZero-vStart), in seconds
  *@retval      none
*/
void cvEquilibriumDelay(uint16_t sensor_channel, 
                        uint16_t relative_voltages[4], 
                        uint16_t equilibrum_time);
/**
  *@brief       cvSignalMeasure: apply CV signal to electrode and measure current response.  Stores test data in SzADCsamples
  *@param       sensor_channel: 0 or 1
  *@param       relative_voltages: voltages relative to vZero bias, {vZero, vStart, vVertex, vEnd}
  *@param       RGAIN: TIA feedback gain resistor value
  *@param       scanrate: rate of change of voltage for CV ramp, in mV/s
  *@retval      none
*/
void cvSignalMeasure(uint16_t channel, 
                     uint16_t relative_voltages[4], 
                     uint32_t RGAIN, uint16_t scanrate);
/**
  *@brief       printCVResults: prints measured voltage and current from CV test using printf()
  *@param       cZero,cStart,cVertex,cEnd: DAC-scale equivalents of relative_voltages
  *@param       sampleCount: total number of collected datapoints
  *@param       RTIA: TIA gain resistor value
  *@param       vZeroMeasured: measured value of vZero output for more accurate voltage calculations
  *@retval      none
*/
void printCVResults(float cZero, 
                    float cStart, 
                    float cVertex, 
                    float cEnd, 
                    int sampleCount, 
                    int RTIA, 
                    float vZeroMeasured);

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
  *@param       input_voltages: +/- voltages, {vStart, vEnd, vAmp}
  *@param       relative_voltages: voltages relative to vZero bias, {vZero, vStart, vEnd}
  *@param       sensor_channel: 0 or 1
  *@retval      none
*/
void swvSetVoltages(int input_voltages[3], 
                    uint16_t relative_voltages[3], 
                    uint8_t sensor_channel);
/**
  *@brief       swvEquilibriumDelay: holds the electrode potential at (vZero-vStart) for a set duration
  *@param       relative_voltages: voltages relative to vZero bias, {vZero, vStart, vEnd}
  *@param       sensor_channel: 0 or 1
  *@param       equilibrium_time: duration to hold voltage at (vZero-vStart), in seconds
  *@retval      none
*/
void swvEquilibriumDelay(uint16_t sensor_channel, 
                         uint16_t relative_voltages[3], 
                         uint16_t amplitude, 
                         uint16_t equilibrium_time);
/**
  *@brief       swvSignalMeasure: apply SWV signal to electrode and measure current response
  *@param       sensor_channel: 0 or 1
  *@param       relative_voltages: voltages relative to vZero bias, {vZero, vStart, vEnd}
  *@param       RGAIN: TIA feedback gain resistor value
  *@param       amplitude: midpoint-to-peak squarewave amplitude in mV
  *@param       cycle_step_size: baseline step size between squarewave cycles, in mV
  *@param       freq: squarewave frequency, in Hz
  *@retval      none
*/
void swvSignalMeasure(uint16_t channel, 
                      uint16_t relative_voltages[3], 
                      uint32_t RGAIN, 
                      uint16_t amplitude, 
                      uint16_t cycle_step_size, 
                      uint16_t freq);
/**
  *@brief       printSWVResults: prints measured voltage and current from SWV test using printf()
  *@param       cZero,cStart,cEnd: DAC-scale equivalents of relative_voltages
  *@param       sampleCount: total number of collected datapoints
  *@param       RTIA: TIA gain resistor value
  *@param       vZeroMeasured: measured value of vZero output for more accurate voltage calculations
  *@retval      none
*/
void printSWVResults(float cZero, 
                     float cStart, 
                     float cEnd, 
                     int sampleCount, 
                     int RTIA, 
                     float vZeroMeasured);

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
  *@param       input_voltages: +/- voltages, {vStart, vVertex, vEnd, vAmp}
  *@param       relative_voltages: voltages relative to vZero bias, {vZero, vStart, vVertex, vEnd}
  *@param       sensor_channel: 0 or 1
  *@retval      none
*/
void cswvSetVoltages(int input_voltages[4], 
                     uint16_t relative_voltages[4], 
                     uint8_t sensor_channel);
/**
  *@brief       cswvEquilibriumDelay: holds the electrode potential at (vZero-vStart) for a set duration
  *@param       relative_voltages: voltages relative to vZero bias, {vZero, vStart, vVertex, vEnd}
  *@param       sensor_channel: 0 or 1
  *@param       amplitude: CSWV midpoint-to-peak amplitude
  *@param       equilibrium_time: duration to hold voltage at (vZero-vStart), in seconds
  *@retval      none
*/
void cswvEquilibriumDelay(uint16_t sensor_channel, 
                          uint16_t relative_voltages[4], 
                          uint16_t amplitude, 
                          uint16_t equilibrium_time);
/**
  *@brief       cswvSignalMeasure: apply CSWV signal to electrode and measure current response
  *@param       sensor_channel: sensor channel, 0 or 1
  *@param       relative_voltages: voltages relative to vZero bias, {vZero, vStart, vVertex, vEnd}
  *@param       RGAIN: TIA feedback gain resistor value
  *@param       amplitude: midpoint-to-peak squarewave amplitude in mV
  *@param       cycle_step_size: baseline step size between squarewave cycles, in mV
  *@param       freq: squarewave frequency, in Hz
  *@retval      none
*/
void cswvSignalMeasure(uint16_t sensor_channel, 
                       uint16_t relative_voltages[4], 
                       uint32_t RGAIN, 
                       uint16_t amplitude, 
                       uint16_t cycle_step_size, 
                       uint16_t freq);
/**
  *@brief       printCSWVResults: prints measured voltage and current from CSWV test using printf()
  *@param       cZero,cStart,cVertex,cEnd: DAC-scale equivalents of relative_voltages
  *@param       sampleCount: total number of collected datapoints
  *@param       RTIA: TIA gain resistor value
  *@param       vZeroMeasured: measured value of vZero output for more accurate voltage calculations
  *@retval      none
*/
void printCSWVResults(float cZero, 
                      float cStart, 
                      float cVertex, 
                      float cEnd, 
                      int sampleCount, 
                      int RTIA, 
                      float vZeroMeasured);

/*****************Chrono-Amperometry(CA) Functions ********************/

/**
  *@brief       runCA: performs setup and carries out electrochemical test/measurement on 3-electrode sensor
  *@param       none
  *@retval      none
*/
void runCA(void);

/**
  *@brief       caSetVoltages: converts +/- voltages(relative to zero) to voltages referenced to bias level (vZero).
  *@param       vStep: +/- amplitude of the CA voltage step in mV
  *@param       relative_voltages: voltages relative to vZero bias, {vZero, vStep}
  *@param       sensor_channel: 0 or 1
  *@retval      none
*/
void caSetVoltages(int vStep, 
                   uint16_t relative_voltages[2], 
                   uint8_t sensor_channel);

/**
  *@brief       caSignalMeasure: apply CA signal to electrode and measure current response
  *@param       sensor_channel: 0 or 1
  *@param       relative_voltages: voltages relative to vZero bias, {vZero, vStep}
  *@param       step_duration: duration in ms of CA step
  *@param       pre_step_delay: delay in ms before CA step is applied
  *@param       RGAIN: TIA feedback gain resistor value
  *@retval      none
*/
void caSignalMeasure(uint16_t sensor_channel, 
                     uint16_t relative_voltages[2], 
                     uint16_t step_duration, 
                     uint16_t pre_step_delay, 
                     uint32_t RGAIN);
/**
  *@brief       printCAResults: prints measured voltage and current from CA test using printf()
  *@param       cZero,cStep: DAC-scale equivalents of relative_voltages
  *@param       length: duration in ms of CA step signal
  *@param       RTIA: TIA gain resistor value
  *@param       sampleCount: total number of collected datapoints
  *@param       timeStep: incremental time between measurements
  *@param       vZeroMeasured: measured value of vZero output for more accurate voltage calculations
  *@retval      none
*/
void printCAResults(float cZero, 
                    float cStep, 
                    int length, 
                    int RTIA, 
                    int sampleCount, 
                    float timeStep, 
                    float vZeroMeasured);

#endif
