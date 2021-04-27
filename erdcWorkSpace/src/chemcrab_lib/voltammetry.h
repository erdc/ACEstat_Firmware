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

//Cyclic Voltammetry Functions
void runCV(void);
void cv_ramp_parameters(uint8_t chan, uint16_t zeroV, uint16_t startV, uint16_t vertexV, uint16_t endV, uint32_t RGAIN, uint16_t sweepRate);
void printCVResults(float cZero, float cStart, float cVertex, float cEnd, int sampleCount, int RTIA);

//Square-wave Voltammetry Functions
void runSWV(void);
void sqv_ramp_parameters(uint8_t chan, uint16_t zeroV, uint16_t startV, uint16_t endV, uint32_t RGAIN, uint16_t amplitude, uint16_t step, uint16_t freq);
void printSWVResults(float cZero, float cStart, float cEnd, int sampleCount, int RTIA);

//Shared Functions
void equilibrium_delay(uint8_t chan, uint16_t start, uint16_t zero , uint16_t time);

#endif
