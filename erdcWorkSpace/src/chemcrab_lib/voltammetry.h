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

//Cyclic Voltammetry(CV) 
void runCV(void);
void cvSetVoltages(int relative_voltages[3], uint16_t DACVoltages[4], uint8_t channel);
void cvEquilibriumDelay(uint16_t chan, uint16_t DACVoltages[4], uint16_t time);
void cvExcitationSignal(uint16_t chan, uint16_t DACvoltages[4], uint32_t RGAIN, uint16_t sweepRate);
void printCVResults(float cZero, float cStart, float cVertex, float cEnd, int sampleCount, int RTIA, float vZeroMeasured);

//Square-wave Voltammetry(SWV) 
void runSWV(void);
void swvSetVoltages(int relative_voltages[3], uint16_t DACVoltages[3], uint8_t channel);
void swvEquilibriumDelay(uint16_t chan, uint16_t DACVoltages[3], uint16_t amp, uint16_t time);
void swvExcitationSignal(uint16_t chan, uint16_t DACvoltages[3], uint32_t RGAIN, uint16_t amplitude, uint16_t step, uint16_t freq);
void printSWVResults(float cZero, float cStart, float cEnd, int sampleCount, int RTIA, float vZeroMeasured);

//Cyclic Square-wave Voltammetry(CSWV) 
void runCSWV(void);
void cswvSetVoltages(int relative_voltages[4], uint16_t DACVoltages[4], uint8_t channel);
void cswvEquilibriumDelay(uint16_t chan, uint16_t DACVoltages[4], uint16_t amp, uint16_t time);
void cswvExcitationSignal(uint16_t chan, uint16_t DACvoltages[4], uint32_t RGAIN, uint16_t amplitude, uint16_t step, uint16_t freq);
void printCSWVResults(float cZero, float cStart, float cVertex, float cEnd, int sampleCount, int RTIA, float vZeroMeasured);

//Chrono-Amperometry (CA)
void runCA(void);
void caSetVoltages(int vStep, uint16_t DACVoltages[2], uint8_t channel);
void caExcitationSignal(uint16_t chan, uint16_t DACVoltages[2], uint16_t length, uint16_t delay, uint32_t RGAIN, int diag);
void printCAResults(float cZero, float cStep, int length, int RTIA, int sampleCount, float timeStep, float vZeroMeasured);
#endif
