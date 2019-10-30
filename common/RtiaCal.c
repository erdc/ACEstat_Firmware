#include "RtiaCal.h"
#include <stdio.h>
#include <string.h>
#include "AfeAdcLib.h"
#include "ClkLib.h"

/**
	@brief void SetupCal_LPRTIA (uint8_t u8Chan, LPTIA_RGAIN_Type LPRTIA, uint8_t u8SelCalResistor, uint8_t u8OpenSensor)
			========== High level function used to setup LPTIA0/1 to measure LPTIA's Gain resistor
    @param u8Chan:{0,1}
      - 0 or CHAN0 for LPTIA0 channel
      - 1 or CHAN1 for LPTIA1 channel
    @param u8LPRTIA:{0 - 26}
      - 0 or LPTIA_RGAIN_DISCONNECT // disconnect LPTIA Gain resistor
      - 1 or LPTIA_RGAIN_200       // RGAIN = 200 ohm
      - 2 or LPTIA_RGAIN_1K        // RGAIN = 1K ohm
      - 3 or LPTIA_RGAIN_2K        // RGAIN = 2K ohm
      - 4 or LPTIA_RGAIN_3K        // RGAIN = 3K ohm
      - 5 or LPTIA_RGAIN_4K        // RGAIN = 4K ohm
      - 6 or LPTIA_RGAIN_6K        // RGAIN = 6K ohm
      - 7 or LPTIA_RGAIN_8K        // RGAIN = 8K ohm
      - 8 or LPTIA_RGAIN_10K       // RGAIN = 10K ohm
      - 9 or LPTIA_RGAIN_12K       // RGAIN = 12K ohm
      - 10 or LPTIA_RGAIN_16K      // RGAIN = 16K ohm
      - 11 or LPTIA_RGAIN_20K      // RGAIN = 20K ohm
      - 12 or LPTIA_RGAIN_24K      // RGAIN = 24K ohm
      - 13 or LPTIA_RGAIN_30K      // RGAIN = 30K ohm
      - 14 or LPTIA_RGAIN_32K      // RGAIN = 32K ohm
      - 15 or LPTIA_RGAIN_40K      // RGAIN = 40K ohm
      - 16 or LPTIA_RGAIN_48K      // RGAIN = 48K ohm
      - 17 or LPTIA_RGAIN_64K      // RGAIN = 64K ohm
      - 18 or LPTIA_RGAIN_85K      // RGAIN = 85K ohm
      - 19 or LPTIA_RGAIN_96K      // RGAIN = 96K ohm
      - 20 or LPTIA_RGAIN_100K     // RGAIN = 100K ohm
      - 21 or LPTIA_RGAIN_120K     // RGAIN = 120K ohm
      - 22 or LPTIA_RGAIN_128K     // RGAIN = 128K ohm
      - 23 or LPTIA_RGAIN_160K     // RGAIN = 160K ohm
      - 24 or LPTIA_RGAIN_196K     // RGAIN = 196K ohm
      - 25 or LPTIA_RGAIN_256K     // RGAIN = 256K ohm
      - 26 or LPTIA_RGAIN_512K     // RGAIN = 512K ohm
   @param u8SelCalResistor:{0,1,2} // Selects resistor used to generate calibration current
      - 0 or RCAL0_RCAL1 for HSDAC to generate differential voltage across external resistor between RCAL0/RCAL1 pins
      - 1 or AIN0_AIN1 for HSDAC to generate differential voltage across external resistor between AIN0/AIN1 pins
      - 2 or AIN2_AIN3 for HSDAC to generate differential voltage across external resistor between AIN2/AIN3 pins
   @param u8OpenSensor:{0,1}
      - 0 or CONNECT_TO_CE for PA amplifier connected to CE/RE pins (SW2 closed)
      - 1 or DISCONNECT_TO_CE for PA amplifier disconnected to CE/RE pins (SW2 Opened)

   @Description: Inputs TIA channel number (0 or 1) and required RTIA value to measure
         LPTIASWx = 0x3624.
            - Potentiostat switches sw2, sw5, sw8, sw9, sw12 & sw13 all closed. Other LP potentiostat switches open.
            - Configures PA amplifier for unity gain mode
         RLOAD is fixed at 10ohms, Rfilter for LPF is set to 100Kohms
         LPDACx VZERO output set to 1.26V for purposes of measuring LPTIA gain resistor.
         P, N, D & T switches configured to select external pins used to connect calibration resistor.
            - 3x options supported (1) RCAL0/RCAL1; 2) AIN0/AIN1; 3) AIN2/AIN3
         
**/
void SetupCal_LPRTIA (uint8_t u8Chan, LPTIA_RGAIN_Type LPRTIA, uint8_t u8SelCalResistor, uint8_t u8OpenSensor)
{
    uint8_t u8ChanNum = 0;
    LPTIA_RGAIN_Type Rtia_Sel;
    
    u8ChanNum = u8Chan;
    Rtia_Sel = LPRTIA; 
  
    LPDacPwrCtrl(u8ChanNum,PWR_UP);            // power up LP VDAC0
    AfeLpTiaPwrDown(u8ChanNum,0);              // Power up PA and TIA amplifiers for Channel1
    delay_10us(500);                           // delay 50mS - optional delay for LP DAC reference
    if (u8OpenSensor == CONNECT_TO_CE)         // SW2 switch closed - CE pin connected to PA amplifier
       AfeLpTiaSwitchCfg(u8ChanNum,
                      0x3624);                 // PA in unity gain mode, LPTIA normal mode with LPF connected
    else
       AfeLpTiaSwitchCfg(u8ChanNum,            // SW2/SW3 & SW4 open disconnect CE/RE pins from PA amplifier
                      0x3120);                 // PA in unity gain mode, LPTIA normal mode with LPF connected
               
    LPDacCfg(u8ChanNum,                        // Configure channel0
            LPDACSWNOR,                        // Normal DAC switch control to caps
            VBIAS12BIT_VZERO6BIT,              // VBIAS is 12-bit output
            LPDACREF2P5);                      // LPDAC reference source is internal LP 2.5V VREF
    LPDacWr(u8ChanNum,(0x1F),0x7C0);           // Set VZERO0/VBIAS0 to 1.26V 
    delay_10us(500);                           // delay 50mS - optional delay for LP DAC reference
    AfeLpTiaCon(u8ChanNum,                     // Configure LPTIA RLOAD = 10ohms, LPF resistor = 100Kohms
                LPTIA_RLOAD_10,
                Rtia_Sel,  
                LPTIA_RFILTER_100K);
  
    switch(u8SelCalResistor)
    {
       case RCAL0_RCAL1:  
          //      Closes DR0, PR0, NR1, TR1 and T5(CHAN0) or T7(CHAN1) to connect external RCAL resistor to excitation amplifier and to SE0/SE1 input to LPTIA
         if (u8ChanNum == 0)                   // Channel 0
            pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_TR1 |
               BITM_AFE_TSWFULLCON_T5;         // Close T5 for SE0
         else                                  // Channel 1
           pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_TR1 |
               BITM_AFE_TSWFULLCON_T7;         // Close T5 for SE1
         pADI_AFE->NSWFULLCON = 
            BITM_AFE_NSWFULLCON_NR1;           // Connect RCAL1 to N-Node of excitation Amp
         pADI_AFE->PSWFULLCON = 
            BITM_AFE_PSWFULLCON_PR0;           // Connect RCAL0 to P-Node of excitation amp  
         pADI_AFE->DSWFULLCON = 
            BITM_AFE_DSWFULLCON_DR0;           // Connect D node to RCAL0
         pADI_AFE->SWCON = 0x10000;                   // Switches controlled by their own FULLCON registers 
         pADI_AFE->HSRTIACON |= 0xF;                  // open HP RTIA switch
         break;
       case AIN1_AIN0:  
          //      Closes D2, P2, N1, T1 and T5(CHAN0) or T7(CHAN1) to connect external resistor between AIN0/AIN1 to excitation amplifier and to SE0/SE1 input to LPTIA
         if (u8ChanNum == 0)                   // Channel 0   
            pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_T1 |
               BITM_AFE_TSWFULLCON_T5;         // Close T5 connect to SE0
         else                                  // Channel 1
            pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_T1 |
               BITM_AFE_TSWFULLCON_T7;         // Close T7 connect to SE1
         pADI_AFE->NSWFULLCON = 
            BITM_AFE_NSWFULLCON_N1;            // Connect AIN0 to N-Node of excitation Amp
         pADI_AFE->PSWFULLCON = 
            BITM_AFE_PSWFULLCON_P2;            // Connect AIN1 to P-Node of excitation amp  
         pADI_AFE->DSWFULLCON = 
            BITM_AFE_DSWFULLCON_D2;            // Connect D node to AIN1
         pADI_AFE->SWCON = 0x10000;            // Switches controlled by their own FULLCON registers 
         pADI_AFE->HSRTIACON |= 0xF;           // open HP RTIA switch
         break;
      case AIN2_AIN3:  
          //      Closes D4, P4, N3, T3 and T5(CHAN0) or T7(CHAN1) to connect external resistor between AIN3/AIN2 to excitation amplifier and to SE0/SE1 input to LPTIA
         if (u8ChanNum == 0)                   // Channel 0   
            pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_T3 |
               BITM_AFE_TSWFULLCON_T5;         // Close T5 connect to SE1
         else                                  // Channel 1
            pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_T3 |
               BITM_AFE_TSWFULLCON_T7;         // Close T7 connect to SE1
         pADI_AFE->NSWFULLCON = 
            BITM_AFE_NSWFULLCON_N3;            // Connect AIN2 to N-Node of excitation Amp
         pADI_AFE->PSWFULLCON = 
            BITM_AFE_PSWFULLCON_P4;            // Connect AIN3 to P-Node of excitation amp  
         pADI_AFE->DSWFULLCON = 
            BITM_AFE_DSWFULLCON_D4;            // Connect D node to AIN3
         pADI_AFE->SWCON = 0x10000;            // Switches controlled by their own FULLCON registers 
         pADI_AFE->HSRTIACON |= 0xF;           // open HP RTIA switch
         break;
    default:
      break;
    }

}
/**
	@brief void SetupCal_HPRTIA_RTIA2 (HPTIASE_RTIA_Type HPRTIA, uint8_t u8SelCalResistor)
			========== High level function used to setup RTIA2 to measure HPTIA's Gain resistor
    @param u8LPRTIA:{0 - 26}
      HPTIASE_RTIA_200 = 0u,  // RGAIN = 200 ohm
      HPTIASE_RTIA_1K,        // RGAIN = 1K ohm
      HPTIASE_RTIA_5K,        // RGAIN = 5K ohm
      HPTIASE_RTIA_10K,       // RGAIN = 10K ohm
      HPTIASE_RTIA_20K,       // RGAIN = 20K ohm
      HPTIASE_RTIA_40K,       // RGAIN = 40K ohm
      HPTIASE_RTIA_80K,       // RGAIN = 80K ohm
      HPTIASE_RTIA_160K,      // RGAIN = 160K ohm

   @param u8SelCalResistor:{0,1,2} // Selects resistor used to generate calibration current
      - 0 or RCAL0_RCAL1 for HSDAC to generate differential voltage across external resistor between RCAL0/RCAL1 pins
      - 1 or AIN0_AIN1 for HSDAC to generate differential voltage across external resistor between AIN0/AIN1 pins
      - 2 or AIN2_AIN3 for HSDAC to generate differential voltage across external resistor between AIN2/AIN3 pins

   @Description: Sets up switches to allow calibration current generated through external precision resistor to flow through internal RTIA2

         
**/
void SetupCal_HPRTIA_RTIA2 (HPTIASE_RTIA_Type HPRTIA, uint8_t u8SelCalResistor)
{
   HPTIASE_RTIA_Type Rtia_Sel;
   
   Rtia_Sel = HPRTIA;
   
  //  AfeHpTiaPwrUp(true);                       // Power up HP TIA 
 //   AfeHpTiaCon(HPTIABIAS_VZERO0);             // Turn on HP TIA, use internal VZERO as CM voltage setting
    

    AfeHpTiaSeCfg(Rtia_Sel,                    // RTIA value select
        //          BITM_HPTIA_CTIA_16PF,         // 8pF cload on HPTIA
                  BITM_HPTIA_CTIA_31PF,
                  0);                          // disconnect protection diode
    
    switch(u8SelCalResistor)
    {
       case RCAL0_RCAL1:  
          //      Closes DR0, PR0, NR1, TR1 and T9 to connect external RCAL resistor to excitation amplifier and to RTIA2
            pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_TR1 |
               BITM_AFE_TSWFULLCON_T9;         // Close T9 
         pADI_AFE->NSWFULLCON = 
            BITM_AFE_NSWFULLCON_NR1;           // Connect RCAL1 to N-Node of excitation Amp
         pADI_AFE->PSWFULLCON = 
            BITM_AFE_PSWFULLCON_PR0;           // Connect RCAL0 to P-Node of excitation amp  
         pADI_AFE->DSWFULLCON = 
            BITM_AFE_DSWFULLCON_DR0;           // Connect D node to RCAL0
         pADI_AFE->SWCON = 0x10000;                   // Switches controlled by their own FULLCON registers 
         break;
       case AIN1_AIN0:  
          //      Closes D2, P2, N1, T1 and T9 to connect external resistor between AIN0/AIN1 to excitation amplifier and to RTIA2
         pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_T1 |
               BITM_AFE_TSWFULLCON_T9;         // Close T9 
         pADI_AFE->NSWFULLCON = 
            BITM_AFE_NSWFULLCON_N1;            // Connect AIN0 to N-Node of excitation Amp
         pADI_AFE->PSWFULLCON = 
            BITM_AFE_PSWFULLCON_P2;            // Connect AIN1 to P-Node of excitation amp  
         pADI_AFE->DSWFULLCON = 
            BITM_AFE_DSWFULLCON_D2;            // Connect D node to AIN1
         pADI_AFE->SWCON = 0x10000;            // Switches controlled by their own FULLCON registers 
         break;
      case AIN2_AIN3:  
          //      Closes D4, P4, N3, T3 and T9 to connect external resistor between AIN3/AIN2 to excitation amplifier and to RTIA2
          pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_T3 |
               BITM_AFE_TSWFULLCON_T9;         // Close T9
         pADI_AFE->NSWFULLCON = 
            BITM_AFE_NSWFULLCON_N3;            // Connect AIN2 to N-Node of excitation Amp
         pADI_AFE->PSWFULLCON = 
            BITM_AFE_PSWFULLCON_P4;            // Connect AIN3 to P-Node of excitation amp  
         pADI_AFE->DSWFULLCON = 
            BITM_AFE_DSWFULLCON_D4;            // Connect D node to AIN3
         pADI_AFE->SWCON = 0x10000;            // Switches controlled by their own FULLCON registers 
         break;
    default:
      break;
    } 
     pADI_AFE->DE0RESCON = 0xFF;                // disconnect RES2_3 gain resistors
     pADI_AFE->DE1RESCON = 0xFF;                // disconnect RES2_5 gain resistors
}
/**
	@brief void SetupCal_HPRTIA_RTIA2_3 (HPTIADE_RTIA_Type HPRTIA, HPTIADE_RLOAD_Type HPRload, uint8_t u8SelCalResistor)
			========== High level function used to setup RTIA2_3 to measure HPTIA's Gain resistor
         
**/
void SetupCal_HPRTIA_RTIA2_3 (uint8_t u8SelCalResistor)
{
      switch(u8SelCalResistor)
    {
       case RCAL0_RCAL1:  
         //      Closes DR0, PR0, NR1, TR1,T6 & T10 to connect external resistor between RCAL0/RCAL1 to excitation amplifier and to RTIA2_03
         pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_TR1 |
               BITM_AFE_TSWFULLCON_T10 | 
               0x20;                           // Close T6 to connect to DE0 
         pADI_AFE->NSWFULLCON = 
            BITM_AFE_NSWFULLCON_NR1;           // Connect RCAL1 pin to N-Node of excitation Amp
         pADI_AFE->PSWFULLCON = 
            BITM_AFE_PSWFULLCON_PR0;           // Connect P-Node of excitation amp to RCAL0 pin
         pADI_AFE->DSWFULLCON = 
            BITM_AFE_DSWFULLCON_DR0;           // Connect D node to RCAL0 pin
         pADI_AFE->SWCON = 0x10000;            // Switches controlled by their own FULLCON registers 
         break;
       case AIN1_AIN0:  
          //      Closes D2, P2, N1, T1 and T6 to connect external resistor between AIN0/AIN1 to excitation amplifier and to RTIA2
         pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_T1 |
               BITM_AFE_TSWFULLCON_T10 | 
               0x20;         // Close T6 to connect to DE0 
         pADI_AFE->NSWFULLCON = 
            BITM_AFE_NSWFULLCON_N1;            // Connect AIN0 to N-Node of excitation Amp
         pADI_AFE->PSWFULLCON = 
            BITM_AFE_PSWFULLCON_P2;            // Connect AIN1 to P-Node of excitation amp  
         pADI_AFE->DSWFULLCON = 
            BITM_AFE_DSWFULLCON_D2;            // Connect D node to AIN1
         pADI_AFE->SWCON = 0x10000;            // Switches controlled by their own FULLCON registers 
         break;
      case AIN2_AIN3:  
          //     To Be completed
         break;
    default:
      break;
    }  
    pADI_AFE->HSRTIACON |= 0xF;                // disconnect RES2 gain resistors
    pADI_AFE->DE1RESCON = 0xFF;                // disconnect RES2_5 gain resistors
}
/**
	@brief void SetupCal_HPRTIA_RTIA2_5 (HPTIADE_RTIA_Type HPRTIA, HPTIADE_RLOAD_Type HPRload, uint8_t u8SelCalResistor)
			========== High level function used to setup RTIA2_3 to measure HPTIA's Gain resistor
         
**/
void SetupCal_HPRTIA_RTIA2_5 (uint8_t u8SelCalResistor)
{
      switch(u8SelCalResistor)
    {
       case RCAL0_RCAL1:  
         //      Closes DR0, PR0, NR1, TR1,T8 & T10 to connect external resistor between RCAL0/RCAL1 to excitation amplifier and to RTIA2_05
         pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_TR1 |
               BITM_AFE_TSWFULLCON_T11 | 
               0x80;                           // Close T8 to connect to DE1 
         pADI_AFE->NSWFULLCON = 
            BITM_AFE_NSWFULLCON_NR1;           // Connect RCAL1 pin to N-Node of excitation Amp
         pADI_AFE->PSWFULLCON = 
            BITM_AFE_PSWFULLCON_PR0;           // Connect P-Node of excitation amp to RCAL0 pin
         pADI_AFE->DSWFULLCON = 
            BITM_AFE_DSWFULLCON_DR0;           // Connect D node to RCAL0 pin
         pADI_AFE->SWCON = 0x10000;            // Switches controlled by their own FULLCON registers 
         break;
       case AIN1_AIN0:  
          //      Closes D2, P2, N1, T1 and T6 to connect external resistor between AIN0/AIN1 to excitation amplifier and to RTIA2
         pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_T1 |
               BITM_AFE_TSWFULLCON_T11 | 
               0x80;                           // Close T8 to connect to DE1 
         pADI_AFE->NSWFULLCON = 
            BITM_AFE_NSWFULLCON_N1;            // Connect AIN0 to N-Node of excitation Amp
         pADI_AFE->PSWFULLCON = 
            BITM_AFE_PSWFULLCON_P2;            // Connect AIN1 to P-Node of excitation amp  
         pADI_AFE->DSWFULLCON = 
            BITM_AFE_DSWFULLCON_D2;            // Connect D node to AIN1
         pADI_AFE->SWCON = 0x10000;            // Switches controlled by their own FULLCON registers 
         break;
      case AIN2_AIN3:  
          //     To Be completed
         break;
    default:
      break;
    } 
    pADI_AFE->HSRTIACON |= 0xF;                // disconnect RES2 gain resistors
    pADI_AFE->DE0RESCON = 0xFF;                // disconnect RES2_3 gain resistors
}
/**
   @brief uint32_t  InitOffsetCalLPTIA(uint8_t u8Chan)
         ==========Initializes ADC and LPTIA for Offset calibration of LPTIA channel using required PGA Gain setting - LP Mode only
   param u8Chan:{0,1}
      - 0 or CHAN0 for LPTIA0 channel
      - 1 or CHAN1 for LPTIA1 channel
   @Description: 
      - Inputs LPTIA channel number
      - Selects ADC input channel based on LPTIA channel number required
      - reads existing factory calibration for selected LPTIA Gain setting
   @return ADC LPTIA Offset calibration for required PGA gain.
**/
uint32_t InitOffsetCalLPTIA(uint8_t u8Chan)
{
    uint32_t u32TIAOffsetCal = 0;
   

   pADI_AFE->TSWFULLCON = 
        0;                                     // Open all T switches
    pADI_AFE->SWCON = 0x10000;                 // Switches controlled by their own FULLCON registers 
    if (u8Chan == CHAN0)
    {
       AfeAdcChan(MUXSELP_LPTIA0_LPF,
                  MUXSELN_LPTIA0_N);           // Select LPF0 output of LPTIA0 as P and LPTIA0 - input as N inputs to the ADC
       u32TIAOffsetCal = 
         pADI_AFE->ADCOFFSETLPTIA0;            // read factory calibration value
    }
    else
    {
       AfeAdcChan(MUXSELP_LPTIA1_LPF,
                  MUXSELN_LPTIA1_N);           // Select LPF1 output of LPTIA1 as P and LPTIA1 - input as N inputs to the ADC
       u32TIAOffsetCal = 
         pADI_AFE->ADCOFFSETLPTIA1;            // read factory calibration value
    }
 return u32TIAOffsetCal; 
  
}

/**
	@brief uint32_t LpTiaOffsetCalAdjust(uint8_t CHAN_NUM, uint32_t FactoryOffsetCal,int32_t iAdcDat)
			========== High level function used to calibrate offset error on ADC LPTIA0/1 channels
    @param u8Chan:{0,1}
      - 0 or CHAN0 for LPTIA0 channel
      - 1 or CHAN1 for LPTIA1 channel
  @param u32FacOffset :{0 - 0x7FFF}
      - .
  @param iAdcDat:{0 - 0xFFFFFFFF}
      - Value based on SINC2DAT, value between 0 to 0xFFFFFFFF
   @Description: Used to remove offset error from LPTIA.
         Inputs TIA channel number (0 or 1) 
         LPTIASWx = 0x3624.
         SE0/SE1 input is expected to be open - no current flowing into it.
         RLOAD is fixed at 10ohms, Rfilter for LPF is set to 100Kohms.
         ADCCON[18:16] is read to determine the PGA gain setting
         LPDACx VZERO output set to 1.26V for purposes of measuring LPTIA gain resistor.
         Inputs ADC measurement for this LPTIA channel
         Function will read the 
         Based on this, it calculates how much the existing offset register needs to be changed by
      - ADC Offset calibration register is a 15-bit, signed value
      - ADC offset correction for Voltage channel represented as a 2s complement number.
      - 0x3FFF	+4095.75. Maximum Positive Offset calibration value
      -  0x0001	+0.25. Minimum Positive Offset calibration value
      -  0x0000	0. No offset adjustment
      -  0x7FFF	-0.25. Minimum Negative Offset calibration value
      -  0x4000	-4096. Maximum Negative Offset calibration value
   @return ADC Offset calibration for required PGA gain
         
**/
uint32_t LpTiaOffsetCalAdjust(uint8_t CHAN_NUM,uint32_t FactoryOffsetCal,int32_t iAdcDat)
{
  int32_t i32Temp = 0;
  uint32_t u32NewCalVal = 0;

  if (iAdcDat > 32768)                         // Value from ADC is too large
  {
     i32Temp = ((iAdcDat - 32768)* 4);         // 4x calibration LSBs in 1 ADC result LSB
     if  (FactoryOffsetCal < i32Temp)              // sign will change - new OFFSET cal value below 0x0000
     {
        u32NewCalVal = ((0x7FFF - i32Temp) +   // Subtract from 0x7FFF (minimum negative adjustment
               FactoryOffsetCal);
     }
     else
     {
       u32NewCalVal = FactoryOffsetCal - i32Temp;
     }
  }
  else if (iAdcDat < 32768)                    // Value from ADC is too small
  {
     i32Temp = ((32768 - iAdcDat)* 4);         // 4x calibration LSBs in 1 ADC result LSB
     if ((FactoryOffsetCal + i32Temp) > 0x3FFF)
        u32NewCalVal = 0x3FFF;                 // Max positive offset adjustment allowed
     else
       u32NewCalVal = FactoryOffsetCal + i32Temp;  // Add offset adjustment to factory cal value
  }
  else                                         // No adjustment needed
    u32NewCalVal = FactoryOffsetCal;

  pADI_AFE->CALDATLOCK = 0xDE87A5AF;           // Write to unlock key to gain access to Calibration registers
  
  if (CHAN_NUM == 0)
    pADI_AFE->ADCOFFSETLPTIA0 = u32NewCalVal;
  else
    pADI_AFE->ADCOFFSETLPTIA1 = u32NewCalVal;
  
  return u32NewCalVal;
  
}
void SetupMeasureHsTia(uint8_t RTIA2_SEL)
{
    uint8_t u8Res_Sel = 0;  
    
    u8Res_Sel = RTIA2_SEL;
  
      switch(u8Res_Sel)
    {
       case 0:                                 // SE0 Input to measure across RTIA2 gain resistor
          //      Closes DR0, PR0, NR1, T5(CHAN0) or T7(CHAN1) & T9 to connect HSTIA to SE0 or SE1 pin
          // Also want to tie off Excitation Amp
          pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_T9 |
               BITM_AFE_TSWFULLCON_T5;         // Close T5 for SE0
         pADI_AFE->NSWFULLCON = 
            BITM_AFE_NSWFULLCON_NR1;           // Connect RCAL1 to N-Node of excitation Amp
         pADI_AFE->PSWFULLCON = 
            BITM_AFE_PSWFULLCON_PR0;           // Connect RCAL0 to P-Node of excitation amp  
         pADI_AFE->DSWFULLCON = 
            BITM_AFE_DSWFULLCON_DR0;           // Connect D node to RCAL0
         pADI_AFE->SWCON = 0x10000;            // Switches controlled by their own FULLCON registers 
         pADI_AFE->DE0RESCON = 0xFF;           // disconnect RES2_3 gain resistors
         pADI_AFE->DE1RESCON = 0xFF;           // disconnect RES2_5 gain resistors         
         break;
       case 1:                                 // DE0 input to measure across RTIA2_03
          //      Closes DR0, PR0, NR1, T10 to connect HSTIA to DE0 pin
          // Also want to tie off Excitation Amp
          pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_T10;        // Close T10 for dE0
         pADI_AFE->NSWFULLCON = 
            BITM_AFE_NSWFULLCON_NR1;           // Connect RCAL1 to N-Node of excitation Amp
         pADI_AFE->PSWFULLCON = 
            BITM_AFE_PSWFULLCON_PR0;           // Connect RCAL0 to P-Node of excitation amp  
         pADI_AFE->DSWFULLCON = 
            BITM_AFE_DSWFULLCON_DR0;           // Connect D node to RCAL0
         pADI_AFE->SWCON = 0x10000;            // Switches controlled by their own FULLCON registers 
         pADI_AFE->HSRTIACON |= 0xF;           // open HP RTIA switch
         pADI_AFE->DE1RESCON = 0xFF;           // disconnect RES2_5 gain resistors
         break;
      case 2:  
          //      Closes DR0, PR0, NR1, T11 to connect HSTIA to DE1 pin
          // Also want to tie off Excitation Amp
          pADI_AFE->TSWFULLCON = 
               BITM_AFE_TSWFULLCON_T11;        // Close T11 for DE1
         pADI_AFE->NSWFULLCON = 
            BITM_AFE_NSWFULLCON_NR1;           // Connect RCAL1 to N-Node of excitation Amp
         pADI_AFE->PSWFULLCON = 
            BITM_AFE_PSWFULLCON_PR0;           // Connect RCAL0 to P-Node of excitation amp  
         pADI_AFE->DSWFULLCON = 
            BITM_AFE_DSWFULLCON_DR0;           // Connect D node to RCAL0
         pADI_AFE->SWCON = 0x10000;            // Switches controlled by their own FULLCON registers 
         pADI_AFE->HSRTIACON |= 0xF;           // open HP RTIA switch
         pADI_AFE->DE0RESCON = 0xFF;           // disconnect RES2_5 gain resistors
         break;
    default:
      break;
    }
}


