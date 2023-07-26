#ifndef ACESTAT_CLEANING_H
#define ACESTAT_CLEANING_H

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
/*********Used for electrochemically cleaning electrodes***********/

/**
  *@brief       cleaningStep1:  A CV scan in Base, 0.350V to 1.35 V at 2V/s
  *@param       none
  *@retval      none
*/
void cleaningStep1(void);

/**
  *@brief       cleaningStep2:  Two sequential CA scans in Base, 2V for 5s followed by 0.350V for 10s
  *@param       none
  *@retval      none
*/
void cleaningStep2(void);

/**
  *@brief       cleaningStep3:  20 CV scans in Acid, 0.350V to 1.35V at 4V/s.  
                                Followed by 4 CV scans in Acid, 0.350V to 1.35V at 0.100V/s
  *@param       none
  *@retval      none
*/
void cleaningStep3(void);

/**
  *@brief       cleaningStep4:  10 CV scans in Acid, at 0.100V/s at each of 4 potential ranges:
                                0.200V to 0.750V, 0.200V to 1.000V, 0.200V to 1.250V, 0.200V to 1.500V
  *@param       none
  *@retval      none
*/
void cleaningStep4(void);


  


#endif