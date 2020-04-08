#ifndef voltammetry_H
#define voltammetry_H

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

#include "craabUtil.h" 

/*Imax = 0.9V/RGAIN*/
#define mvStepDelay 147 //delay for 5mV/S

void runCV(uint8_t szInSring[16]);
void cv_ramp_parameters(uint16_t start, uint16_t end, uint32_t RGAIN);
void runSWV(uint8_t szInSring[16]);
void sqv_dep_time(uint16_t start, uint16_t time);
void sqv_ramp_parameters(uint16_t start, uint16_t end, uint32_t RGAIN, uint16_t amplitude);

#endif