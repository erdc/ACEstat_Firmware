/**
 *****************************************************************************
   @file     IntLib.c
   @brief    Set of External interrupt control functions.
   @version  V0.1
   @author   ADI
   @date     February 2016 
   @par Revision History:
   - V0.1, February 2016: initial version.
              

All files provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/
#ifndef INTLIB_H
#define INTLIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include <ADuCM355.h>
       
extern int EiCfg(int iEiNr,int iEnable, int iMode);
extern int EiSta(void);
extern int EiClr(int iEiNr);

//iEiNr in EiCfg()
#define EXTINT0 0x00000008 
#define EXTINT1 0x00000080 
#define EXTINT2 0x00000800 
#define EXTINT3 0x00008000
#define EXTUARTRX 0x00100000 
#define BITM_XINT_CLR_AFEIRQ (0x8)


//iEnable in EiCfg()	
#define INT_DIS	0x0	
#define INT_EN    0x1

//iMode in EiCfg()	
#define INT_RISE  0x0	
#define INT_FALL  0x1
#define INT_EDGES 0x2
#define INT_HIGH  0x3
#define INT_LOW	0x4	

#ifdef __cplusplus
}
#endif 

#endif // #define INTLIB_H
