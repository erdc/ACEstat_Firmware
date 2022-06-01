#ifndef eis_H
#define eis_H

/**Analog devices Libraries*/
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
#include "Impedance.h"

/**ERDC Libraries*/
#include "craabUtil.h"

/**Global variables relevant to high-level EIS functions*/

/**ACEstat EIS implementation makes use of Analog Devices' functions from M355_Impedance application example*/
/**This library provides interfacing to ACEstat external control applications*/

void runEIS(void);

#endif
