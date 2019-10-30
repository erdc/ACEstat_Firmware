/**
 *****************************************************************************
   @file       AfeAdcLib.h
   @brief      Set of ADC peripheral functions

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
#ifndef AFEADCLIBLIB_H
#define AFEADCLIBLIB_H


#ifdef __cplusplus
extern "C" {
#endif

#include "ADuCM355.h"
#include "adi_types.h"

typedef enum
{
   AfeCalReg_ADCGAINGN1 = REG_AFE_ADCGAINGN1,
   AfeCalReg_ADCOFFSETGN1 = REG_AFE_ADCOFFSETGN1,
   AfeCalReg_ADCGAINGN1P5 = REG_AFE_ADCGAINGN1P5,
   AfeCalReg_ADCOFFSETGN1P5 = REG_AFE_ADCOFFSETGN1P5,
   AfeCalReg_ADCGAINGN2 = REG_AFE_ADCGAINGN2,
   AfeCalReg_ADCOFFSETGN2 = REG_AFE_ADCOFFSETGN2,
   AfeCalReg_ADCGAINGN4 = REG_AFE_ADCGAINGN4,
   AfeCalReg_ADCOFFSETGN4 = REG_AFE_ADCOFFSETGN4,
   AfeCalReg_ADCGAINGN9 = REG_AFE_ADCGAINGN9,
   AfeCalReg_ADCOFFSETGN9 = REG_AFE_ADCOFFSETGN9,
   AfeCalReg_ADCGNLPTIA0 = REG_AFE_ADCGNLPTIA0,
   AfeCalReg_ADCGNHSTIA = REG_AFE_ADCGNHSTIA,
   AfeCalReg_ADCOFFSETHSTIA = REG_AFE_ADCOFFSETHSTIA,
   AfeCalReg_DC_CANCLEL = REG_AFE_ADCPGAOFFSETCANCEL,
   AfeCalReg_ADCOFFSETLPTIA0 = REG_AFE_ADCOFFSETLPTIA0,
   AfeCalReg_ADCOFFSETLPTIA1 = REG_AFE_ADCOFFSETLPTIA1,
   AfeCalReg_ADCGNLPTIA1 = REG_AFE_ADCGNLPTIA1,
}AfeCalReg_Type;

#ifdef EOL
#define EOL "\r\n"
#endif

#define V_ADC_REF_mV   1835u    // ADC reference is 1.82V. ADC calibration adjustment factor is 1.835/1.82 resulting in this #define value in mV */
#define V_ADC_BIAS_mV   1110    // 1.11V ADC common mode voltage reference value - measured at ADCVBIAS_CAP pin
#define C_ADC_REF      0x8000u  /* ADC code corresponding to V_ADC_REF voltage */
#define C_ADC_BIAS     0x8000u  /* ADC bias, i.e., the code corresponding to Vin=0 */

/* PGA gain values */
//const char *gnpga_val[] = { "1", "1.5", "2", "4", "9" };
//#define PRINT_GNPGA(ig) printf(#ig ",%s,%d" EOL, szValGnPga[ig], (ig));
//#define PRINT_GNPGA(g) printf(#g ",%s,%d" EOL, gnpga_val[(g)>>16], (g>>16));

extern const uint8_t uiValGnPga_x2[];
extern const char *szValGnPga[];
extern const uint32_t uiGnPga[];


// ########################### Definitions and Macro ######################
extern uint32_t AfeAdcPwrUp(uint16_t iMode);  // Configures AFECON[7]
extern uint32_t AfeAdcFiltCfg(uint16_t iSinc3, uint16_t iSinc2, uint16_t iLPF, uint16_t iAdcSampleRate);  // iSinc3 configures SINC3OSR and SINC3BYP, iSinc2 = SINC2OSR, iLPF=LPFBYPEN, iAdcSampleRate=ADC SAMPLERATE
extern uint32_t AfeAdcIntCfg(uint16_t iAdcInt); // Configure ADCINTIEN register bits
extern uint32_t AfeAdcPgaCfg(uint32_t uiGain, int16_t DcCancelInMv) ;
extern uint32_t AfeSysCfg(uint32_t powerMode, uint32_t bandwidth);
extern uint32_t AfeAdcDFTCfg(uint16_t uiHann, uint16_t uiNum, uint32_t uiDftIn); // Configure DFTCON register
extern uint32_t AfeAdcChan(uint32_t uiPinput, uint32_t uiNinput);  // uiPinput = ADCCON[12:8], uiPinput = ADCCON[5:0]

extern uint32_t AfeAdcGo(uint16_t iStart);    // Starts ADC converting - AFECON[8]
extern uint32_t AfeAdcSinc2Go(uint16_t iStart);    // Starts ADC converting - AFECON[8] and resets SINC2 filter
extern uint32_t AfeAdcIntSta(void); // read INSTA register to read DAC interrupt status register
extern uint32_t AfeAdcRd(uint16_t iChan);  // returns 32-bit ADC result. iChan selects ADCDAT, DFTREAL and DFTIMAG result, LPF Result(SINC2DAT) or Temp sensor result(TEMPSENSDAT).
extern uint32_t AfeAdcChopEn(uint32_t opt);  //chop enable/disable
extern uint32_t AfeAdcRepeatCfg(uint32_t num,uint32_t enable); //disable/enable ADC conversion for data number

extern uint32_t AfeAdcDigComp(uint16_t uiMinVal, uint16_t uiMinHysteresis, uint16_t uiMaxVal, uint16_t uiMaxHysteresis); // configure ADCMIN, ADCMINSM, ADCMAX, ADCMAXSMEN
extern uint32_t AfeAdcResultsDelta(uint32_t iDelta); // Configure ADCDELTA
extern uint32_t AfeCalRegWrite(AfeCalReg_Type CalRegAddr,uint32_t Val);// wrtie calibration register
extern uint32_t AfeAdcStatCfg(uint32_t stdev,uint32_t samples,uint32_t enable);

/*
converte 18bit sign DFT result to 32bit signed value.
*/
#define convertDftToInt(x) ((x)&0x20000)?((int32_t)(0xFFFC0000|x)) : ((int32_t)(0x0003FFFF&x));

#define SINC3OSR_5   0x0000
#define SINC3OSR_4   0x1000
#define SINC3OSR_2   0x2000
#define SINC3BYP     0x0040

#define SINC2OSR_22 0   // OSR by 22
#define SINC2OSR_44 0x100 // OSR by 44
#define SINC2OSR_89 0x200 // OSR by 89
#define SINC2OSR_178 0x300 // OSR by 178
#define SINC2OSR_267 0x400 // OSR by 267
#define SINC2OSR_533 0x500 // OSR by 533
#define SINC2OSR_640 0x600 // OSR by 640
#define SINC2OSR_667 0x700 // OSR by 667
#define SINC2OSR_800 0x800 // OSR by 800
#define SINC2OSR_889 0x900 // OSR by 889
#define SINC2OSR_1067 0xA00 // OSR by 1067
#define SINC2OSR_1333 0xB00 // OSR by 1333

#define LFPBYPEN_BYP 0x0010
#define LFPBYPEN_NOBYP	0x0000

#define ADCSAMPLERATE_800K 1
#define ADCSAMPLERATE_1600K 0

#define GNPGA_1   0
#define GNPGA_1_5 0x10000
#define GNPGA_2   0x20000
#define GNPGA_4   0x30000
#define GNPGA_9   0x40000

#define GNOFFSEL_LPTIA    0
#define GNOFFSEL_TEMPSENS 0x2000
#define GNOFFSEL_HPTIA    0x4000
#define GNOFFSEL_NOCAL    0x6000

#define DFTIN_RAWADC 0x200000
#define DFTIN_SINC3 0x100000
#define DFTIN_SINC2  0x000000

#define DFTNUM_4     0
#define DFTNUM_8     0x10
#define DFTNUM_16    0x20
#define DFTNUM_32    0x30
#define DFTNUM_64    0x40
#define DFTNUM_128   0x50
#define DFTNUM_256   0x60
#define DFTNUM_512   0x70
#define DFTNUM_1024  0x80
#define DFTNUM_2048  0x90
#define DFTNUM_4096  0xA0
#define DFTNUM_8192  0xB0
#define DFTNUM_16384 0xC0

#define MUXSELP_FLOAT    0x0
#define MUXSELP_HPTIA_P  0x1
#define MUXSELP_LPTIA0_LPF 0x2
#define MUXSELP_LPTIA1_LPF 0x3
#define MUXSELP_AIN0     0x4
#define MUXSELP_AIN1     0x5
#define MUXSELP_AIN2     0x6
#define MUXSELP_AIN3     0x7
#define MUXSELP_AVDD_2   0x8
#define MUXSELP_DVDD_2   0x9
#define MUXSELP_AVDDREG  0xA
#define MUXSELP_TEMP     0xB
#define MUXSELP_BIAS1    0xC
#define MUXSELP_VDE0     0xD
#define MUXSELP_VSE0     0xE
#define MUXSELP_VSE1     0xF
#define MUXSELP_VREF2P5  0x10
#define MUXSELP_VREF1P8DAC  0x12
#define MUXSELP_TEMPN    0x13
#define MUXSELP_AIN4     0x14
#define MUXSELP_AIN5     0x15
#define MUXSELP_AIN6     0x16
#define MUXSELP_VZERO0   0x17
#define MUXSELP_VBIAS0   0x18
#define MUXSELP_VCE0     0x19
#define MUXSELP_VRE0     0x1A
#define MUXSELP_VZERO1   0x1B
#define MUXSELP_VBIAS1   0x1C
#define MUXSELP_VCE1     0x1D
#define MUXSELP_VRE1     0x1E
#define MUXSELP_VCE0_2   0x1F
#define MUXSELP_VCE1_2   0x20
#define MUXSELP_LPTIA0_P  0x21
#define MUXSELP_LPTIA1_P  0x22
#define MUXSELP_AGND        0x23
#define MUXSELP_P_NODE      0x24
#define MUXSELP_TEMPSEN1      0x25

#define MUXSELN_FLOAT    0x000
#define MUXSELN_HPTIA_N  0x100
#define MUXSELN_LPTIA0_N 0x200
#define MUXSELN_LPTIA1_N 0x300
#define MUXSELN_AIN0     0x400
#define MUXSELN_AIN1     0x500
#define MUXSELN_AIN2     0x600
#define MUXSELN_AIN3     0x700
#define MUXSELN_VSET1P1  0x800
#define MUXSELN_TEMPN    0xB00
#define MUXSELN_AIN4     0xC00
#define MUXSELN_AIN5     0xD00
#define MUXSELN_AIN6     0xE00
#define MUXSELN_VZERO0   0x1000
#define MUXSELN_VBIAS0   0x1100
#define MUXSELN_VZERO1   0x1200
#define MUXSELN_VBIAS1   0x1300
#define MUXSELN_N_NODE   0x1400
#define MUXSELN_TEMPSEN1 0x1500

#define RAWADC     0
#define TEMPSENSOR 1
#define LPF        2
#define DFT_REAL   3
#define DFT_IMAG   4
#define AVERAGE    5

#define ADCIDLE    0
#define HANNDIS    0
#define NOINT      0
#define ADCPWRDOWN 0

#define ADC_STATISTIC_STDEV_1	(1u<<BITP_AFE_STATSCON_STDDEV)
#define ADC_STATISTIC_STDEV_4	(4u<<BITP_AFE_STATSCON_STDDEV)
#define ADC_STATISTIC_STDEV_9	(9u<<BITP_AFE_STATSCON_STDDEV)
#define ADC_STATISTIC_STDEV_16	(16u<<BITP_AFE_STATSCON_STDDEV)
#define ADC_STATISTIC_STDEV_25	(25u<<BITP_AFE_STATSCON_STDDEV)
#define ADC_STATISTIC_SAMPLE_8  (4u<<BITP_AFE_STATSCON_SAMPLENUM)
#define ADC_STATISTIC_SAMPLE_16  (3u<<BITP_AFE_STATSCON_SAMPLENUM)
#define ADC_STATISTIC_SAMPLE_32  (2u<<BITP_AFE_STATSCON_SAMPLENUM)
#define ADC_STATISTIC_SAMPLE_64  (1u<<BITP_AFE_STATSCON_SAMPLENUM)
#define ADC_STATISTIC_SAMPLE_128  (0u<<BITP_AFE_STATSCON_SAMPLENUM)
#ifdef __cplusplus
}
#endif

#endif // #define AFEADCLIBLIB_H
