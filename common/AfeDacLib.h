/**
 *****************************************************************************
   @file       AfeHPDacLib.h
   @brief      Set of high Power DAC peripheral functions

   @version    V0.1
	@author     ADI
	@date       September 2016
   @par Revision History:
   - V0.1, September 2016: initial version.


All files provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/
#ifndef AFEHPDACLIB_H
#define AFEHPDACLIB_H


#ifdef __cplusplus
extern "C" {
#endif

#include "ADuCM355.h"
#include "adi_types.h"


/* ########################### Definitions and Macro ###################### */
#ifndef CHAN0
#define CHAN0  (0x0)
#endif
#ifndef CHAN1
#define CHAN1  (0x1)
#endif

//Low power DAC definition
#define VBIAS12BIT_VZERO6BIT 0x0
#define VBIAS6BIT_VZERO12BIT 0x18
#define VBIAS12BIT_VZERO12BIT_SHORT	0x10
#define VBIAS6BIT_VZERO6BIT_SHORT	0x08
#define ULPMODEEN  0x20
#define ULPMODEDIS 0x20
#define LPDACSWNOR  0x0
#define LPDACSWDIAG 0x20
#define LPDACREF2P5  0
#define LPDACREFAVDD 0x4

#define C_LPDAC_REF       4095u  /* LP DAC 12-bit code corresponding to VLPDAC_REF voltage */
#define V_LPDAC_REF_mV    2200u  /* LP DAC reference voltage in mV */
#define LPDAC_C6_TO_C12    64u  /* factor to convert 6-bit code to 12-bit code = LSB6/LSB12 ratio */
#define LPDAC_C12_FROM_C6(c6) ((c6)*LPDAC_C6_TO_C12)

//High power DAC definition
#define HPDAC_ATTEN_DIV5 0x01
#define HPDAC_ATTEN_DIV1 0x00
#define HPDAC_INAMPGAIN_2 0x00
#define HPDAC_INAMPGAIN_DIV4 0x00001000
#define HPDAC_WGTYPE_DACDIR   0X00
#define HPDAC_WGTYPE_SINE  0x4
#define HPDAC_WGTYPE_TRAP  0x6

#define PWR_DOWN BITM_AFE_LPDACCON0_PWDEN
#define PWR_UP 0

/*
   Amplitude of excitation sinewave used for TIA Calibration
*/
#ifndef HPDAC_LSB
#define HPDAC_LSB (0.19753)   //809mv/(2^12-1), 1.82V reference
#endif 

/* ############################### Function API ########################## */
extern uint32_t LPDacPwrCtrl(uint32_t Chan, uint32_t Cfg);
extern uint32_t LPDacCfg(uint32_t Chan, uint32_t Mode, uint32_t OutSel, uint32_t Rng);
extern uint32_t LPDacWr(uint32_t Chan, uint32_t Dat6Bit, uint32_t Dat12Bit);
extern uint32_t LPDacBiasSet(uint32_t Chan, uint16_t Vzero, int16_t Vbias2Vzero);

extern uint32_t AfeHPDacPwrUp(bool_t Flag);    // Enables/disables AFECON.6/9/14/20/21
extern uint32_t AfeWaveGenGo(bool_t Flag);
extern uint32_t AfeHPDacCfg(uint32_t Atten, uint32_t Rate, uint32_t InAmpCfg); // Configure DACCON register

extern uint32_t AfeHPDacWgType(uint8_t Type);
extern uint32_t AfeHPDacDirWr(uint16_t Dat);   // Direct write to HP DAC DATA - HSDACDAT, WGCON[2:1]
extern uint32_t AfeHPDacSineCfg(uint32_t Freq, uint32_t Phase, int16_t Offset, uint16_t Amplitude); // WGCON[2:1], WGFCW

#ifdef __cplusplus
}
#endif

#endif // #ifndef AFEHPDACLIB_H
