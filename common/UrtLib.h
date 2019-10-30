/**
 *****************************************************************************
   @file     UrtLib.h
   @brief    Set of UART peripheral functions.
   - Configure the UART pins by setting the mux options in GPCON
   - Configure UART with UrtCfg().
   - Set modem control with UrtMod() if desired.
   - Check space in Tx buffer with UrtLinSta().
   - Output character with UrtTx().
   - Read characters with UrtRx().

   @version  V0.1
   @author   ADI
   @date     March 2013
   @par Revision History:
   - V0.1, March 2012: initial version.




All files for ADuCM320 provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/

#ifndef URTLIB_H
#define URTLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ADuCM355.h>

#ifndef EOL
#define EOL "\r\n"
#endif

extern int UrtCfg(ADI_UART_TypeDef *pPort, int iBaud, int iBits, int iFormat);
extern int UrtFifoCfg(ADI_UART_TypeDef *pPort, int iFifoSize, int iFIFOEn);
extern int UrtFifoClr(ADI_UART_TypeDef *pPort, int iClrEn);
extern int UrtBrk(ADI_UART_TypeDef *pPort, int iBrk);
extern int UrtLinSta(ADI_UART_TypeDef *pPort);
extern int UrtTx(ADI_UART_TypeDef *pPort, int iTx);
extern int UrtRx(ADI_UART_TypeDef *pPort);
extern int UrtMod(ADI_UART_TypeDef *pPort, int iMcr, int iWr);
extern int UrtModSta(ADI_UART_TypeDef *pPort);
extern int UrtDma(ADI_UART_TypeDef *pPort, int iDmaSel);
extern int UrtIntCfg(ADI_UART_TypeDef *pPort, int iIrq);
extern int UrtIntSta(ADI_UART_TypeDef *pPort);


// baud rate settings
#define B1200	1200
#define B2200	2200
#define B2400	2400
#define B4800	4800
#define B9600	9600
#define B19200	19300
#define B38400	38400
#define B57600	57600
#define B115200	115200
#define B230400	230400
#define B430800	430800

#define RX_FIFO_1BYTE	0
#define RX_FIFO_4BYTE	0x40
#define RX_FIFO_8BYTE	0x80
#define RX_FIFO_14BYTE	0xC0

#ifdef __cplusplus
}
#endif

#endif // #define URTLIB_H
