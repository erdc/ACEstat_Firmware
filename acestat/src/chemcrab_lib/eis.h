#ifndef eis_H
#define eis_H

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
#include <stdio.h>
#include <math.h>
#include "M355_ECSns_EIS.h"
#include "M355_ECSns_DCTest.h"

#include "craabUtil.h"

//IMPORTED AD EIS FUNCTIONS
/*
   Uncomment macro below to add DC bias for biased sensor(ex. O2 sensor) Impedance measuremnt
   bias voltage is configured by SnsInit,which means (VBIAS-VZERO) will be added to excitaion sinewave as a DC offset.
   1 - EIS for biased gas sensor
   0 - EIS for none-biased gas sensor
*/
#define EIS_DCBIAS_EN   0

/*
    Configure measurement for 2/3 lead sensor
    0 - 3 lead sensor
    1 - 2 lead sensor
*/
#define EN_2_LEAD   1

// On initialization, this function is called to temporarily close SW1 in the Low Power loop.
// This results in the LPTIA output being shorted to its input.
// For a short duration, the amplifier can handle this
// This greatly speeds up the settling time of the gas sensor.

void ChargeECSensor(void);

/**
   @brief uint8_t SnsACInit(uint8_t channel)
          Initialization for AC test, setup wave generation and switches
   @param channel :{CHAN0,CHAN1}
      - 0 or CHAN0, Sensor channel 0
      - 1 or CHAN1, Sensor channel 1
   @return 1.
*/
uint8_t SnsACInit(uint8_t channel);

/**
   @brief uint8_t SnsACSigChainCfg(float freq)
         ======== configuration of AC signal chain depends on required excitation frequency.
   @param freq :{}
            - excitation AC signal frequency
   @return 1.
   @note settings including DAC update rate, ADC update rate and DFT samples can be adjusted for
   different excitation frequencies to get better performance. As general guidelines,
       - DAC update rate: make sure at least 4 points per sinewave period. Higher rate comsumes more power.
       - ADC update rate:  at least follow Nyquist sampling rule.
       - DFT samples should cover more than 1 sine wave period. more DFT sample reduce variation but take longer time.
          the configuration can be optimised depending on user's applicationn
*/
uint8_t SnsACSigChainCfg(float freq);

/**
   @brief uint8_t SnsACTest(uint8_t channel)
          start AC test
   @param channel :{CHAN0,CHAN1}
      - 0 or CHAN0, Sensor channel 0
      - 1 or CHAN1, Sensor channel 1
   @param pDFTData :{}
      - pointer to DFT result:6x word
   @return 1.
*/
uint8_t SnsACTest(uint8_t channel);


/**
   @brief uint8_t SnsMagPhaseCal()
          calculate magnitude and phase of sensor
   @param pDFTData : {}
      - input array which stored 6 DFT data
   @param RMag :{}
      - calculated Magnitude of sensor
   @param RPhase :{}
      - calulated Phase of sensor

   @return 1.
*/
uint8_t SnsMagPhaseCal(void);

/**
    communications setup functions, almost certainly redundant once all
    headers are integrated
**/

void runEIS(void);
uint16_t getEISFrequencies();
void printEISResults(void);
//void AfeAdc_Int_Handler(void);

#endif
