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
  *@brief       get_voltage_input: get signed voltage from user through command-line interface
  *@param       none
  *@retval      -9999 to +9999 mV, voltage input for voltammetry test ranges
*/
int get_voltage_input(void);

/**
  *@brief       get_low_frequency: get lower-bound frequency from user through command line for EIS test range.  Special consideration for frequencies <1 but >0
  *             first character must be '.' if using decimal value(ex: 0.1Hz) for lower frequency bound             
  *@param       none
  *@retval      lower-bound of frequency range for impedance spectroscopy
*/
float get_frequency(void);

/**
  *@brief       get_parameter: gets generic test parameters from user over command-line interface
  *@param       dec: number of characters expected in parameter input.
  *@retval      user parameter input
*/
int get_parameter(int dec);

/**
  *@brief       get_sensor_channel: get sensor channel for test from user
  *@param       none
  *@retval      0 or 1, corresponding to ADuCM355 EC sensor channels
*/
uint16_t get_sensor_channel(void);

#endif