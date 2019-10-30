/**
 *****************************************************************************
   @file     RstLib.h
   @brief    Set of Reset Control functions.
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
#ifndef RSTLIB_H
#define RSTLIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include "ADuCM355.h"
#include "DioLib.h"

#define ALLON_RSTCON_KEY (0x12EA)
#define AFEDIESTA   (*((uint32_t *)(0x40007008)))

#define BITM_ALLON_RSTCON_BYPMMRRST	(0x01)
#define BITM_ALLON_RSTCON_BYPWDTRST	(0x02)
#define BITM_ALLON_RSTCON_BYPPINRST	(0x04)
#define ALLCON_RSTSTA_CLEAR_ALL		(0xFF)


extern int ReadRstSta(void);
extern int ClearRstSta(int iStaClr );
extern uint8_t AfeRstSta(void);
extern uint32_t AfeDieSta(void);


//Reset status.
#define RST_NONE	0	


#ifdef __cplusplus
}
#endif 

#endif // #define RSTLIB_H
