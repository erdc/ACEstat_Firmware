#include "AdcCal.h"
#include <stdio.h>
#include <string.h>

float fVrefDiv = 0.0;                         // Used to reflect PGA gain value - set by ADCCON[18:16]


  int32_t i32Temp = 0;
  uint32_t u32NewCalVal = 0;
  int32_t iTargetAdcCode = 0;
  float fTempLsbCalc = 0;
  float fTemp1 = 0;
  float fPgaDiv = 0;
  float fGainAdjRequired, fGainAdj = 0;
  float fGainAdjustLsb = 0.000061035; 
  int32_t iGainError = 0;

/**
   @brief uint32_t  AdcOffsetCalInit(uint32_t u32Gain, uint8_t u8PwrMode)
         ==========Initializes ADC for Offset calibration using required PGA Gain setting in LP/HP Mode - voltage channels only
   @param u32Gain :{GNPGA_1, GNPGA_1_5, GNPGA_2, GNPGA_4, GNPGA_9}
      - ADCCON[18:16]
      - 0 or GNPGA_1 for Gain =1
      - 0x10000 or GNPGA_1_5 for Gain =1.5
      - 0x20000 or GNPGA_2 for Gain =2
      - 0x30000 or GNPGA_4 for Gain =4
      - 0x40000 or GNPGA_9 for Gain =9
   @param u8PwrMode :{0, 1}
      - 0 for Low Power mode
      - 1 for high Power mode
   @Description: Inputs PGA Gain setting
      - Selects internal 1.1V reference as the ADC's P and N inputs (internal short)
      - Slows ADC output rate to minimuze noise for calibration measurement
      - Configures the input buffers for LP or HP mode recommended settings.
      - reads existing factory calibration for selected PGA Gain setting
   @return ADC Offset calibration for required PGA gain.
**/
uint32_t  AdcOffsetCalInit(uint32_t u32Gain, uint8_t u8PwrMode)
{
   uint32_t u32OffsetCal = 0;

   AfeAdcChan(MUXSELP_BIAS1,MUXSELN_VSET1P1);  // Select 1.11V VREF as P and N input to ADC

   if (u8PwrMode == 0)                         // LP Mode?
   {
      pADI_AFE->ADCBUFCON = 0x005F3D04;        // Set ADC input buffers/PGA for recommended chop configuration for LP Mode
      AfeAdcFiltCfg(SINC3OSR_4,                   // Enable 2KSPS update rate - enable SINC2 to reduce noise
   //   AfeAdcFiltCfg(SINC3OSR_5,                   // Enable 2KSPS update rate - enable SINC2 to reduce noise
                 SINC2OSR_533,
                 LFPBYPEN_NOBYP,
                 ADCSAMPLERATE_800K);
      
   //   AfeAdcFiltCfg(SINC3OSR_4,SINC2OSR_178,LFPBYPEN_BYP,ADCSAMPLERATE_800K); //200k SPS
   }
   else                                        // HP Mode
   {
      pADI_AFE->ADCBUFCON = 0x005F3D0F;        // Set ADC input buffers/PGA for recommended chop configuration for HP Mode
      AfeAdcFiltCfg(SINC3OSR_4,SINC2OSR_533,LFPBYPEN_NOBYP,ADCSAMPLERATE_1600K); //bypass LPF, 400KHz ADC update rate
   }
   AfeAdcIntCfg(
       BITM_AFE_ADCINTIEN_SINC2RDYIEN);   // Select the SINC2 filter output as ADC interrupt source
   pADI_AFE->AFECON |= 0x10000;                // Enable SINC2 digital filter option on ADC output
   AfeAdcPgaCfg(u32Gain,0);                       // Configure ADC for selected gain setting

   switch (u32Gain)
   {
      case GNPGA_1:
        u32OffsetCal = pADI_AFE->ADCOFFSETGN1;
        break;
      case GNPGA_1_5:
        u32OffsetCal = pADI_AFE->ADCOFFSETGN1P5;
        break;
      case GNPGA_2:
        u32OffsetCal = pADI_AFE->ADCOFFSETGN2;
        break;
      case GNPGA_4:
        u32OffsetCal = pADI_AFE->ADCOFFSETGN4;
        break;
      case GNPGA_9:
        u32OffsetCal = pADI_AFE->ADCOFFSETGN9;
        break;
      default:
        u32OffsetCal = pADI_AFE->ADCOFFSETGN1;
        break;
   }
  return u32OffsetCal;
}

/**
   @brief uint32_t  AdcGainCalInit(uint32_t u32Gain, uint8_t u8PwrMode)
         ==========Initializes ADC for Gain calibration using required PGA Gain setting in LP/HP Mode
   @param u32Gain :{GNPGA_1, GNPGA_1_5, GNPGA_2, GNPGA_4, GNPGA_9}
      - ADCCON[18:16]
      - 0 or GNPGA_1 for Gain =1
      - 0x10000 or GNPGA_1_5 for Gain =1.5
      - 0x20000 or GNPGA_2 for Gain =2
      - 0x30000 or GNPGA_4 for Gain =4
      - 0x40000 or GNPGA_9 for Gain =9
   @param u8PwrMode :{0, 1}
      - 0 for Low Power mode
      - 1 for high Power mode
   @Description: Inputs PGA Gain setting

   @return ADC Gain calibration for required PGA gain.
**/
uint32_t  AdcGainCalInit(uint32_t u32Gain, uint8_t u8PwrMode)
{
   uint32_t u32GainCal = 0;

 //  AfeAdcChan(MUXSELP_VREF1P8DAC,              // Select 1.82V HSDAC Reference as P input, V1.11V internal reference as N inputs to the ADC
 //             MUXSELN_VSET1P1);


   if (u8PwrMode == 0)                         // LP Mode?
   {
      pADI_AFE->ADCBUFCON = 0x005F3D04;        // Set ADC input buffers/PGA for recommended chop configuration for LP Mode
      AfeAdcFiltCfg(SINC3OSR_4,                   // Enable 2KSPS update rate - enable SINC2 to reduce noise
                 SINC2OSR_533,
                 LFPBYPEN_NOBYP,
                 ADCSAMPLERATE_800K); 
      
   //   AfeAdcFiltCfg(SINC3OSR_4,SINC2OSR_178,LFPBYPEN_BYP,ADCSAMPLERATE_800K); //200k SPS
   }
   else                                        // HP Mode
   {
      pADI_AFE->ADCBUFCON = 0x005F3D0F;        // Set ADC input buffers/PGA for recommended chop configuration for HP Mode
      AfeAdcFiltCfg(SINC3OSR_4,SINC2OSR_533,LFPBYPEN_NOBYP,ADCSAMPLERATE_1600K); //bypass LPF, 400KHz ADC update rate
   }
   AfeAdcIntCfg(
       BITM_AFE_ADCINTIEN_SINC2RDYIEN);   // Select the SINC2 filter output as ADC interrupt source
   pADI_AFE->AFECON |= 0x10000;                // Enable SINC2 digital filter option on ADC output
   AfeAdcPgaCfg(u32Gain,0);                       // Configure ADC for selected gain setting

   switch (u32Gain)
   {
      case GNPGA_1:
        u32GainCal = pADI_AFE->ADCGAINGN1;
        break;
      case GNPGA_1_5:
        u32GainCal = pADI_AFE->ADCGAINGN1P5;
        break;
      case GNPGA_2:
        u32GainCal = pADI_AFE->ADCGAINGN2;
        break;       
      case GNPGA_4:
        u32GainCal = pADI_AFE->ADCGAINGN4;
        break;    
      case GNPGA_9:
        u32GainCal = pADI_AFE->ADCGAINGN9;
        break; 
      default:
        u32GainCal = pADI_AFE->ADCGAINGN1;
        break;
   }
  return u32GainCal;
}

uint32_t AdcGainCalLP(uint8_t u8Gain)
{
     uint32_t u32GainCal = 0;

  return u32GainCal;
}

uint32_t ReadGainCal(uint32_t u32Gain)
{
  uint32_t u32GainCal = 0;
  
   switch (u32Gain)
   {
      case GNPGA_1:
        u32GainCal = pADI_AFE->ADCGAINGN1;
        break;
      case GNPGA_1_5:
        u32GainCal = pADI_AFE->ADCGAINGN1P5;
        break;
      case GNPGA_2:
        u32GainCal = pADI_AFE->ADCGAINGN2;
        break;       
      case GNPGA_4:
        u32GainCal = pADI_AFE->ADCGAINGN4;
        break;    
      case GNPGA_9:
        u32GainCal = pADI_AFE->ADCGAINGN9;
        break; 
      default:
        u32GainCal = pADI_AFE->ADCGAINGN1;
        break;
   }
  return u32GainCal;
}


/**
   @brief uint32_t  AdcOffsetCalAdjust(uint32_t u32Gain, uint32_t u32FacOffset, int32_t iAdcDat)
         ==========Function to generate new ADC offset calibration values based on measured voltage and existing Offset cal value
   @param u8Gain :{GNPGA_1, GNPGA_1_5, GNPGA_2, GNPGA_4, GNPGA_9}
      - ADCCON[18:16]
      - 0 or GNPGA_1 for Gain =1
      - 0x10000 or GNPGA_1_5 for Gain =1.5
      - 0x20000 or GNPGA_2 for Gain =2
      - 0x30000 or GNPGA_4 for Gain =4
      - 0x40000 or GNPGA_9 for Gain =9
   @param u32FacOffset :{0 - 0x7FFF}
      - .
   @param iAdcDat:{0 - 0xFFFFFFFF}
      - Value based on SINC2DAT, value between 0 to 0xFFFFFFFF
   @Description: Inputs PGA Gain setting
      - Takes ADC measurement for internal short using PGA gain setting
      - Based on this, it calculates how much the existing offset register needs to be changed by
      - ADC Offset calibration register is a 15-bit, signed value
      - ADC offset correction for Voltage channel represented as a 2s complement number.
      - 0x3FFF	+4095.75. Maximum Positive Offset calibration value
      -  0x0001	+0.25. Minimum Positive Offset calibration value
      -  0x0000	0. No offset adjustment
      -  0x7FFF	-0.25. Minimum Negative Offset calibration value
      -  0x4000	-4096. Maximum Negative Offset calibration value
   @return ADC Offset calibration for required PGA gain.
**/
uint32_t  AdcOffsetCalAdjust(uint32_t u32Gain,
                        uint32_t u32FacOffset,
                        int32_t iAdcDat)
{
  int32_t i32Temp = 0;
  uint32_t u32NewCalVal = 0;

  if (iAdcDat > 32768)                         // Value from ADC is too large
  {
     i32Temp = ((iAdcDat - 32768)* 4);         // 4x calibration LSBs in 1 ADC result LSB
     if  (u32FacOffset < i32Temp)              // sign will change - new OFFSET cal value below 0x0000
     {
        u32NewCalVal = ((0x7FFF - i32Temp) +   // Subtract from 0x7FFF (minimum negative adjustment
               u32FacOffset);
     }
     else
     {
       u32NewCalVal = u32FacOffset - i32Temp;
     }
  }
  else if (iAdcDat < 32768)                    // Value from ADC is too small
  {
     i32Temp = ((32768 - iAdcDat)* 4);         // 4x calibration LSBs in 1 ADC result LSB
     if ((u32FacOffset + i32Temp) > 0x3FFF)
        u32NewCalVal = 0x3FFF;                 // Max positive offset adjustment allowed
     else
       u32NewCalVal = u32FacOffset + i32Temp;  // Add offset adjustment to factory cal value
  }
  else                                         // No adjustment needed
    u32NewCalVal = u32FacOffset;

  pADI_AFE->CALDATLOCK = 0xDE87A5AF;           // Write to unlock key to gain access to Calibration registers

  switch (u32Gain)
  {
     case GNPGA_1:
       pADI_AFE->ADCOFFSETGN1 = u32NewCalVal;
       break;
     case GNPGA_1_5:
        pADI_AFE->ADCOFFSETGN1P5 = u32NewCalVal;
        break;
      case GNPGA_2:
        pADI_AFE->ADCOFFSETGN2 = u32NewCalVal;
        break;
      case GNPGA_4:
        pADI_AFE->ADCOFFSETGN4 = u32NewCalVal;
        break;
      case GNPGA_9:
        pADI_AFE->ADCOFFSETGN9 = u32NewCalVal;
        break;
      default:
        break;

  }
   pADI_AFE->CALDATLOCK = 0xDE87A5AF;           // Write again to lock key Calibration registers
  return u32NewCalVal;
}
/**
   @brief uint32_t  AdcGainCalAdjust(uint32_t u32Gain, uint32_t u32FactoryGain, int32_t iAdcDat, float fVTarget)
         ==========Function to generate new ADC Gain calibration values based on measured voltage and existing Gain cal value
   @param u8Gain :{GNPGA_1, GNPGA_1_5, GNPGA_2, GNPGA_4, GNPGA_9}
      - ADCCON[18:16]
      - 0 or GNPGA_1 for Gain =1
      - 0x10000 or GNPGA_1_5 for Gain =1.5
      - 0x20000 or GNPGA_2 for Gain =2
      - 0x30000 or GNPGA_4 for Gain =4
      - 0x40000 or GNPGA_9 for Gain =9
   @param u32FactoryGain :{0 - 0x7FFF}
      - .
   @param iAdcDat:{0 - 0xFFFFFFFF}
      - Value based on SINC2DAT, value between 0 to 0xFFFFFFFF
   @param fVTarget:{0.2 to 1.82}
      - Voltage applied to input - target voltage to calibrate against
   @Description: Inputs PGA Gain setting
      - Takes ADC measurement for internal 1.82V v 1.11V references using PGA gain setting
      - Based on this, it calculates how much the existing gain calibration register needs to be changed by
      - ADC Gain calibration register is a 15-bit, signed value
      - ADC gain correction for Voltage channel represented as follows:
      - 0x0000, 0. Illegal value. Will result in ADC result of 0
      - 0x2000, 0.5x. ADC result multiplied by 0.5
      - 0x4000. 1.0. ADC result multiplied by 1. No Gain adjustment. Default value
      - 0x4001, 1.000061. Minimum Positive Gain adjustment
      - 0x7FFF. 2x. Maximum Positive Gain adjustment
      - 0x0001. 0.000061x. Maximum Negative Gain Adjustment
      - 0x3FFF. 0.999939x. Minimum negative Gain adjustment

   @return ADC Gain calibration for required PGA gain.
**/
uint32_t  AdcGainCalAdjust(uint32_t u32Gain,
                        uint32_t u32FactoryGain,
                        int32_t iAdcDat, 
                        float fVTarget,
                        float fVref,
                        float fVbiasCap,
                        float kFactor)
{

  
  fPgaDiv = PGAAdjustFactor();                 // get floating point number for PGA gain adjustment
  fTempLsbCalc =                               // Calculate the LSB size of the ADC for PGA setting
    (((fVref *kFactor)/32767)/fPgaDiv);
  //  ((fVref * fPgaDiv)*kFactor)/32767;
 // fTemp1 = (fVref-fVbiasCap)/ fTempLsbCalc;     // Calcuale # of LSBs expected 
  fTemp1 = (fVTarget-fVbiasCap)/ fTempLsbCalc;     // Calcuale # of LSBs expected 
  iTargetAdcCode = (int)fTemp1;   
  
   i32Temp = (iAdcDat - 0x8000);               // Convert ADc reading to unsigned value
 
  if (i32Temp > iTargetAdcCode)                // Value from ADC is too large
  {
     fGainAdjRequired = ((float)iTargetAdcCode)/((float)i32Temp);
     fGainAdj = ((float)u32FactoryGain) *fGainAdjRequired ;
     //iGainError= (int)(fGainAdj/fGainAdjustLsb); 
     u32NewCalVal = (int)fGainAdj;
  }
  else if (i32Temp < iTargetAdcCode)                // Value from ADC is too small
  {
  //  fGainAdjRequired = ((float)i32Temp)/((float)iTargetAdcCode);
    fGainAdjRequired = ((float)iTargetAdcCode)/((float)i32Temp);
  //  fGainAdj = 1-fGainAdjRequired;
    fGainAdj = ((float)u32FactoryGain) *fGainAdjRequired ;
    u32NewCalVal = (int)fGainAdj;
  }
  else
    u32NewCalVal = u32FactoryGain;             // No gain change required
  
  if ((u32NewCalVal == 0 ) | (u32NewCalVal >0x8000))                    // illegal value
    u32NewCalVal = 0x14000;                    
  pADI_AFE->CALDATLOCK = 0xDE87A5AF;           // Write to unlock key to gain access to Calibration registers
  
  switch (u32Gain)
  {
     case GNPGA_1:
       pADI_AFE->ADCGAINGN1 = u32NewCalVal;
       break;
     case GNPGA_1_5:
        pADI_AFE->ADCGAINGN1P5 = u32NewCalVal;
        break;
      case GNPGA_2:
        pADI_AFE->ADCGAINGN2 = u32NewCalVal;
        break;       
      case GNPGA_4:
        pADI_AFE->ADCGAINGN4 = u32NewCalVal;
        break;    
      case GNPGA_9:
        pADI_AFE->ADCGAINGN9 = u32NewCalVal;
        break; 
      default:
        break;
    
  }
   pADI_AFE->CALDATLOCK = 0xDE87A5AF;           // Write again to lock key Calibration registers
  return u32NewCalVal;
}

float PGAAdjustFactor(void)
{
  uint32_t u32AdcconPGA = 0;
  
  u32AdcconPGA = ((pADI_AFE->ADCCON & 0x70000)>>16); // Read off ADCCON[18:16] to determine PGA gain setting
  switch (u32AdcconPGA)
  {
     case 0:                                   // PGA Gain = 1;
       fVrefDiv = 1;
       break;
     case 1:                                   // PGA Gain = 1;
       fVrefDiv = 1.5;
       break;
     case 2:                                   // PGA Gain = 2;
       fVrefDiv = 2;
       break;
     case 3:                                   // PGA Gain = 4;
       fVrefDiv = 4;
       break;
     case 4:                                   // PGA Gain = 9;
       fVrefDiv = 9;
       break;  
     default:
       fVrefDiv = 1;
       break;
  }
  return fVrefDiv;
}

