#include "HSDacCal.h"
#include <stdio.h>
#include <string.h>


/**
	@brief void DacAttenSetup(uint8_t u8Atten)
			========== High level function to setup T,D,P & N switches for HSDAC calibration via external RCAL
   @param iAdcDat:{0,1,2,3}
      - 0  to Set HSDACCON[0],[12] = 0 for +/-607mV output range. Gain of 2
      - 1  to Set HSDACCON[0]=1, HSDACCON[12] = 0 for +/-121mV output range. Gain = 0.4x
      - 2  to Set HSDACCON[0]=0, HSDACCON[12] = 1 for +/-75mV output range. Gain = 0.25x
      - 3  to Set HSDACCON[0]=1, HSDACCON[12] = 1 for +/-15.1mV output range. Gain = 0.05x
	@return void

   @Description: 
      Sets HSDAC output range by configuring HSDACCON[12], [0] accordingly 
**/
void DacAttenSetup(uint8_t u8Atten)
{
   uint8_t u8AttenSw = 0;
   
   u8AttenSw = u8Atten;
  
   switch (u8AttenSw)
   {
     case 0:                        // Gain = 2
       pADI_AFE->HSDACCON &= 0xEFFE; 
       break;
     case 1:                        // Gain = 0.4 x
       pADI_AFE->HSDACCON &= 0xEFFE; 
       pADI_AFE->HSDACCON |= 0x1;
       break;
     case 2:                        // Gain = 0.25x
       pADI_AFE->HSDACCON &= 0xEFFE; 
       pADI_AFE->HSDACCON |= 0x1000;
       break;
     case 3:                        // Gain = 0.05x
       pADI_AFE->HSDACCON &= 0xEFFE; 
       pADI_AFE->HSDACCON |= 0x1001;
       break;
   default:
       pADI_AFE->HSDACCON &= 0xEFFE;
     break;
     }
}

/**
	@brief uint32_t SwitchSetup(void)
			========== High level function to setup T,D,P & N switches for HSDAC calibration via external RCAL

	@return pADI_AFE->SWCON

   @Description: 
      Closes DR0, PR0, TR1 and T9 to connect external RCAL resistor to excitation amplifier
**/
uint32_t SwitchSetup(void)
{
   pADI_AFE->SWCON = BITM_AFE_SWCON_T9CON |   
     (BITM_AFE_SWCON_TMUXCON & (0x8<<BITP_AFE_SWCON_TMUXCON))|
     (BITM_AFE_SWCON_NMUXCON & (0xA<<BITP_AFE_SWCON_NMUXCON))|
     (BITM_AFE_SWCON_PMUXCON & (0x1<<BITP_AFE_SWCON_PMUXCON))| 
     (BITM_AFE_SWCON_DMUXCON & (0x1<<BITP_AFE_SWCON_DMUXCON));  

   return pADI_AFE->SWCON;  
}


/**
	@brief uint32_t HSDacOffsetAdjustFullRange(int32_t iAdcDat)
			========== High level function used to calibrate HSDAC when HSDACCON[0][12]=0 and HSDACCON[0]=1, HSDACCON[12]=0
    @param iAdcDat:{0 - 0xFFFFFFFF}
      - Value based on SINC2DAT, value between 0 to 0xFFFFFFFF
	@return New DAC calibration value.

   @Description: Inputs ADC error measurement
         Based on this input, it adjusts the associated offset calibration register.
         Use this function when INAMP/Attenuation set to full scale, +/-607mV range or +/-121mV
         Works for both HP and LP mode updating DACOFFSETHP or DACOFFSET - based on PMBW[0]
**/
uint32_t HSDacOffsetAdjustFullRange(int32_t iAdcDat)
{
  uint8_t u8PwrMode = 0;                       // Flag to determine PMBW[0]. =0 for LP Mode ;1 for HP mode
  uint32_t u32FacOffset = 0;                   // Local variable to temporarily read Factory Offset cal
  int32_t i32Temp = 0;                         // temp variable for calcualting offset adjustment
  uint32_t u32NewCalVal = 0;                   // variable used to store and return new calibration value
  
  u8PwrMode = (pADI_AFE->PMBW & 0x1);          // PMBW[0]. =0 for LP Mode ;1 for HP mode
  
  if ((u8PwrMode & 0x1) == 0)                   // LP Mode
      u32FacOffset =
        (pADI_AFE->DACOFFSET & 0xFFF);        // read factory calibration value for full o/p range - LP mode
  else                                         // HP mode
    u32FacOffset =
        (pADI_AFE->DACOFFSETHP & 0xFFF);      // read factory calibration value for full o/p range - HP mode

  u32NewCalVal = u32FacOffset;                 // If there is no adjustment required (ADC code =0x8000), ensure existing cal value is returned
 // In this range, ~7x ADC LSBs = 1 DAC LSB.
 // there are 2x DAC offset calibration bits per DAC LSB
   if (iAdcDat > 32768)                        // Value from ADC indicates positive offset
   {
     i32Temp = ((iAdcDat - 32768)* 2);         // ~7x DAC  bits in 1 ADC result LSB
     i32Temp = (i32Temp / 7);                  // 0.5 DAC calibration bits in 1 DAC LSB
     if  (u32FacOffset < i32Temp)              // sign will change - new OFFSET cal value below 0x0000
      {
         u32NewCalVal =                        // Subtract from 0xFFF (minimum negative adjustment
           ((0xFFF - i32Temp) + u32FacOffset);
      }
     else
     {
       u32NewCalVal = u32FacOffset - i32Temp;  // reduce factory offset cal to reduce the error
     }
   }
   else if (iAdcDat < 32768)                   // Value from ADC indicates negative offset
   {
     i32Temp = ((32768 - iAdcDat)* 2);         // ~7x DAC  bits in 1 ADC result LSB
     i32Temp = (i32Temp/ 7);                   // 0.5 DAC calibration bits in 1 DAC LSB
     if ((i32Temp + u32FacOffset) > 0xFFF)     // Check if cal value sign bit is changing
     {
       u32NewCalVal = i32Temp - (0xFFF - u32FacOffset);
     }
     else
     { 
     u32NewCalVal = u32FacOffset +             // Increase factory offset cal value 
           i32Temp;
     }
   }

   pADI_AFE->CALDATLOCK = 0xDE87A5AF;           // Write to unlock key to gain access to Calibration registers
   if ((u8PwrMode & 0x1) == 0)                   // LP Mode
      pADI_AFE->DACOFFSET = (u32NewCalVal &0xFFF);
   else
      pADI_AFE->DACOFFSETHP = (u32NewCalVal &0xFFF);
   pADI_AFE->CALDATLOCK = 0xDE87A5AF;           // lock key again
  
return u32NewCalVal;  
}

/**
	@brief uint32_t HSDacOffsetAdjustAttenRange(int32_t iAdcDat)
			========== High level function used to calibrate HSDAC when HSDACCON[0],[12]=1. Also when HSDACCON[12]=1 and HSDACCON[0] = 0
    @param iAdcDat:{0 - 0xFFFFFFFF}
      - Value based on SINC2DAT, value between 0 to 0xFFFFFFFF
	@return New DAC calibration value.

   @Description: Inputs ADC error measurement
         Based on this input, it adjusts the associated offset calibration register.
         Use this function when INAMP/Attenuation set to full scale, +/-15.1mV range
         Works for both HP and LP mode updating DACOFFSETATTENHP or DACOFFSETATTEN - based on PMBW[0]
   Note: Function assumes ADC PGA is set for Gain = 4
**/
uint32_t HSDacOffsetAdjustAttenRange(int32_t iAdcDat)
{
   uint8_t u8PwrMode = 0;                      // Flag to determine PMBW[0]. =0 for LP Mode ;1 for HP mode
   uint32_t u32FacOffset = 0;                  // Local variable to temporarily read Factory Offset cal
   int32_t i32Temp = 0;                        // temp variable for calcualting offset adjustment
   uint32_t u32NewCalVal = 0;                  // variable used to store and return new calibration value
   
   u8PwrMode = (pADI_AFE->PMBW & 0x1);         // PMBW[0]. =0 for LP Mode ;1 for HP mode
  
  if ((u8PwrMode & 0x1) == 0)                  // LP Mode
  {
    if ((pADI_AFE->HSDACCON & 0x1000) == 0x0)
    {
      u32FacOffset =
        (pADI_AFE->DACOFFSET & 0xFFF);        // read factory calibration value for full o/p range - LP mode
      u32NewCalVal = u32FacOffset;             // If there is no adjustment required (ADC code =0x8000), ensure existing cal value is returned
    }
    else
    {
      u32FacOffset =
        (pADI_AFE->DACOFFSETATTEN & 0xFFF);    // read factory calibration value for attenuated o/p range - LP mode
      u32NewCalVal = u32FacOffset;             // If there is no adjustment required (ADC code =0x8000), ensure existing cal value is returned
    }
  }
  else
  {
    // HP mode
    if ((pADI_AFE->HSDACCON & 0x1000) == 0x00)
    {
       u32FacOffset =
          (pADI_AFE->DACOFFSETHP & 0xFFF);    // read factory calibration value for full o/p range - HP mode
       u32NewCalVal = u32FacOffset;            // If there is no adjustment required (ADC code =0x8000), ensure existing cal value is returned
    }
    else
    {
       u32FacOffset =
          (pADI_AFE->DACOFFSETATTENHP & 0xFFF);// read factory calibration value for full o/p range - HP mode
       u32NewCalVal = u32FacOffset;            // If there is no adjustment required (ADC code =0x8000), ensure existing cal value is returned
    }
  }
  
  // Note: Function assumes ADC PGA is set for Gain = 4
  // In this range, ADV LSB = 13.89uV
  // DAC LSB with HSDACCON[0]=[12] = 1 is 9.88uV
  // DAC LSB with HSDACCON[0]= 0 HSDACCON[12] = 1 is 49uV
  // 2x DAC offset calibration bits per DAC LSB
  //So assume there 14 ADC LSBs per 5 DAC Calibration LSBs
   if (iAdcDat > 32768)                        // Value from ADC indicates positive offset
   {
     if (((pADI_AFE->HSDACCON & 0x1000) == 0x1000) && // HSDACCON[12]=1, for +/-15mV range
        ((pADI_AFE->HSDACCON & 0x1) == 0x1))
     {
        i32Temp = ((iAdcDat - 32768)* 14);     // adjust ADC error reading
        i32Temp = (i32Temp / 5);               // assume there 5 ADC LSBs per 14 DAC Calibration LSBs
     }
     else if 
        (((pADI_AFE->HSDACCON & 0x1000) == 0x1000) && // HSDACCON[12]=1,HSDACCON[12]=0, for +/-75mV range
        ((pADI_AFE->HSDACCON & 0x1) == 0x0))                              
     {
        i32Temp = ((iAdcDat - 32768)* 14);     // adjust ADC error reading
        i32Temp = (i32Temp / 25);              // assume there 25 ADC LSBs per 14 DAC Calibration LSBs
     }
     else                                      // HSDACCON[0]=1, HSDACCON[12]=0 for +/-121mV range
     {
        i32Temp = ((iAdcDat - 32768)* 14);     // adjust ADC error reading
        i32Temp = (i32Temp / 40);              // assume there 40 ADC LSBs per 14 DAC Calibration LSBs
     }
     if  (u32FacOffset < i32Temp)              // sign will change - new OFFSET cal value below 0x0000
      {
         u32NewCalVal =                        // Subtract from 0xFFF (minimum negative adjustment
           ((0xFFF - i32Temp) + u32FacOffset);
      }
     else
     {
       u32NewCalVal = u32FacOffset - i32Temp;  // reduce factory offset cal to reduce the error
           
     }
   }
   else if (iAdcDat < 32768)                   // Value from ADC indicates negative offset
   {
     if (((pADI_AFE->HSDACCON & 0x1000) == 0x1000) && // HSDACCON[12]=1, for +/-15mV range
        ((pADI_AFE->HSDACCON & 0x1) == 0x1))
     {
        i32Temp = ((32768 - iAdcDat)* 14);        // adjust ADC error reading
        i32Temp = (i32Temp/ 5);                   // assume there 5 ADC LSBs per 14 DAC Calibration LSBs
     }
     else if 
        (((pADI_AFE->HSDACCON & 0x1000) == 0x1000) && // HSDACCON[12]=1,HSDACCON[12]=0, for +/-75mV range
        ((pADI_AFE->HSDACCON & 0x1) == 0x0))                                
     {
        i32Temp = ((32768 - iAdcDat)* 14);     // adjust ADC error reading
        i32Temp = (i32Temp / 25);              // assume there 25 ADC LSBs per 14 DAC Calibration LSBs
     } 
     else                                      // HSDACCON[0]=1, HSDACCON[12]=0 for +/-121mV range
     {
        i32Temp = ((32768 - iAdcDat)* 14);     // adjust ADC error reading
        i32Temp = (i32Temp / 40);              // assume there 40 ADC LSBs per 14 DAC Calibration LSBs      
     }
       
     if ((i32Temp + u32FacOffset) > 0xFFF)     // Check if cal value sign bit is changing
     {
       u32NewCalVal = i32Temp - (0xFFF - u32FacOffset);
     }
     else
     { 
     u32NewCalVal = u32FacOffset +             // Increase factory offset cal value 
           i32Temp;
     }
   }
  
   pADI_AFE->CALDATLOCK = 0xDE87A5AF;          // Write to unlock key to gain access to Calibration registers
   if ((u8PwrMode & 0x1) == 0)                 // LP Mode
   {
     if ((pADI_AFE->HSDACCON & 0x1000) == 0x0)
        pADI_AFE->DACOFFSET = (u32NewCalVal &0xFFF);
     else
        pADI_AFE->DACOFFSETATTEN = (u32NewCalVal &0xFFF);
   }
   else                                        // HP Mode
   {
     if ((pADI_AFE->HSDACCON & 0x1000) == 0x0)
        pADI_AFE->DACOFFSETHP = (u32NewCalVal &0xFFF);
     else
        pADI_AFE->DACOFFSETATTENHP = (u32NewCalVal &0xFFF);
   }
   pADI_AFE->CALDATLOCK = 0xDE87A5AF;          // lock key again
   return u32NewCalVal;  
}
/**
	@brief uint32_t GainAdjust(uint8_t u8GainDir)
			========== High level function used to adjust HSDAC Pk-Pk value up or down 1x calibration bit
    @param u8GainDir:{0, 1}
      - 0 to reduce pk-pk output voltage
      - 1 to increase pk-pk output voltage
	@return New DAC calibration value.

   @Description: Inputs ADC error measurement
         Based on this input, it adjusts the associated offset calibration register.
         Use this function when INAMP/Attenuation set to full scale, +/-15.1mV range
         Works for both HP and LP mode updating DACOFFSETATTENHP or DACOFFSETATTEN - based on PMBW[0]
   Note: Function assumes ADC PGA is set for Gain = 4
**/
uint32_t GainAdjust(uint8_t u8GainDir)
{
  uint32_t u32NewCalVal = 0;                  // variable used to store and return new calibration value
  
  u32NewCalVal = pADI_AFE->DACGAIN;
  if ((u8GainDir & 0x1) == 0)                 // reduce pk-pk voltage
  {
    if (u32NewCalVal == 0)
      u32NewCalVal = 0;                       // Can't go any lower
    else
      u32NewCalVal--;
  }
  else if ((u8GainDir & 0x1) == 1)            // Increase pk-pk voltage
  {
    if (u32NewCalVal == 0xFFF)                // Can't go any higher
           u32NewCalVal = 0xFFF;  
    else
      u32NewCalVal++;
  }
  
  pADI_AFE->CALDATLOCK = 0xDE87A5AF;          // Write to unlock key to gain access to Calibration registers
  pADI_AFE->DACGAIN = u32NewCalVal;
  pADI_AFE->CALDATLOCK = 0xDE87A5AF;          // Write to lock key to gain access to Calibration registers
  return pADI_AFE->DACGAIN;
}
