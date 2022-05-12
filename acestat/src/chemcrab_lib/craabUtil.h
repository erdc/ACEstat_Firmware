#ifndef craabUtil_H
#define craabUtil_H

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

#include "ad5940.h"

/**Standard Libraries*/
#include <stdio.h>
#include <math.h>

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

/**
  *@brief       uart_get_flag: returns current value of uart flag
  *@param       none
  *@retval      flag variable, 0 or 1
*/
int uart_get_flag(void);

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

/***************** TIA setup functions ********************/

/**
  *@brief       HSRTIA_LOOKUP: get an HSRTIA register mask from list selection
  *@param       choice: list number selection for HSRTIA value, 0-7
  *@retval      HSRTIA register value for selected resistance
*/
uint16_t HSRTIA_LOOKUP(uint8_t choice);

/**
  *@brief       LPRTIA_LOOKUP: get an LPRTIA register value from list selection
  *@param       choice: list number selection for LPRTIA value, 0-25
  *@retval      LPRTIA register value for selected resistance
*/
uint16_t LPRTIA_LOOKUP(uint8_t choice);

/**
  *@brief       HSRTIA_VAL_LOOKUP: get physical resistance from HSRTIA register value
  *@param       RGAIN: HSRTIA register value
  *@retval      feedback resistance in Ohms
*/
int HSRTIA_VAL_LOOKUP(uint32_t RGAIN);

/**
  *@brief       LPRTIA_VAL_LOOKUP: get physical resistance from LPRTIA register value
  *@param       RGAIN: LPRTIA register value
  *@retval      feedback resistance in Ohms
*/
int LPRTIA_VAL_LOOKUP(uint32_t RGAIN);

/**
  *@brief       AFE_SETUP_LPTIA_LPDAC: configure the AFE registers to the necessary settings for voltammetry testing
  *@param       sensor_channel: 0 or 1
  *@retval      none
*/
void AFE_SETUP_LPTIA_LPDAC(uint8_t sensor_channel);

/**
  *@brief       hptia_setup_parameters: previously used setup function for HPTIA
  *@param       RTIA: TIA feedback gain resistance
  *@retval      none
*/
void hptia_setup_parameters(uint32_t RTIA);

/**
  *@brief       lptia_setup_parameters: previously used setup function for LPTIA
  *@param       RTIA: TIA feedback gain resistance
  *@retval      none
*/
void lptia_setup_parameters(uint32_t RTIA);

/**
  *@brief       AFE_SETUP_VOLTAMMETRY: sets up the to run voltammetry
  *@param       channel: electrode channel to use
  *@param       RTIA: TIA feedback gain resistance
  *@retval      none
*/
void AFE_SETUP_VOLTAMMETRY(uint8_t channel, uint32_t RTIA);



/***************** Command-line input parsing functions ********************/

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
float get_low_frequency(void);

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

/***************** General-purpose timer configuration functions ********************/

/**
  *@brief       gpt_config_scanrate: setup general-purpose timer 2 to control voltammetry scanrate
  *@param       mvRate: one of 10,20,30,40,50,100,150,200,250,300,350,400,450,500 mV/s.  Otherwise defaults to 50 mV/s
  *@retval      none
*/
void gpt_config_scanrate(uint16_t mvRate);

/**
  *@brief       gpt_config_simple: setup general-purpose timer 0 to have 39.4us period.  Used for equilibrium delays and chronoamperometry
  *@param       none
  *@retval      none
*/
void gpt_config_simple(void);

/**
  *@brief       reset_timer_ctr: sets timer_ctr to 0 to restart counting
  *@param       none
  *@retval      none
*/
void reset_timer_ctr(void);

/**
  *@brief       get_timer_ctr: gets the current value of timer_ctr
  *@param       none
  *@retval      timer_ctr, used to count GPT cycles for equilibrium timing
*/
uint32_t get_timer_ctr(void);

/**
  *@brief       gpt_wait_for_flag: holds voltammetry test for flag inducating GPT period has passed.  Ensures scanrate is maintained during voltammetry
  *@param       none
  *@retval      none
*/
void gpt_wait_for_flag(void);

/**
  *@brief       scanrate_lookup: gets GPT load value from pre-defined table of scanrates, used to configure GPT 
  *@param       mvRate: one of 10,20,30,40,50,100,150,200,250,300,350,400,450,500 mV/s.  Otherwise defaults to 50 mV/s
  *@retval      hex value to use as GPT LOAD to give desired voltammetry scanrate
*/
uint16_t scanrate_lookup(uint16_t mvRate);

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

