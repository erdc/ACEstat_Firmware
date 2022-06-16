#ifndef ACESTAT_ADC_H
#define ACESTAT_ADC_H

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

/***************** ADC control and conversion ********************/

#define MAX_BUFFER_LENGTH 16000
#define ADCSTART pADI_AFE->AFECON |= BITM_AFE_AFECON_ADCCONVEN
#define ADCSTOP  pADI_AFE->AFECON &= (~BITM_AFE_AFECON_ADCCONVEN)
extern uint8_t adcModeSel;
extern volatile uint8_t dftRdy; //better to convert these to flag functions similar to uart_flag
extern volatile uint8_t adcRdy; //better to convert these to flag functions similar to uart_flag

/**
  *@brief       adc_voltage_setup_RE: configure the ADC to measure voltage from reference electrode to 1.1V internal reference capacitor
  *@param       sensor_channel: 0 or 1
  *@retval      none
*/
void adc_voltage_setup_RE(uint8_t sensor_channel);

/**
  *@brief       adc_voltage_setup_SE: configure the ADC to measure voltage from sensing(AKA working) electrode to 1.1V internal reference capacitor
  *@param       sensor_channel: 0 or 1
  *@retval      none
*/
void adc_voltage_setup_SE(uint8_t sensor_channel);

/**
  *@brief       adc_voltage_setup_AIN: configure the ADC to measure voltage between analog input pins
  *@param       sensor_channel: 0 for AIN1-AIN0 , 1 for AIN3-AIN2, 2 for AIN6-AIN5
  *@retval      none
*/
void adc_voltage_setup_AIN(uint8_t analog_channel);

/**
  *@brief       adc_current_setup_lptia: configure the ADC to measure current using the + and -terminal of the LPTIA
  *@param       sensor_channel: 0 or 1
  *@retval      none
*/
void adc_current_setup_lptia(uint8_t sensor_channel);

/**
  *@brief       calc_current_lptia: converts adc-scale representation of current measured with LPTIA to micro-amps value
  *@param       adc_data: adc-scale representation of current measured using LPTIA
  *@param       RGAIN: LPTIA feedback gain resistance
  *@param       RLOAD: LPTIA input load resistance
  *@retval      measured current in micro-amps
*/
float calc_current_lptia(uint16_t adc_data, 
                         int RGAIN, 
                         int RLOAD);

/**
  *@brief       calc_voltage_adc: converts adc-scale measured voltage to milli-volts
  *@param       adc_data: measured voltage in adc-scale
  *@retval      measured voltage in milli-volts
*/
float calc_voltage_adc(uint16_t adc_data);

/**
  *@brief       return_adc_buffer: returns pointer to szADCSamples, the MAX_BUFFER_LENGTH-element array for storing ADC data
  *@param       none
  *@retval      pointer to ADC data buffer array
*/
uint16_t* return_adc_buffer(void);

/**
  *@brief       get_adc_val: returns current value of ADCDAT register
  *@param       none
  *@retval      ADCRAW, equal to ADCDAT register value
*/
uint16_t get_adc_val(void);

/**
  *@brief       reset_adc_flag: sets the global adcRdy flag to 0
  *@param       none
  *@retval      none
*/
void reset_adc_flag(void);


/**
  *@brief       set_adc_flag: sets the flobal adcRdy flag to 1
  *@param       none
  *@retval      none
*/
void set_adc_flag(void);

/**
  *@brief       set_adc_mode: sets the adc to use regular or DFT mode
  *@param       mode: 0 for regular mode, 1 for DFT mode
  *@retval      none
*/
void set_adc_mode(uint8_t mode);

/**
  *@brief       oversample_adc: software-defined adc oversampling to increase effective bit resolution.  
  *@param       mode:   
  *@param       sensor_channel: 0 or 1
  *@param       oversample_rate: oversampling rate, 16 gives +2 effective bits precision
  *@retval      none
*/
int oversample_adc(int mode, 
                   uint8_t sensor_channel, 
                   uint16_t oversample_rate);
                   
/**Macros for defining oversample mode and ADC mux positions*/
#define MODE_LPTIA 0                    //Use as input to oversample_adc(mode)
#define MODE_VRE 1                      //Use as input to oversample_adc(mode)
#define MODE_VZERO 2                    //Use as input to oversample_adc(mode)
#define MODE_AIN 3                      //Use as input to oversample_adc(mode)
#define ELECTRODE_CHAN0 0               //Use as input to oversample_adc(sensor_channel)   
#define ELECTRODE_CHAN1 1               //Use as input to oversample_adc(sensor_channel) 
#define ANALOG_CHAN0 2                  //Use as input to oversample_adc(sensor_channel)
#define ANALOG_CHAN1 3                  //Use as input to oversample_adc(sensor_channel)
#define ANALOG_CHAN2 4                  //Use as input to oversample_adc(sensor_channel)
#define ADC_OVERSAMPLE_RATE 16          //Oversampling rate for software-defined ADC oversampling
#define SKIP_RATE 2                     //Store data in output buffer every SKIP_RATE DAC increments
    
/**
  *@brief       adc_to_voltage: converts adc-scale measurements to voltage, in milli-volts
  *@param       adc_data: adc-scale measured voltage
  *@retval      voltage in millivolts
*/
float adc_to_voltage(float adc_data);

/**
  *@brief       adc_to_current: converts adc-scale measurements to current, in micro-amps
  *@param       adc_data: adc-scale measured current
  *@param       RTIA: LPTIA feedback gain resistance
  *@retval      current in micro-amps
*/
float adc_to_current(float adcVal, 
                     int RTIA);

/**
  *@brief       voltammetry_mov_avg: testing a basic moving average filter for squarewave voltametry data
  *@param       width: moving average window width
  *@param       arr: pointer to adc samples array
  *@param       pos: current position in *arr
  *@param       sample_count: length of *arr
  *@param       RTIA: LPTIA feedback gain resistance
  *@retval      adjusted value for measurement at pos based on local average
*/
float swv_mov_avg(int width, 
                   uint16_t *arr, 
                   int pos,
                   uint16_t sample_count,
                   int RTIA);
                                           
/**
  *@brief       cv_mov_avg: testing a basic moving average filter for cyclic voltametry data
  *@param       width: moving average window width
  *@param       arr: pointer to adc samples array
  *@param       pos: current position in *arr
  *@param       sample_count: length of *arr
  *@param       RTIA: LPTIA feedback gain resistance
  *@retval      adjusted value for measurement at pos based on local average
*/
float cv_mov_avg(int width, 
                 uint16_t *arr, 
                 int pos, 
                 uint16_t sample_count, 
                 int RTIA);

/***************** DAC control and conversion ********************/

/**
  *@brief       mv_to_DAC: convert voltage in milli-volts to DAC-scale value
  *@param       mV: voltage in millivolts
  *@param       nBits: DAC channel bits, 6 or 12 for ADuCM355
  *@retval      DAC-scale representation of mV
*/
uint16_t mV_to_DAC(uint16_t mV,
                   uint8_t nBits);

/**
  *@brief       DAC_to_mV: convert DAC-scale value to milli-volts
  *@param       DAC: DAC-scale representation of measured voltage
  *@param       nBits: DAC channel bits, 6 or 12 for ADuCM355
  *@retval      millivolts equivalent of DAC-scale value
*/
float DAC_to_mV(float DAC,
                uint8_t nBits);

/**
  *@brief       adjust_DAC: measure 6-bit DAC channel and adjust 12-bit channel value to compensate for lower precision of 6-bit channel
  *@param       vZero: 6-bit DAC channel voltage
  *@param       vStart: 12-bit DAC channel voltage
  *@param       vDiffTarget: desired differntial voltage from vZero-vStart
  *@param       sensor_channel: 0 or 1
  *@retval      required amount (in millivolts) to shift 12-bit channel to compensate for low 6-bit channel precision 
*/
int adjust_DAC(uint16_t vZero,
               uint16_t vStart,
               int vDiffTarget,
               uint8_t sensor_channel);

/***************** System shutdown control ********************/

/**
  *@brief       turn_off_afe_power_things_down: power down DAC/TIA/ADC/PA/etc... and open all switches
  *@param       none
  *@retval      none
*/
void turn_off_afe_power_things_down(void);

/**
  *@brief       power_down_ADC: shutdown the ADC
  *@param       none
  *@retval      none
*/
void power_down_ADC(void);

#endif

