#ifndef CYCLOVOLTAMMETRY_H
#define CYCLOVOLTAMMETRY_H
#include "ADuCM355.h"
#include "ClkLib.h"
#include "UrtLib.h"
#include "GptLib.h"
#include "AfeAdcLib.h"
#include "AfeWdtLib.h"
#include "DioLib.h"
#include "RstLib.h"
#include "AfeTiaLib.h"
#include "AfeDacLib.h"
#include <stdio.h>
#include <math.h>

void sensor_setup_cv(void);

void hptia_setup(void);

void cv_ramp(void);

void cv_ramp_parameters(uint16_t start, uint16_t end, uint32_t RGAIN);

void sqv_ramp_parameters(uint16_t start, uint16_t end, uint32_t RGAIN, uint16_t amplitude);

uint16_t RTIA_LOOKUP(uint8_t choice);
void hptia_setup_parameters(uint32_t RTIA);

int RTIA_VAL_LOOKUP(uint32_t RGAIN);

#endif