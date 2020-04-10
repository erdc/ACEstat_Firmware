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

//Cyclic Voltammetry Functions
void runCV(uint8_t* szInSring);
void cv_ramp_parameters(uint16_t start, uint16_t mid, uint16_t end, uint32_t RGAIN);
void printCVResults(float cStart, float cMid, float cEnd, int samplesCount, int RTIA);

//Square-wave Voltammetry Functions
void runSWV(uint8_t* szInSring);
void sqv_dep_time(uint16_t start, uint16_t time);
void sqv_ramp_parameters(uint16_t start, uint16_t end, uint32_t RGAIN, uint16_t amplitude, int dep);
void printSWVResults(float cStart, float cEnd, uint16_t amp, int sampleCount, int RTIA, int dep);


#endif
