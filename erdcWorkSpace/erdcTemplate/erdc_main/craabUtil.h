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

#define ADCSTART pADI_AFE->AFECON |= BITM_AFE_AFECON_ADCCONVEN  //start ADC conversion
#define ADCSTOP  pADI_AFE->AFECON &= (~BITM_AFE_AFECON_ADCCONVEN)  //stop ADC conversion

void adcCurrentSetup_hptia(void);
float calcCurrent_hptia(uint16_t DAT, int RGAIN);

uint16_t pollReadADC(void);

void adcCurrentSetup_lptia(void);
float calcADCVolt(uint16_t DAT);
float calcCurrent_lptia(uint16_t DAT, int RGAIN, int RLOAD);
void powerDownADC(void);

void turn_off_afe_power_things_down(void);


#endif

