/**
 *****************************************************************************
   @file       AfeAdcLib.c
   @brief      Set of ADC peripheral functions

   @version    V0.3
	@author     ADI
	@date       November 2018
   @par Revision History:
   - V0.1, September 2016: initial version.
   - V0.2, September 2017:
         - Swapped ADCFILTERCON[4] bit description in AfeAdcFiltCfg() headers
            @param iLPF :{LFPBYPEN_BYP,LFPBYPEN_NOBYP}
   - V0.3, November 2018, Fixed bug in AfeAdcIntSta(void) 


All files provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/
#include "AfeAdcLib.h"

/* PGA gain values */
const uint8_t uiValGnPga_x2[] = { 2, 3, 4, 8, 18 }; /* doubled to be int */
const char *szValGnPga[] = { "1", "1.5", "2", "4", "9" };
const uint32_t uiGnPga[] = { GNPGA_1, GNPGA_1_5, GNPGA_2, GNPGA_4, GNPGA_9 };

/**
	@brief uint32_t AfeAdcPwrUp(uint16_t iMode)
			========== Power up/down Afe ADC
	@param iMode :{ADCPWRDOWN, BITM_AFE_AFECON_ADCEN}
		- AFECON[7]
		- 0 or ADCPWRDOWN to power down the ADC.
		- 0x80 or BITM_AFE_AFECON_ADCEN.
	@return 1.
**/
uint32_t AfeAdcPwrUp(uint16_t iMode)  // Configures AFECON[7]
{
  uint32_t i = 0;

  i = (pADI_AFE->AFECON & (~BITM_AFE_AFECON_ADCEN));
  i |= iMode;
  pADI_AFE->AFECON = i;

  return i;
}

/*
	@brief uint32_t AfeSysCfg(uint32_t powerMode, uint32_t bandwidth)
		=========== FUNCTION Description
   @param powerMode:{ENUM_AFE_PMBW_LP,ENUM_AFE_PMBW_HP}
      -ENUM_AFE_PMBW_LP, set high speed DAC and ADC in low power mode
      -ENUM_AFE_PMBW_HP, set high speed DAC and ADC in high power mode
   @param bandwidth: {ENUM_AFE_PMBW_BW50,ENUM_AFE_PMBW_BW100,ENUM_AFE_PMBW_BW250}
      -ENUM_AFE_PMBW_BW50, system bandwidth 50 KHz
      -ENUM_AFE_PMBW_BW100, system bandwidth 100 KHz
      -ENUM_AFE_PMBW_BW250, system bandwidth 250 KHz
	@return none
**/
uint32_t AfeSysCfg(uint32_t powerMode, uint32_t bandwidth)
{
   pADI_AFE->PMBW = powerMode|bandwidth;
   return 1;
}

/**
	@brief uint32_t AfeAdcFiltCfg(uint16_t iSinc3, uint16_t iSinc2, uint16_t iLPF, uint16_t iAdcSampleRate)
			========== Configures ADC update rate via ADC filter options
	@param iSinc3 :{SINC3OSR_5,SINC3OSR_4,SINC3OSR_2,SINC3BYP}
		- ADCFILTERCON[13:12], SINC3OSR
		- SINC3OSR_5, ADC udpate rate(sinc3 filter output) = AdcSampleRate/5
      - SINC3OSR_4, ADC udpate rate(sinc3 filter output) = AdcSampleRate/4
      - SINC3OSR_2, ADC udpate rate(sinc3 filter output) = AdcSampleRate/2
      - SINC3BYP, ADC udpate rate(sinc3 filter output) = AdcSampleRate
	@param iSinc2 :{SINC2OSR_22,SINC2OSR_44,SINC2OSR_89,SINC2OSR_178,SINC2OSR_267,SINC2OSR_533,SINC2OSR_640,SINC2OSR_667,SINC2OSR_800,SINC2OSR_889,SINC2OSR_1067,SINC2OSR_1333}
		- ADCFILTERCON[11:8], SINC2OSR
		- 0 or SINC2OSR_22 for OSR value of 22
      - 0x100 or SINC2OSR_44 for OSR value of 44
		- 0x200 or SINC2OSR_89 for OSR value of 89
      - 0x300 or SINC2OSR_178 for OSR value of 178
      - 0x400 or SINC2OSR_267 for OSR value of 267
      - 0x500 or SINC2OSR_533 for OSR value of 533
      - 0x600 or SINC2OSR_640 for OSR value of 640
      - 0x700 or SINC2OSR_667 for OSR value of 667
      - 0x800 or SINC2OSR_800 for OSR value of 800
      - 0x900 or SINC2OSR_889 for OSR value of 889
      - 0xA00 or SINC2OSR_1067 for OSR value of 1067
      - 0xB00 or SINC2OSR_1333 for OSR value of 1333
@param iLPF :{LFPBYPEN_BYP,LFPBYPEN_NOBYP}
		- ADCFILTERCON[4], LPFBYPEN
		- 0x0000 or LFPBYPEN_NOBYP to enable low pass filter
		- 0x0010 or LFPBYPEN_BYP to bypass the low pass filter
@param iAdcSampleRate :{ADCSAMPLERATE_1600K,ADCSAMPLERATE_800K}
		- ADCFILTERCON[0], ADCSAMPLERATE
		- 0 or ADCSAMPLERATE_1600K to select 1.6MSPS ADC raw update rate
      - 1 or ADCSAMPLERATE_800K to select 800KSPS ADC raw update rate
	@return ADCFILTERCON.
**/
uint32_t AfeAdcFiltCfg(uint16_t iSinc3, uint16_t iSinc2, uint16_t iLPF, uint16_t iAdcSampleRate)  // iSinc3 configures SINC3OSR and SINC3BYP, iSinc2 = SINC2OSR, iLPF=LPFBYPEN, iAdcSampleRate=ADC SAMPLERATE
{
    uint32_t reg;
    reg = pADI_AFE->ADCFILTERCON;
    reg &= ~(BITM_AFE_ADCFILTERCON_SINC3OSR|BITM_AFE_ADCFILTERCON_SINC2OSR|   \
         BITM_AFE_ADCFILTERCON_SINC3BYP|BITM_AFE_ADCFILTERCON_LPFBYPEN|BITM_AFE_ADCFILTERCON_ADCCLK);
    reg |= iSinc3|iSinc2|iLPF|iAdcSampleRate;
    pADI_AFE->ADCFILTERCON = reg;
    return pADI_AFE->ADCFILTERCON;
}

/**
	@brief uint32_t AfeAdcIntCfg(uint16_t iAdcInt)
			========== Power up/down Afe ADC
	@param iAdcInt :{NOINT|BITM_AFE_ADCINTIEN_ADCRDYIEN|BITM_AFE_ADCINTIEN_DFTRDYIEN|
                   BITM_AFE_ADCINTIEN_SINC2RDYIEN|BITM_AFE_ADCINTIEN_TEMPRDYIEN|
                  BITM_AFE_ADCINTIEN_ADCMINFAILIEN|BITM_AFE_ADCINTIEN_ADCMAXFAILIEN|
                  BITM_AFE_ADCINTIEN_ADCDELTAFAILIEN}
      - ADCINTIEN[6:0]
		- 0 or NOINT, no interrupt enabled.
		- 0x1 or BITM_AFE_ADCINTIEN_ADCRDYIEN for ADC result ready interrupt enable.
		- 0x2 or BITM_AFE_ADCINTIEN_DFTRDYIEN for DFT result ready interrupt enable.
		- 0x4 or BITM_AFE_ADCINTIEN_SINC2RDYIEN for LPF result ready interrupt enable.
		- 0x8 or BITM_AFE_ADCINTIEN_TEMPRDYIEN for temp sensor result ready interrupt enable.
		- 0x10 or BITM_AFE_ADCINTIEN_ADCMINFAILIEN for ADC MIN value fail interrupt enable.
      - 0x20 or BITM_AFE_ADCINTIEN_ADCMAXFAILIEN for  ADC MAX value fail interrupt enable.
      - 0x40 or BITM_AFE_ADCINTIEN_ADCDELTAFAILIEN for  ADC DELTA value fail interrupt enable.
	@return pADI_AFE->ADCINTIEN.
**/
uint32_t AfeAdcIntCfg(uint16_t iAdcInt)    // Configure ADCINTIEN register bits
{
  pADI_AFE->ADCINTIEN = iAdcInt;
   return pADI_AFE->ADCINTIEN;
}

/**
	@brief uint32_t AfeAdcPgaCfg(uint16_t uiGain, int16_t DcCancelInMv)
			========== PGA configuration
   @param uiGain :{GNPGA_1, GNPGA_1_5, GNPGA_2, GNPGA_4, GNPGA_9}
      - ADCCON[18:16]
      - 0 or GNPGA_1 for Gain =1
      - 0x10000 or GNPGA_1_5 for Gain =1.5
      - 0x20000 or GNPGA_2 for Gain =2
      - 0x30000 or GNPGA_4 for Gain =4
      - 0x40000 or GNPGA_9 for Gain =9
    @param DcCancelInMv:{}
      - 0 for normal operation of PGA input stage. no DC cancel
      - other value, range +/-1100 mV,
   e.x. to cancel 100mV in signal, and if PGA gain = 4, set DcCancelInMv = 400
	@return pADI_AFE->ADCCON.
**/
uint32_t AfeAdcPgaCfg(uint32_t uiGain, int16_t DcCancelInMv) //uiAAFCfg= ADCCON[21:20], uiGain = ADCCON[18:16],uiOffsetSel =ADCCON[15]
{
   uint32_t i = 0;
   uint16_t dacCode;

   i= (pADI_AFE->ADCCON & (~(BITM_AFE_ADCCON_GNPGA|BITM_AFE_ADCCON_GNOFSELPGA)));  // Mask relevant bits of ADCCON
   i |= uiGain;
   if ((pADI_AFE->PMBW & 0x1) == 0)
      pADI_AFE->ADCBUFCON = 0x005f3d04;
   if ((pADI_AFE->PMBW & 0x1) == 1)
      pADI_AFE->ADCBUFCON = 0x005f3d0F;
   if(DcCancelInMv != 0)
   {
      i |= BITM_AFE_ADCCON_GNOFSELPGA;
      dacCode = 2048 + (DcCancelInMv*4095*2+1)/4400;
      /*enable DC cancel for ADC, cancel voltage come from ULPDAC1*/
      pADI_AFE->LPDACCON1 = 0x0001;
      if(dacCode<4096)
         pADI_AFE->LPDACDAT1 = (32<<12) + dacCode;
      pADI_AFE->ADCBUFCON &= ~BITM_AFE_ADCBUFCON_AMPDIS;
   }
   pADI_AFE->ADCCON = i;
   return pADI_AFE->ADCCON;
}

/**
	@brief uint32_t AfeAdcDFTCfg(uint16_t uiHann, uint16_t uiNum, uint32_t uiDftIn)
			========== Configures DFT hardware accelerator block
	@param iHann :{HANNDIS,BITM_AFE_DFTCON_HANNINGEN}
      - DFTCON[0]
		- 0 or HANNDISto disable Hanning window
      - 1 or BITM_AFE_DFTCON_HANNINGEN to enable Hanning window
    @param uiNum:{DFTNUM_4,DFTNUM_8,DFTNUM_16,DFTNUM_32,DFTNUM_64,DFTNUM_128,
                 DFTNUM_256,DFTNUM_512,DFTNUM_1024,DFTNUM_2048,DFTNUM_4096,
                 DFTNUM_8192, DFTNUM_16384}
      - DFTCON[7:4]
      - 0 or DFTNUM_4 to select 4x samples for the DFT calculation
      - 0x10 or DFTNUM_8 to select 8x samples for the DFT calculation
      - 0x20 or DFTNUM_16 to select 16x samples for the DFT calculation
      - 0x30 or DFTNUM_32 to select 32x samples for the DFT calculation
      - 0x40 or DFTNUM_64 to select 64x samples for the DFT calculation
      - 0x50 or DFTNUM_128 to select 128x samples for the DFT calculation
      - 0x60 or DFTNUM_256 to select 256x samples for the DFT calculation
      - 0x70 or DFTNUM_512 to select 512x samples for the DFT calculation
      - 0x80 or DFTNUM_1024 to select 1024x samples for the DFT calculation
      - 0x90 or DFTNUM_2048 to select 2048x samples for the DFT calculation
      - 0xA0 or DFTNUM_4096 to select 4096x samples for the DFT calculation
      - 0xB0 or DFTNUM_8192 to select 8192x samples for the DFT calculation
      - 0xC0 or DFTNUM_16384 to select 16384x samples for the DFT calculation
    @param uiDftIn:{DFTIN_SINC3,DFTIN_SINC2,DFTIN_RAWADC}
      - DFTCON[21:20]
      - 0x200000 or DFTIN_RAWADC to select the RAW ADC output directly as the DFT input
      - 0x100000 or DFTIN_SINC3 to select the SINC3, decimated output as the DFT input
      - DFTIN_SINC2 to select the SINC2 output as the DFT input
   @return pADI_AFE->DFTCON.
**/
uint32_t AfeAdcDFTCfg(uint16_t uiHann, uint16_t uiNum, uint32_t uiDftIn) // Configure DFTCON register
{
   pADI_AFE->DFTCON = (uiHann|uiNum|uiDftIn);
   return pADI_AFE->DFTCON;
}

/**
	@brief uint32_t AfeAdcChan(uint32_t uiPinput, uint32_t uiNinput)
			========== Select ADC positive and Negative inputs from MUX selection
	@param uiPinput :{MUXSELP_FLOAT, MUXSELP_HPTIA_P,MUXSELP_LPTIA0_P,MUXSELP_LPTIA1_P,
                    MUXSELP_AIN0,MUXSELP_AIN1,MUXSELP_AIN2,MUXSELP_AIN3,MUXSELP_AVDD_2,MUXSELP_DVDD_2,
                    MUXSELP_AVDDREG,MUXSELP_TEMP,MUXSELP_BIAS1,MUXSELP_VDE0,
                    MUXSELP_VSE0,MUXSELP_VSE1,MUXSELP_VREF2P5,MUXSELP_VREF1P8ADC,
                    MUXSELP_VREF1P8DAC,MUXSELP_TEMPN,MUXSELP_AIN4,MUXSELP_AIN5,
                    MUXSELP_AIN6,MUXSELP_VZERO0,MUXSELP_VBIAS0,MUXSELP_VCE0,
                    MUXSELP_VRE0,MUXSELP_VZERO1,MUXSELP_VBIAS1,MUXSELP_VCE1,
                    MUXSELP_VRE1,MUXSELP_VCE0_2,MUXSELP_VCE1_2,MUXSELP_LPTIA0_LPF
                    MUXSELP_LPTIA1_LPF }
       - ADCCON[5:0]
		- 0 or MUXSELP_FLOAT
      - 1 or MUXSELP_HPTIA_P for High power TIA P output
    @param uiNinput:{MUXSELN_FLOAT,MUXSELN_HPTIA_N,MUXSELN_LPTIA0_N,
                     MUXSELN_LPTIA1_N,MUXSELN_AIN0,MUXSELN_AIN1,MUXSELN_AIN2,
                     MUXSELN_AIN3,MUXSELN_VSET1P1,MUXSELN_AGND,MUXSELN_TEMPN,
                     MUXSELN_AIN4,MUXSELN_AIN5,MUXSELN_AIN6,MUXSELN_VZERO0,
                     MUXSELN_VBIAS0,MUXSELN_VZERO1,MUXSELN_VBIAS1 }
      - ADCCON[12:8]

	@return pADI_AFE->ADCCON.
**/
uint32_t AfeAdcChan(uint32_t uiPinput, uint32_t uiNinput) // uiPinput = ADCCON[12:8], uiPinput = ADCCON[5:0]
{
  uint32_t i = 0;
  i = (pADI_AFE->ADCCON & 0xFFFFE000);   // Mask bits 12 to 0
  i |= (uiPinput|uiNinput);
  pADI_AFE->ADCCON = i;
  return pADI_AFE->ADCCON;
}

/**
	@brief uint32_t AfeAdcGo(uint16_t iStart)
			========== Starts ADC converting or returns it to idle mode
	@param iStart :{ADCIDLE,BITM_AFE_AFECON_ADCCONVEN }
       - AFECON[8]
		- 0 or ADCIDLE for ADC Idle mode
      - 0x100 or BITM_AFE_AFECON_ADCCONVEN to start ADC converting
	@return pADI_AFE->AFECON.
**/
uint32_t AfeAdcGo(uint16_t iStart)    // Starts ADC converting - AFECON[8]
{
   uint32_t i = 0;

   i = (pADI_AFE->AFECON & (~BITM_AFE_AFECON_ADCCONVEN));
   pADI_AFE->AFECON &= (~BITM_AFE_AFECON_ADCCONVEN);      // Clear conversion bit to restart SINC3 filter
   i |= iStart;
   pADI_AFE->AFECON = i;
   return pADI_AFE->AFECON;
}
/**
	@brief uint32_t AfeAdcSinc2Go(uint16_t iStart)
			========== Starts ADC converting or returns it to idle mode and resets SINC2 filter
	@param iStart :{ADCIDLE,BITM_AFE_AFECON_ADCCONVEN }
       - AFECON[8]
		- 0 or ADCIDLE for ADC Idle mode
      - 0x100 or BITM_AFE_AFECON_ADCCONVEN to start ADC converting
	@return pADI_AFE->AFECON.
**/
uint32_t AfeAdcSinc2Go(uint16_t iStart)    // Starts ADC converting - AFECON[8] and resets SINC2 filter
{
   uint32_t i = 0;
   
   pADI_AFE->AFECON &= (~(BITM_AFE_AFECON_SINC2EN));      // Clear SINC2 Filter bit to reset it
   i = (pADI_AFE->AFECON & (~BITM_AFE_AFECON_ADCCONVEN));
   pADI_AFE->AFECON &= (~BITM_AFE_AFECON_ADCCONVEN);      // Clear conversion bit to restart SINC3 filter
   i |= (iStart | BITM_AFE_AFECON_SINC2EN);
   pADI_AFE->AFECON |= BITM_AFE_AFECON_SINC2EN;           // Re-enable SINC2 filter
   pADI_AFE->AFECON = i;
   return pADI_AFE->AFECON;
}

/**
	@brief uint32_t AfeAdcIntSta(void)
			========== returns ADC Interrupt status register
	@return pADI_AFE->ADCINTSTA.
**/
uint32_t AfeAdcIntSta(void)
{
  return pADI_AFE->ADCINTSTA;
}

/**
	@brief uint32_t AfeAdcRd(uint16_t iChan)
			========== read ADC result for selected ADC output
	@param iChan :{RAWADC,TEMPSENSOR,LPF,DFT_REAL,DFT_IMAG,AVERAGE}

		- 0 or RAWADC for ADCDAT result
		- 1 or TEMPSENSOR for TEMPSENSDAT result
		- 2 or LPF for SINC2DAT result
		- 3 or DFT_REAL for DFTREAL result
		- 4 or DFT_IMAG for DFTIMAG result
		- 5 or AVERAGE for STATSMEAN result
	@return selected ADC data result.
**/
uint32_t AfeAdcRd(uint16_t iChan)  // returns 32-bit ADC result. iChan selects ADCDAT, DFTREAL and DFTIMAG result, LPF Result(SINC2DAT) or Temp sensor result(TEMPSENSDAT), AVERAGE for STATSMEAN
{
  uint32_t i = 0;
  switch (iChan)
  {
     case RAWADC:
       i = pADI_AFE->ADCDAT;
       break;
     case TEMPSENSOR:
       i = pADI_AFE->TEMPSENSDAT;
       break;
     case LPF:
       i = pADI_AFE->SINC2DAT;
       break;
     case DFT_REAL:
       i = pADI_AFE->DFTREAL;
       break;
     case DFT_IMAG:
       i = pADI_AFE->DFTIMAG;
       break;
     case AVERAGE:
       i = pADI_AFE->STATSMEAN;
       break;
     default:
        i = pADI_AFE->ADCDAT;
       break;
  }
   return i;
}

/**
	@brief uint32_t AfeAdcChopEn(uint32_t opt)
			========== disable/enable chop of ADC
	@param opt: {0,1}
      - 1,  enable ADC chop
      - 0,  disable ADC chop
	@return 1.
**/
uint32_t AfeAdcChopEn(uint32_t opt)
{
   uint32_t reg;
   if(!opt) //disable chop
   {
      reg = (pADI_AFE->ADCBUFCON&0xFFFFFFF0)|0x0000000F;
   }
   else  //enable chop
   {
      reg = (pADI_AFE->ADCBUFCON&0xFFFFFFF0)|0x00000004;
   }
   pADI_AFE->ADCBUFCON  = reg;
   return 1;
}


/**
	@brief uint32_t AfeAdcRepeatCfg(uint32_t num,uint32_t enable)
			========== ADC stop after specified number data has been sampled
	@param num: {0-255}
      - num, numbers that ADC conversion will repeat
   @param enable:{0,1}
      - 0, disable ADC repeat function
      - 1, enable ADC repeat function
	@return pADI_AFE->REPEATADCCNV.
**/
uint32_t AfeAdcRepeatCfg(uint32_t num,uint32_t enable)
{
   pADI_AFE->REPEATADCCNV = (num<<BITP_AFE_REPEATADCCNV_NUM)|enable;
   return pADI_AFE->REPEATADCCNV;
}

/**
	@brief uint32_t AfeCalRegWrite(AfeCalReg_Type CalRegAddr,uint32_t Val)
			========== Write Calibration register which are protected by Key.
	@param CalRegAddr :{AfeCalReg_ADCGAINGN1|AfeCalReg_ADCOFFSETGN1|AfeCalReg_ADCGAINGN1P5|AfeCalReg_ADCGAINGN2|
                       AfeCalReg_ADCGAINGN4|AfeCalReg_ADCGAINGN9 }
		- AfeCalReg_ADCGAINGN1 registers need to write to.
	@param Val :{0 to 0xFFFFFFFF}
		- Val value written to.
	@return 1.
**/
uint32_t AfeCalRegWrite(AfeCalReg_Type CalRegAddr,uint32_t Val)
{
   pADI_AFE->CALDATLOCK = 0xDE87A5AF;
   *(uint32_t*)CalRegAddr = Val;
   pADI_AFE->CALDATLOCK = 0;
   return 1;
}

/**
	@brief uint32_t AfeAdcDigComp(uint16_t uiMinVal, uint16_t uiMinHysteresis, uint16_t uiMaxVal, uint16_t uiMaxHysteresis)
			========== Setup ADC digital comparator features - optional function
	@param uiMinVal :{0 to 0xFFFF}
		- uiMinVal
   - ADCMIN.[15:0]
	@param uiMinHysteresis :{0 to 0xFFFF}
		- uiMinVal
   - ADCMINSM.[15:0]
	@param uiMaxVal :{0 to 0xFFFF}
		- uiMaxVal
   - ADCMAX.[15:0]
	@param uiMaxHysteresis :{0 to 0xFFFF}
		- uiMaxHysteresis
   - ADCMAXSMEN.[15:0]
	@return 1.
**/
uint32_t AfeAdcDigComp(uint16_t uiMinVal, uint16_t uiMinHysteresis, uint16_t uiMaxVal, uint16_t uiMaxHysteresis) // configure ADCMIN, ADCMINSM, ADCMAX, ADCMAXSMEN
{
   pADI_AFE->ADCMIN = uiMinVal;                // Setup Minimum trip point for ADCMINERR interrupt source
   pADI_AFE->ADCMINSM = uiMinHysteresis;       // Setup hysteresis value for ADCMINERR interrupt source
   pADI_AFE->ADCMAX = uiMaxVal;                // Setup Maximum trip point for ADCMAXERR interrupt source
   pADI_AFE->ADCMAXSMEN = uiMaxHysteresis;     // Setup hysteresis value for ADCMAXERR interrupt source
   return 1;
}

/**
	@brief uint32_t AfeAdcResultsDelta(uint32_t iDelta)
			========== Configures ADC DELTA register.
      A delta interrupt is generated if the difference between 2 consecutive ADC samples is greater than value in this register
	@param iDelta :{0 - 0xFFFF }
       - .
	@return pADI_AFE->ADCDELTA
**/
uint32_t AfeAdcResultsDelta(uint32_t iDelta) // Configure ADCDELTA
{
   pADI_AFE->ADCDELTA = iDelta;
   return pADI_AFE->ADCDELTA;
}

/**
 	@brief uint32_t AfeAdcStatCfg(uint32_t stdev,uint32_t samples,uint32_t enable)
		=========== configures ADC statistic module
	@param stdev:{ADC_STATISTIC_STDEV_1,ADC_STATISTIC_STDEV_4,ADC_STATISTIC_STDEV_9,ADC_STATISTIC_STDEV_16,ADC_STATISTIC_STDEV_25}
		- ADC_STATISTIC_STDEV_1, ignore ADC data when |ADCcode-Average of sample|>1*stdev of sample
		- ADC_STATISTIC_STDEV_4, ignore ADC data when |ADCcode-Average of sample|>2*stdev of sample
		- ADC_STATISTIC_STDEV_9, ignore ADC data when |ADCcode-Average of sample|>3*stdev of sample
		- ADC_STATISTIC_STDEV_16, ignore ADC data when |ADCcode-Average of sample|>4*stdev of sample
		- ADC_STATISTIC_STDEV_25, ignore ADC data when |ADCcode-Average of sample|>5*stdev of sample
	@param samples:{ADC_STATISTIC_SAMPLE_8,ADC_STATISTIC_SAMPLE_16,ADC_STATISTIC_SAMPLE_32,ADC_STATISTIC_SAMPLE_64,ADC_STATISTIC_SAMPLE_128}
		- ADC_STATISTIC_SAMPLE_8, do statistic calculation after 8 samples
		- ADC_STATISTIC_SAMPLE_16, do statistic calculation after 16 samples
		- ADC_STATISTIC_SAMPLE_32, do statistic calculation after 16 samples
		- ADC_STATISTIC_SAMPLE_64, do statistic calculation after 16 samples
		- ADC_STATISTIC_SAMPLE_128, do statistic calculation after 16 samples
	@param enable:{ENABLE,DISABLE}
		- ENABLE, enable statistic mudule
		- DISABLE, disable statistic module
   @return pADI_AFE->STATSCON
**/
uint32_t AfeAdcStatCfg(uint32_t stdev,uint32_t samples,uint32_t enable)
{
	if(enable>0)
		pADI_AFE->STATSCON = stdev|samples|enable;
	else
		pADI_AFE->STATSCON &= (~BITM_AFE_STATSCON_STATSEN);

	return pADI_AFE->STATSCON ;
}
