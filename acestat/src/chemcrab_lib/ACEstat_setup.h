#ifndef ACESTAT_SETUP_H
#define ACESTAT_SETUP_H

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
#include "ad5940.h"

/***************** ACEstat test mode definitions for top-level API control ********************/
#define MODE_CV_DEBUG   0
#define MODE_CV         1
#define MODE_SWV        2
#define MODE_CSWV       3
#define MODE_CA         4
#define MODE_EIS        5
#define MODE_OCP        6

/***************** UART and Clock setup ********************/

/**
  *@brief       ClockInit: configures system clock to run from high-frequency oscillator 
  *@param       none
  *@retval      none
*/
void ClockInit(void);

/**
  *@brief       UartInit: configures UART to run at 9600 baudrate on pins p0.10 and p0.11
  *@param       none
  *@retval      none
*/
void UartInit(void);

/**
  *@brief       return_uart_buffer: returns pointer to UART buffer array
  *@param       none
  *@retval      pointer to UART buffer
*/
uint8_t* return_uart_buffer(void);

#define  UART_INBUFFER_LEN 16

#endif