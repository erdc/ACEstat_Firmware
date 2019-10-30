/**
 *****************************************************************************
   @file     AfeWdtLib.h
   @brief    Set of AFE watchdog Timer peripheral functions.
   @version  V0.1
   @author   ADI
   @date     August 2016
     - V0.2, July 2018, added AfeWdtWindowCfg() to support windowed watchdog settings

All files provided by ADI, including this file, are
provided as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/
#ifndef AFEWDTLIB_H
#define AFEWDTLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ADuCM355.h"
#include "adi_types.h"

// ########################### Definitions and Macro ###################### */
#ifndef WDT_MODE_TYPE
#define WDT_MODE_TYPE
typedef enum
{
	WDT_MODE_FREE = 0u,	/* operate in free running mode */
	WDT_MODE_PERIODIC,	/* operate in periodic mode */
}WDT_MODE_Type;
#endif

#define WDT_RESTART_KEY	0xCCCC
#define WDT_IRQ_EN	(true)
#define WDT_RESET_EN	(false)
#define WDT_CLKIN_DIV2	(true)
#define WDT_CLKIN_DIV1	(false)
#define AFEWDT_OFF_FOR_PD (true)
#define AFEWDT_ALWAYS_ON (false)
#define WDT_WINDOW_DIS 0
#define WDT_WINDOW_EN 1

/* ########################### Function API ######################## */
extern uint8_t AfeWdtLd(uint16_t uTld);
extern uint16_t AfeWdtVal(void);
extern uint8_t AfeWdtCfg(WDT_MODE_Type Mod, uint8_t uPre, bool_t bInt, bool_t bClkInDiv2);
extern uint8_t AfeWdtWindowCfg(bool_t bEnable, uint16_t uMIN_LOAD);
extern uint16_t AfeWdtPowerDown(bool_t bPdStop);
extern uint8_t AfeWdtGo(bool_t bEnable);
extern uint8_t AfeWdtKick(void);
extern uint16_t AfeWdtSta(void);

#ifdef __cplusplus
}
#endif

#endif // #define





