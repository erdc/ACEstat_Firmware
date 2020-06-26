#ifndef craabUtil_H
#define craabUtil_H

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
#include <stdio.h>
#include <math.h>
#include "M355_ECSns_EIS.h"
#include "M355_ECSns_DCTest.h"

#define ADCSTART pADI_AFE->AFECON |= BITM_AFE_AFECON_ADCCONVEN  //start ADC conversion
#define ADCSTOP  pADI_AFE->AFECON &= (~BITM_AFE_AFECON_ADCCONVEN)  //stop ADC conversion

//UART/CLOCK SETUP FUNCTIONS
void ClockInit(void);
void UartInit(void);
void UART_Int_Handler(void);
uint8_t* return_uart_buffer(void);
#define  UART_INBUFFER_LEN 16

/*FLAG CONTROL*/
int flag_set(void);
int flag_reset(void);
int get_flag(void);
/*END FLAG CONTROL*/

/*ADC Mode Control*/
extern uint8_t adcModeSel;
extern volatile uint8_t dftRdy;

//KEITH'S ORIGINAL UTIL FUNCTIONS
void adcCurrentSetup_hptia(void);
float calcCurrent_hptia(uint16_t DAT, int RGAIN);
void adcCurrentSetup_lptia(void);
float calcADCVolt(uint16_t DAT);
float calcCurrent_lptia(uint16_t DAT, int RGAIN, int RLOAD);
void powerDownADC(void);
void turn_off_afe_power_things_down(void);

#define MAX_BUFFER_LENGTH 16000
uint16_t* return_adc_buffer(void);

//IMPORTED electrochemistry functions
void sensor_setup_cv(void);
void hptia_setup(void);

uint16_t RTIA_LOOKUP(uint8_t choice);
void hptia_setup_parameters(uint32_t RTIA);
int RTIA_VAL_LOOKUP(uint32_t RGAIN);
//Retrieves voltammetry parameters from UART input
uint16_t getParameter(int dec);

//Used to configure voltammetry sweeprates using digital timers
void GptCfgVoltammetry(uint16_t mvRate);
void GptWaitForFlag(void);
uint16_t sweeprateLookup(uint16_t mvRate);
uint16_t getAdcVal(void);
void setAdcMode(uint8_t mode);

void AfeAdc_Int_Handler(void);
void GP_Tmr2_Int_Handler(void);

#endif

