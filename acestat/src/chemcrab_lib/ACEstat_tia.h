#ifndef ACESTAT_TIA_H
#define ACESTAT_TIA_H

/**Analog Devices ADuCM355 reference libraries*/
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
#include "ad5940.h"

/***************** TIA setup functions ********************/

/**
  *@brief       HSRTIA_LOOKUP: get an HSRTIA register mask from list selection
  *@param       choice: list number selection for HSRTIA value, 0-7
  *@retval      HSRTIA register value for selected resistance
*/
uint16_t HSRTIA_LOOKUP(uint8_t choice);

/**
  *@brief       LPRTIA_LOOKUP: get an LPRTIA register value from list selection
  *@param       choice: list number selection for LPRTIA value, 0-25
  *@retval      LPRTIA register value for selected resistance
*/
uint16_t LPRTIA_LOOKUP(uint8_t choice);

/**
  *@brief       HSRTIA_VAL_LOOKUP: get physical resistance from HSRTIA register value
  *@param       RGAIN: HSRTIA register value
  *@retval      feedback resistance in Ohms
*/
int HSRTIA_VAL_LOOKUP(uint32_t RGAIN);

/**
  *@brief       LPRTIA_VAL_LOOKUP: get physical resistance from LPRTIA register value
  *@param       RGAIN: LPRTIA register value
  *@retval      feedback resistance in Ohms
*/
int LPRTIA_VAL_LOOKUP(uint32_t RGAIN);

/**
  *@brief       AFE_SETUP_LPTIA_LPDAC: configure the AFE registers to the necessary settings for voltammetry testing
  *@param       sensor_channel: 0 or 1
  *@retval      none
*/

/**Quick fix to reset RLOAD to 0Ohm during configuration*/
#define SHORT_RLOAD (111 << 10)

void AFE_SETUP_LPTIA_LPDAC(uint8_t sensor_channel);

/**
  *@brief       hptia_setup_parameters: previously used setup function for HPTIA
  *@param       RTIA: TIA feedback gain resistance
  *@retval      none
*/
void hptia_setup_parameters(uint32_t RTIA);

/**
  *@brief       lptia_setup_parameters: previously used setup function for LPTIA
  *@param       RTIA: TIA feedback gain resistance
  *@retval      none
*/
void lptia_setup_parameters(uint32_t RTIA);

/**
  *@brief       AFE_SETUP_VOLTAMMETRY: sets up the to run voltammetry
  *@param       channel: electrode channel to use
  *@param       RTIA: TIA feedback gain resistance
  *@retval      none
*/
void AFE_SETUP_VOLTAMMETRY(uint8_t channel, uint32_t RTIA);

#endif