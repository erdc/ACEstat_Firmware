/**
 *****************************************************************************
   @file     CrcLib.h
   @brief    CRC library header file.
   @version  V0.2
   @author   ADI
   @date     2016/12/2
   @par Revision History:
   -  V0.1, February 2016: initial version.
   -  V0.2, July 2018: Removed AFE CRC.

All files provided by ADI, including this file, are
provided as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/

#include "ADuCM355.h"

#define ADI_TEST_CRC_POLYNOMIAL  (0x04C11DB7)
#define ADI_AFE_SEQ_CRC8_POLYNOMIAL     (0x07000000)



/*============================= MACRO =======================*/
#define CRC_CTL_NOSWAP 0
#define CRC_CTL_MSBFIRST 0
#ifndef ENABLE
#define ENABLE 1
#endif
#ifndef DISABLE
#define DISABLE 0
#endif

/*====================== FUNCTION ===========================*/
/*
   Digital part CRC peripheral
*/
extern uint32_t CrcCfg(uint32_t swap,uint32_t dir,uint32_t poly, uint32_t enable);
extern uint32_t CrcGen(uint32_t inputData);
extern uint32_t CrcSetSeed(uint32_t seed);
extern uint32_t CrcGetSeed(void);

extern uint32_t SoftwareCrc(uint32_t inputData,uint32_t poly,uint32_t seed);

