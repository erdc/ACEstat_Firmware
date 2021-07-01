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

//Cyclic Voltammetry(CV) Functions
void runCV(void);
void set_CV_voltages(int relative_voltages[3], uint16_t absolute_voltages[4]);
void cv_ramp_parameters(uint16_t chan, int startV, int vertexV, int endV, uint32_t RGAIN, uint16_t sweepRate);
void printCVResults(float cZero, float cStart, float cVertex, float cEnd, int sampleCount, int RTIA);
void equilibrium_delay_CV(uint16_t chan, int startV, int vertexV, int endV, uint16_t time);

//Square-wave Voltammetry(SWV) Functions
void runSWV(void);
void set_SWV_voltages(int relative_voltages[3], uint16_t absolute_voltages[3]);
void swv_ramp_parameters(uint16_t chan, int startV, int endV, uint32_t RGAIN, uint16_t amplitude, uint16_t step, uint16_t freq);
void printSWVResults(float cZero, float cStart, float cEnd, int sampleCount, int RTIA);
void equilibrium_delay_SWV(uint16_t chan, int startV, int endV, uint16_t amp, uint16_t time);

//Cyclic Square-wave Voltammetry(CSWV) Functions
void runCSWV(void);
void set_CSWV_voltages(int relative_voltages[4], uint16_t absolute_voltages[4]);
void cswv_ramp_parameters(uint16_t chan, int startV, int vertexV, int endV, uint32_t RGAIN, uint16_t amplitude, uint16_t step, uint16_t freq);
void printCSWVResults(float cZero, float cStart, float cVertex, float cEnd, int sampleCount, int RTIA);
void equilibrium_delay_CSWV(uint16_t chan, int startV, int vertexV, int endV, uint16_t amp, uint16_t time);

#endif
