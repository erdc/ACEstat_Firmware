/*********************************************************************
Definitions for ACEstat interrupt handler functions
*********************************************************************/

#ifndef ACESTAT_INTHANDLERS_H
#define ACESTAT_INTHANDLERS_H

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

/**Declaration of variable used by interrupt handlers*/
extern uint8_t adcModeSel;
extern volatile uint8_t dftRdy; //better to convert these to flag set/clear functions?
extern volatile uint8_t adcRdy; //better to convert these to flag set/clear functions?

/***************** UART flag control for user input parsing********************/

/**
  *@brief       uart_flag_set: sets uart flag varaiable to 1 and returns 1
  *@param       none
  *@retval      1
*/
int uart_flag_set(void);  

/**
  *@brief       uart_flag_reset: sets uart flag to 0 and returns 1
  *@param       none
  *@retval      1
*/
int uart_flag_reset(void);

/***************** Interrupt handlers ********************/

/**
  *@brief       AfeAdc_Int_Handler
  *@param       none
  *@retval      none
*/
void AfeAdc_Int_Handler(void);

/**
  *@brief       GP_Tmr2_Int_Handler
  *@param       none
  *@retval      none
*/
void GP_Tmr2_Int_Handler(void);

/**
  *@brief       GP_Tmr0_Int_Handler
  *@param       none
  *@retval      none
*/
void GP_Tmr0_Int_Handler(void);


/**
  *@brief       UART_Int_Handler
  *@param       none
  *@retval      none
*/
void UART_Int_Handler(void);

#endif