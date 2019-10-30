/**
 *****************************************************************************
   @file     PwrLib.h
   @brief    Set of power Management Control functions.
   @version  V0.1
   @author   ADI
   @date     March 2016
   @par Revision History:
   - V0.1, February 2016: initial version.


All files provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/
#ifndef PWRLIB_H
#define PWRLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ADuCM355.h"
#include "adi_types.h"

typedef enum
{
   PSM_RANGBAT_GT2_75 = (0U<<BITP_PMG_IEN_RANGEBAT),
   PSM_RANGBAT_2_75_1_6 = (1U<<BITP_PMG_IEN_RANGEBAT),
}PSM_RANGBAT_Type;

#define MONITOR_VBAT_EN 0
#define MONITOR_VBAT_DIS   8
#define AFE_HIBERNATE	(2u)
#define AFE_ACTIVE	(1u)

extern uint32_t PwrCfg(uint32_t Mode,uint32_t MonVbBat,uint32_t SramRet);
extern uint32_t PwrRead(void);
extern uint32_t AfePwrCfg(uint16_t Mode);
extern uint32_t PSMIntEn(uint32_t Msk);
extern uint32_t PSMRangeCfg(PSM_RANGBAT_Type rangeBat);


#ifdef __cplusplus
}
#endif

#endif // #define PWRLIB_H
