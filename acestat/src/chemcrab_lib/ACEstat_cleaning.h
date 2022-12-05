#ifndef ACEstat_cleaning_H
#define ACEstat_cleaning_H

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
#include "ACEstat_interface.h"
#include "ACEstat_gpt.h"
#include "ACEstat_adc.h"
#include "ACEstat_misc.h"
#include "ACEstat_setup.h"
#include "ACEstat_tia.h"
#include "ACEstat_voltammetry.h"


/*****************Electrode Cleaning Functions ********************/

/**
  *@brief       cleanElectrodeAcid: 
  *@param       none
  *@retval      none
*/
void cleanElectrodeAcid(acestatTest_type *testParams);

/**
  *@brief       cleanElectrodeBase: 
  *@param       none
  *@retval      none
*/
void cleanElectrodeBase(acestatTest_type *testParams);


#endif