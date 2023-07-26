#ifndef ACESTAT_IMPULSE_H
#define ACESTAT_IMPULSE_H

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


/**
  *@brief       impulseSpike:  Measure the impulse response of a solution across an electrode
  *@param       none
  *@retval      none
*/
void impulseResponse(void);





#endif