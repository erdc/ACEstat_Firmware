#ifndef ACESTAT_INTERFACE_H
#define ACESTAT_INTERFACE_H

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

/***************** Output printing mode control********************/

#define PRINT_MODE_RAW 0                        //print raw ADC values over UART
#define PRINT_MODE_PROCESSED 1                  //print processed values over UART

/**
  *@brief       set_printing_mode: changes global printing_mode variable to mode
  *@param       mode: PRINT_MODE_RAW or PRINT_MODE_PROCESSED
  *@retval      none
*/
void set_printing_mode(uint8_t mode);

/**
  *@brief       get_printing_mode: returns the value of printing_mode
  *@param       none
  *@retval      current value of printing_mode
*/
uint8_t get_printing_mode(void);

/***************** Command-line input parsing functions ********************/

/**
  *@brief       return_uart_buffer: returns pointer to UART buffer array
  *@param       none
  *@retval      pointer to UART buffer
*/
uint8_t* return_uart_buffer(void);

/**
  *@brief       get_frequency: get a float parameter for IES frequency input
  *@param       none
  *@retval      float representing the frequency to be used for EIS test
*/
float get_frequency(void);

/**
  *@brief       get_parameter: gets generic test parameters from user over command-line interface
  *@param       none
  *@retval      user parameter input as integer
*/
int get_parameter();

/**
  *@brief       get_sensor_channel: get sensor channel for test from user
  *@param       none
  *@retval      0 or 1, corresponding to ADuCM355 EC sensor channels
*/
uint16_t get_sensor_channel(void);

#endif