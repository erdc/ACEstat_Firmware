/*********************************************************************
Definitions for variables used across multiple ACEstat library files
*********************************************************************/

#ifndef ACESTAT_MISC_H
#define ACESTAT_MISC_H

/**Analog Devices ADuCM355 reference libraries*/
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

#define  UART_INBUFFER_LEN 16

extern volatile uint32_t timer_ctr;
extern volatile uint8_t tmr2_timeout;

#define USE_SINC2_FOR_TEST 0
extern volatile uint8_t  ucInCnt;
extern volatile uint32_t ucCOMIID0;
extern volatile uint32_t iNumBytesInFifo;
extern uint8_t  ucComRx;

extern uint8_t UART_buffer[UART_INBUFFER_LEN];
extern uint8_t UART_overflow_buffer[UART_INBUFFER_LEN];

extern volatile uint8_t adcRdy;
extern volatile uint8_t dftRdy;
extern volatile uint16_t ADCRAW;
extern uint8_t adcModeSel;
extern volatile uint8_t uart_flag;

/*TEMP DEFINES TEST*/
#define BITP_AFE_ADCINTIEN_VARIEN             8            /*  Variance Interrupt */
#define BITP_AFE_ADCINTIEN_MEANIEN            7            /*  Mean Interrupt */
#define BITP_AFE_ADCINTIEN_ADCDELTAFAILIEN    6            /*  Delta Interrupt */
#define BITP_AFE_ADCINTIEN_ADCMAXFAILIEN      5            /*  ADCMAX Interrupt */
#define BITP_AFE_ADCINTIEN_ADCMINFAILIEN      4            /*  ADCMIN Interrupt */
#define BITP_AFE_ADCINTIEN_TEMPRDYIEN         3            /*  Temp Sensor Interrupt */
#define BITP_AFE_ADCINTIEN_SINC2RDYIEN        2            /*  Low Pass Filter Result Interrupt */
#define BITP_AFE_ADCINTIEN_DFTRDYIEN          1            /*  DFT Result Ready Interrupt */
#define BITP_AFE_ADCINTIEN_ADCRDYIEN          0            /*  ADCDAT Ready Interrupt */
#define BITM_AFE_ADCINTIEN_VARIEN            (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  Variance Interrupt */
#define BITM_AFE_ADCINTIEN_MEANIEN           (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  Mean Interrupt */
#define BITM_AFE_ADCINTIEN_ADCDELTAFAILIEN   (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  Delta Interrupt */
#define BITM_AFE_ADCINTIEN_ADCMAXFAILIEN     (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  ADCMAX Interrupt */
#define BITM_AFE_ADCINTIEN_ADCMINFAILIEN     (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  ADCMIN Interrupt */
#define BITM_AFE_ADCINTIEN_TEMPRDYIEN        (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Temp Sensor Interrupt */
#define BITM_AFE_ADCINTIEN_SINC2RDYIEN       (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Low Pass Filter Result Interrupt */
#define BITM_AFE_ADCINTIEN_DFTRDYIEN         (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  DFT Result Ready Interrupt */
#define BITM_AFE_ADCINTIEN_ADCRDYIEN         (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  ADCDAT Ready Interrupt */

#define BITP_AFE_ADCINTSTA_VARRDY             8            /*  Variance Result Ready */
#define BITP_AFE_ADCINTSTA_MEANRDY            7            /*  Mean Result Ready */
#define BITP_AFE_ADCINTSTA_ADCDIFFERR         6            /*  ADC Delta Ready */
#define BITP_AFE_ADCINTSTA_ADCMAXERR          5            /*  ADC Maximum Value */
#define BITP_AFE_ADCINTSTA_ADCMINERR          4            /*  ADC Minimum Value */
#define BITP_AFE_ADCINTSTA_TEMPRDY            3            /*  Temp Sensor Result Ready */
#define BITP_AFE_ADCINTSTA_SINC2RDY           2            /*  Low Pass Filter Result Status */
#define BITP_AFE_ADCINTSTA_DFTRDY             1            /*  DFT Result Ready Status */
#define BITP_AFE_ADCINTSTA_ADCRDY             0            /*  ADC Result Ready Status */
#define BITM_AFE_ADCINTSTA_VARRDY            (_ADI_MSK_3(0x00000100,0x00000100UL, uint32_t  ))    /*  Variance Result Ready */
#define BITM_AFE_ADCINTSTA_MEANRDY           (_ADI_MSK_3(0x00000080,0x00000080UL, uint32_t  ))    /*  Mean Result Ready */
#define BITM_AFE_ADCINTSTA_ADCDIFFERR        (_ADI_MSK_3(0x00000040,0x00000040UL, uint32_t  ))    /*  ADC Delta Ready */
#define BITM_AFE_ADCINTSTA_ADCMAXERR         (_ADI_MSK_3(0x00000020,0x00000020UL, uint32_t  ))    /*  ADC Maximum Value */
#define BITM_AFE_ADCINTSTA_ADCMINERR         (_ADI_MSK_3(0x00000010,0x00000010UL, uint32_t  ))    /*  ADC Minimum Value */
#define BITM_AFE_ADCINTSTA_TEMPRDY           (_ADI_MSK_3(0x00000008,0x00000008UL, uint32_t  ))    /*  Temp Sensor Result Ready */
#define BITM_AFE_ADCINTSTA_SINC2RDY          (_ADI_MSK_3(0x00000004,0x00000004UL, uint32_t  ))    /*  Low Pass Filter Result Status */
#define BITM_AFE_ADCINTSTA_DFTRDY            (_ADI_MSK_3(0x00000002,0x00000002UL, uint32_t  ))    /*  DFT Result Ready Status */
#define BITM_AFE_ADCINTSTA_ADCRDY            (_ADI_MSK_3(0x00000001,0x00000001UL, uint32_t  ))    /*  ADC Result Ready Status */
/*END TEMP DEFINES*/




#endif