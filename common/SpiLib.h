/**
 *****************************************************************************
   @file     SpiLib.h
   @brief    Set of SPI peripheral functions.
   
   @internal   001 @endinternal
   @version  V1.0
   @author   ADI
   @date     April 2015 
   @par Revision History:
   - V0.1, March 2013: initial version. 
   - V0.2, April 2013: Renamed SpiCountRd to SpiCount and changed functionality
   - V1.0, April 2015: Changed library format

All files provided by ADI, including this file, are
provided as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/

#ifndef SPILIB_H
#define SPILIB_H

#ifdef __cplusplus
extern "C" {
#endif 

#include <ADuCM355.h>

extern int SpiSta(ADI_SPI_TypeDef *pSPI);
extern int SpiRx(ADI_SPI_TypeDef *pSPI);
extern int SpiTx(ADI_SPI_TypeDef *pSPI, int iTx);
extern int SpiBaud(ADI_SPI_TypeDef *pSPI, int iClkDiv);
extern int SpiCfg(ADI_SPI_TypeDef *pSPI, int iFifoSize, int iMasterEn, int iConfig);
extern int SpiIenEn(ADI_SPI_TypeDef *pSPI,int iIntType);   
extern int SpiIenDis(ADI_SPI_TypeDef *pSPI,int iIntType);
extern int SpiFifoFlush(ADI_SPI_TypeDef *pSPI, int iTxFlush, int iRxFlush);
extern int SpiTxFifoFlush(ADI_SPI_TypeDef *pSPI, int iTxFlush);
extern int SpiRxFifoFlush(ADI_SPI_TypeDef *pSPI, int iRxFlush);
extern int SpiFifoSta(ADI_SPI_TypeDef *pSPI);
extern int SpiDma(ADI_SPI_TypeDef *pSPI, int iDmaRxSel, int iDmaTxSel, int iDmaEn);
extern int SpiCount(ADI_SPI_TypeDef *pSPI, int iSpiCnt, int iWr, int iFrameContEn);
extern int SpiRdCmd(ADI_SPI_TypeDef *pSPI, int iCfg, int iTxBytes, int iCmdEn);
extern int SpiFlowCtl(ADI_SPI_TypeDef *pSPI, int iCfg, int iRdBurstSize, int iWaitTime);
extern int SpiCsCfg(ADI_SPI_TypeDef *pSPI, int iCsCfg, int iCSoverRide);


#define CS0   0x1
#define CS1   0x2
#define CS2   0x4
#define CS3   0x8

#define FORCE_CS_HIGH   0x1
#define FORCE_CS_LOW   0x2

#ifdef __cplusplus
}
#endif 

#endif // #define SPILIB_H
