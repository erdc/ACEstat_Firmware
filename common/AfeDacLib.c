/**
 *****************************************************************************
   @file       AfeHPDacLib.c
   @brief      Set of high Power DAC peripheral and wave generator functions

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

#include "AfeDacLib.h"

/*==========================================================================*/
/*                                LOW POWER DAC                             */
/*==========================================================================*/

 /**
   @brief uint32_t LPDacPwrCtrl(uint32_t Chan, uint32_t Cfg)
         ==========Powers up or down selected VDAC
        Need to write to call LPDacSwitchCfg() after this function
   @param Chan :{CHAN0, CHAN1}
      - CHAN0 for LPDAC0 channel
      - CHAN1 for LPDAC1 channel
   @param Cfg :{PWR_UP,PWR_DOWN}   \n
      - PWR_DOWN or BITM_AFE_LPDACCON0_PWDEN to power down VDAC channel
      - PWR_UP to Power up LP VDAC channel
   @return new ULPDACCON.
**/

uint32_t LPDacPwrCtrl(uint32_t Chan, uint32_t Cfg)
{
   uint16_t tmp;
   if(Chan ==0)  // ULP DAC0 Channel
   {
     tmp = (pADI_AFE->LPDACCON0)&(~BITM_AFE_LPDACCON0_PWDEN);
     tmp |= Cfg;
     pADI_AFE->LPDACCON0 = tmp|0x1;
     return pADI_AFE->LPDACCON0;
   }
   else          // ULP DAC1 Channel
   {
     tmp = (pADI_AFE->LPDACCON1)&(~BITM_AFE_LPDACCON1_PWDEN);
     tmp |= Cfg;
     pADI_AFE->LPDACCON1 = tmp|0x1;
     return pADI_AFE->LPDACCON1;
   }
}

/**
	@brief uint32_t LPDacCfg(uint32_t Chan, uint32_t Mode, uint32_t OutSel, uint32_t Rng)
			==========Sets the output range of LP DAC.
   @param Chan :{CHAN0, CHAN1}
      - CHAN0 for LPDAC0 channel
      - CHAN1 for LPDAC1 channel
   @param Mode :{LPDACSWNOR, LPDACSWDIAG}
      - 0 or LPDACSWNOR to configure normal operation
      - 0x20 or LPDACSWDIAG to configure output switches for diagnostics mode
   @param OutSel :{VBIAS12BIT_VZERO6BIT, VBIAS6BIT_VZERO12BIT,VBIAS12BIT_VZERO12BIT_SHORT}
      - 0 or VBIAS12BIT_VZERO6BIT to set VBIAS with 12-bit precision, and VZERO with 6-bit
      - 0x18 or VBIAS6BIT_VZERO12BIT to set VZERO with 12-bit precision, and VBIAS with 6-bit
      - 0x10 or VBIAS12BIT_VZERO12BIT_SHORT to set VBIAS with 12-bit precision and short VZERO to VBIAS
   @param Rng :{LPDACREF2P5, LPDACREFAVDD}
      - 0 or LPDACREF2P5 to config LP 2.5V uint32_ternal reference as LP VDAC reference.
      - 0x4 or LPDACREFAVDD to use AVDD as LP VDAC reference.

	@return new ULPDACCON.
**/

uint32_t LPDacCfg(uint32_t Chan, uint32_t Mode, uint32_t OutSel, uint32_t Rng)
{
  if(Chan ==0)  // ULP DAC0 Channel
   {
     pADI_AFE->LPDACCON0 = (Mode|OutSel|Rng|0x1);
     return pADI_AFE->LPDACCON0;
   }
   else          // ULP DAC1 Channel
   {
     pADI_AFE->LPDACCON1 = (Mode|OutSel|Rng|0x1);
     return pADI_AFE->LPDACCON1;
   }
}

/**
   @brief uint32_t LPDacWr(uint32_t Chan, uint32_t Dat6Bit, uint32_t Dat12Bit)
         ==========Writes the DAC value.
   @param Chan :{CHAN0, CHAN1}
      - CHAN0 for LPDAC0 channel
      - CHAN1 for LPDAC1 channel
   @param Dat6Bit :{}
      - DACIN6, value between 0 to 0x3F
   @param Dat12Bit :{}
      - DACIN12, value between 0 to 0xFFF
   @return DAC data.
**/
uint32_t LPDacWr(uint32_t Chan, uint32_t Dat6Bit, uint32_t Dat12Bit)
{
  if(Chan ==0)  // ULP DAC0 Channel
   {
     pADI_AFE->LPDACDAT0 = ((Dat6Bit<<12) |Dat12Bit);
     return pADI_AFE->LPDACDAT0;
   }
   else          // ULP DAC1 Channel
   {
     pADI_AFE->LPDACDAT1 = ((Dat6Bit<<12) |Dat12Bit);
     return pADI_AFE->LPDACDAT1;
   }
}

/*==========================================================================*/
/*                                HIGH POWER DAC                            */
/*==========================================================================*/

/**
   @brief uint32_t AfeHPDacPwrUp(bool_t Flag);
          ======Power up or Power down high power(speed) DAC, Enables/disables AFECON.6/9/14/20/21
   @param Flag :{true,false}
      - 0 or false, power down High power Dac
      - 1 or true,   power up High power Dac
   @return register AFECON.
*/
uint32_t AfeHPDacPwrUp(bool_t Flag)
{
   uint32_t reg;
   reg = pADI_AFE->AFECON;
   if(Flag>0) /*power up high power dac*/
   {
      /*power up aldo, reference, DAC, INAMP,Excitatioin buffer*/
      reg |= BITM_AFE_AFECON_EXBUFEN|BITM_AFE_AFECON_INAMPEN|BITM_AFE_AFECON_DACREFEN|BITM_AFE_AFECON_DACEN;
      reg &= (~BITM_AFE_AFECON_HPREFDIS);
      pADI_AFE->AFECON = reg;
   }
   else  /*power down high power dac*/
   {
      /*power down, reference, wave generator*/
      pADI_AFE->AFECON &= (~(BITM_AFE_AFECON_EXBUFEN|BITM_AFE_AFECON_INAMPEN|BITM_AFE_AFECON_DACREFEN|BITM_AFE_AFECON_DACEN));
   }
   return pADI_AFE->AFECON;
}

/**
   @brief uint32_t AfeWaveGenGo(bool_t Flag);
          ======Start or stop waveform generator, including trap/sine/dac directly writting
   @param Flag :{true,false}
      - 0 or false, stop waveform generator
      - 1 or true,   start waveform generator
   @return register AFECON.
*/
uint32_t AfeWaveGenGo(bool_t Flag)
{
   if(Flag>0)
      pADI_AFE->AFECON |= BITM_AFE_AFECON_WAVEGENEN;
   else
      pADI_AFE->AFECON &= (~BITM_AFE_AFECON_WAVEGENEN);

   return pADI_AFE->AFECON;
}

/**
   @brief uint32_t AfeHPDacCfg(uint32_t Atten, uint32_t Rate, uint32_t InAmpCfg)
          ======set attenuator, dac update rate and RCF, INAMP
   @param Atten :{HPDAC_ATTEN_DIV5,HPDAC_ATTEN_DIV1}
      - 1 or HPDAC_ATTEN_DIV5, DAC attenuator enabled at 1/5
      - 0 or HPDAC_ATTEN_DIV1, DAC attenuator disabled
   @param iRate :{7-255}
      - dac update rate = 16MHz/iRate
   @param InAmpCfg :{HPDAC_INAMPGAIN_2,HPDAC_INAMPGAIN_DIV4}
      - 0 or HPDAC_INAMPGAIN_2, select gain of excitation INAMP, gain = 2
      - 0x00001000 or HPDAC_INAMPGAIN_DIV4, select gain of excitation INAMP, gain = 1/4
   @return register HSDACCON.
   @note Don't try combine iFiltCfg, only one bit can be set and at least one bit should be set
*/
uint32_t AfeHPDacCfg(uint32_t Atten, uint32_t Rate, uint32_t InAmpCfg)
{
   uint32_t reg;
   reg = Atten|(Rate<<BITP_AFE_HSDACCON_RATE)|InAmpCfg;
   //pADI_AFE->PMBW |= ENUM_AFE_PMBW_RCFOW;	/*OVer written RCF's bandwidth, enable AFE_HSDACCON_RATE control*/
   pADI_AFE->HSDACCON = reg;
   return pADI_AFE->HSDACCON;
}

/**
   @brief uint32_t AfeHPDacWgType(uint8_t Type)
          ======select wave type for wave generator
   @param Type :{HPDAC_WGTYPE_DACDIR,HPDAC_WGTYPE_SINE,HPDAC_WGTYPE_TRAP}
      - HPDAC_WGTYPE_DACDIR, direct write to DAC
      - HPDAC_WGTYPE_SINE, sinusoid
      - HPDAC_WGTYPE_TRAP, Trapezoid
   @return WGCON.
*/
uint32_t AfeHPDacWgType(uint8_t Type)
{
   uint32_t reg;
   reg = pADI_AFE->WGCON&(~BITM_AFE_WGCON_TYPESEL);
   reg |=  Type;
   pADI_AFE->WGCON = reg;
   return pADI_AFE->WGCON;
}

/**
   @brief uint32_t AfeHPDacSineCfg(uint32_t Freq, uint32_t Phase, int16_t Offset, uint16_t Amplitude)
          ======set frequency, pahse, offset and amplitude of sine wave. select sine type of WGCON
   @param Freq :{}
      - Sinusoid generator frequency control word, 20bit
   @param Phase :{}
      - Sinusoid phase offset, 20bit
   @param Offset :{}
      - Sinusoid offset, added to the waveform generator, 12bit
   @param Amplitude :{}
      - DAC output voltage, 11bit
   @return 1.
*/
uint32_t AfeHPDacSineCfg(uint32_t Freq, uint32_t Phase, int16_t Offset, uint16_t Amplitude)
{
   pADI_AFE->WGFCW = Freq;
   pADI_AFE->WGPHASE = Phase;
   pADI_AFE->WGOFFSET = Offset;
   pADI_AFE->WGAMPLITUDE = Amplitude;
   return 1;
}


/**
   @brief uint32_t AfeHPDacDirWr(uint16_t Dat);
          ======DAC code, written directly to high speed 12bit DAC
@param Dat :{0-4095}
      - 12bit DAC code, write directly to high speed DAC
   @return HSDACDAT.
*/
uint32_t AfeHPDacDirWr(uint16_t Dat)
{
   pADI_AFE->HSDACDAT = Dat;
   return pADI_AFE->HSDACDAT;
}
