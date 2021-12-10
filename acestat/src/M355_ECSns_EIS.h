/**
 *****************************************************************************
   @addtogroup EC sensor
   @{
   @file     M355_ECSns_EIS.h
   @brief    Electrochemical Impedance Spectroscopy.
   @version  V0.1
   @author   ADI
   @date     April 28th 2017
   @par Revision History:
   - V0.1, April 28th 2017: initial version.
   - V0.2, September 2018: Changed ImpResult_t ffreq field to float


All files for ADuCM355 provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/

#ifndef M355_ECSNS_EIS
#define M355_ECSNS_EIS

#ifdef __cplusplus
extern "C" {
#endif

#include "AfeAdcLib.h"
#include "AfeDacLib.h"
#include "AfeTiaLib.h"
#include "AfeWdtLib.h"
#include "ClkLib.h"
#include "DioLib.h"
#include "DmaLib.h"
#include "FeeLib.h"
#include "GptLib.h"
#include "I2cLib.h"
#include "IntLib.h"
#include "PwrLib.h"
#include "RstLib.h"
#include "RtcLib.h"
#include "SpiLib.h"
#include "UrtLib.h"
#include "CrcLib.h"
#include <stdio.h>

/*
   uncomment this to use CMSIS_DSP library to calculate Impedance
*/
#include <math.h>
#define PI  3.14159265f


/*AC test Macros*/
/*
   RCAL, external calibration resistor
   will be used in impedance calculation
*/
#define AFE_RCAL  200u                                 // Assume 200ohms RCAL
/*
   High power DAC update rate
   controlled by HSDACCON[8:1], rate = 16MHz/HSDACCON[8:1]
   these bits need to be configured depending on the AC excitaion signal frequency.
   higher frequency excitation signal requires higher update rate, results in better performance but higher power consumption
*/
//#define HPDAC_UPDATE_RATE   2283u  /*2.283MHz*/
#define HPDAC_UPDATE_RATE   320u  /*320KHz*/
#define HPDAC_RATE_REG ((uint8_t)(16000/HPDAC_UPDATE_RATE))  /*AFE system clock = 16MHz*/
/*
   Excitation sine wave frequency
   controlled by WGFCW[23:0], frequency = WGFCW[23:0]*16000000/2^30 Hz; 
*/
#define SINE_FREQ  30000u /*30k Hz*/
#define SINE_FREQ_REG   (uint32_t)(((uint64_t)SINE_FREQ<<30)/16000000.0+0.5)
/*
   Excitaion sine wave amplitude, this value could be applied on calibration resistor or unknown sensor
   Controlled by WGAMPLITUDE[10:0], HSDACCON[0] and HSDACCON[12]
   ----------------------------------------------------------------------------------
     Gain   |  DAC attenuator(HSDACCON[0])  |  Excitaion Amplifier Gain(HSDACCON[12])   |
   ---------|-----------------------------|-----------------------------------------|
       2    |           1(0)              |                  2(0)                   |
   ---------|-----------------------------|-----------------------------------------|
      1/5   |           1(0)              |                  1/5(1)                 |
   ---------|-----------------------------|-----------------------------------------|
      1/4   |           1/4(1)            |                  2(0)                   |
   ---------|-----------------------------|-----------------------------------------|
      1/20  |           1/4(1)            |                  1/5(1)                 |
   ----------------------------------------------------------------------------------
   AC amplitude = WGAMPLITUDE[10:0]*HPDAC_LSB*Gain
   HPDAC_LSB = 800mV/(2^12-1)
*/
#define SINE_AMPLITUDE   15u //15mV
#define SINE_AMPLITUDE_REG (uint16_t)(SINE_AMPLITUDE*20/HPDAC_LSB+0.5)  //assuming Gain = 1/20
/*
   Excitation sine wave phase and DC offset
*/
#define SINE_PHASE 0 /*0 degree*/
/*
   Excitation sine wave phase and DC offset
*/
#define SINE_OFFSET 0 /*0 dc offset*/
#define SINE_OFFSET_REG (uint16_t)(SINE_OFFSET/HPDAC_LSB+0.5)

/*DFT data
DFT_result[0] - real part of Rload+Sensor
DFT_result[1] - img part of Rload+Sensor
DFT_result[2] - real part of Rload
DFT_result[3] - img part of Rload
DFT_result[4] - real part of Rcal
DFT_result[5] - img part of Rcal
*/
typedef struct
{
   float freq;
   int32_t DFT_result[6];
   float DFT_Mag[4];
   float   Mag;
   float   Phase;
   float   RloadMag;
   float   Cap;
   float   Re_Mag;
   float   Im_Mag;
}ImpResult_t;

/*=========================== Function declarations ====================*/
uint8_t SnsACInit(uint8_t channel);
uint8_t SnsACSigChainCfg(float freq);
uint8_t SnsACTest(uint8_t channel);
uint8_t SnsMagPhaseCal(void);


#ifdef __cplusplus
}
#endif

#endif // #define M355_ECSNS_EIS
