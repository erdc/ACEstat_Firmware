/**
 *****************************************************************************
   @addtogroup tia
   @{
   @file       TiaLib.c
   @brief      Set of Tia peripheral functions.

   @internal   002 @endinternal
   @version    V0.1
	@author     ADI
	@date       November 2015
   @par Revision History:
   - V0.1, August 2013: initial version.


All files provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/

#include	"AfeTiaLib.h"

const uint32_t ulprtia_ohm[] =
{
   0xFFFFFFFF,200,1000,2000,3000,4000,6000,8000,10000,
   12000,16000,20000,24000,30000,32000,40000,48000,64000,
   85000,96000,100000,120000,128000,160000,196000,256000,
   512000
};
const uint32_t hprtiase_ohm[] =
{
   200,1000,5000,10000,20000,40000,80000,160000,0xFFFFFFFF
};
const uint32_t hprtiade_ohm[] =
{
   50,100,200,1000,5000,10000,20000,40000,80000,160000,0xFFFFFFFF
};

/*********************************************************************/
/*                Ultral low power TIA and PA                        */
/*   Related registers:                                              */
/*                      LPTIASWx                                    */
/*                      LPTIACONx                                   */
/*   These two registers control the TIA amplifier and potentiostat  */
/*   amplifier, basicly used for bias gas sensor and convert current */
/*   which produced from sensor to voltage.                          */
/*********************************************************************/

/**
   @brief uint32_t AfeLpTiaSwitchCfg(uint8_t channel,ULPTIA_SWMODE_TypeDef Mode)
          ======configure switches of Low power tia
   @param channel : {CHAN0,CHAN1}
      - 0 or CHAN0, channel 0
      - 1 or CHAN1, channel 1
   @param Mode : {SWMODE_OFF,SWMODE_NORM,SWMODE_NOISECANCEL,SWMODE_DIODE,SWMODE_SHORT,SWMODE_AC,
                  SWMODE_RAMP,SWMODE_HPCAPA,SWMODE_LPCAPA,SWMODE_DUALSNS0,SWMODE_DUALSNS1,SWMODE_EXTRES,
                  SWMODE_RESISTOR,SWMODE_EDASIG,SWMODE_EDARCAL,SWMODE_EDASIG_EXTRES,SWMODE_EDARCAL_EXTRES,
                  SWMODE_ECG,SWMODE_2LEAD}
   @return register LPTIASW.
   @note typically, use SWMODE_NORM for electrochemical sensor application
*/
uint32_t AfeLpTiaSwitchCfg(uint8_t channel,ULPTIA_SWMODE_TypeDef Mode)
{
   if(channel>0)/*channel 1 configuration*/
   {
      pADI_AFE->LPTIASW1 = Mode;
      return pADI_AFE->LPTIASW1;
   }
   else  /*channel 0 configuration*/
   {
      pADI_AFE->LPTIASW0 = Mode;
      return pADI_AFE->LPTIASW0;
   }
}


/**
   @brief uint32_t AfeLpTiaCon(uint8_t uiChan, LPTIA_RLOAD_Type Rload,LPTIA_RGAIN_Type Gain,LPTIA_RF_Type Rf)
          ======set tia load resistor, gain resistor and LPF filter resistor
   @param uiChan : {CHAN0,CHAN1}
      - 0 or CHAN0, channel 0
      - 1 or CHAN1, channel 1
   @param Rload :{TIA_RLOAD_0,TIA_RLOAD_10,TIA_RLOAD_50,TIA_RLOAD_100,TIA_RLOAD_1600
                  TIA_RLOAD_3100,TIA_RLOAD_3600}
      - LPTIA_RLOAD_0,       RLOAD = 0 ohm
      - LPTIA_RLOAD_10,     RLOAD = 10 ohm
      - LPTIA_RLOAD_30,      RLOAD = 30 ohm
      - LPTIA_RLOAD_50,      RLOAD = 50 ohm
      - LPTIA_RLOAD_100,     RLOAD = 100 ohm
      - LPTIA_RLOAD_1600,    RLOAD = 1600 ohm
      - LPTIA_RLOAD_3100,    RLOAD = 3100 ohm
      - LPTIA_RLOAD_3600,    RLOAD = 3600 ohm
   @param Gain :{LPTIA_RGAIN_DISCONNECT,LPTIA_RGAIN_200,LPTIA_RGAIN_1K,LPTIA_RGAIN_2K,LPTIA_RGAIN_3K,
                  LPTIA_RGAIN_4K,LPTIA_RGAIN_6K,LPTIA_RGAIN_8K,LPTIA_RGAIN_10K,LPTIA_RGAIN_12K,LPTIA_RGAIN_16K,LPTIA_RGAIN_20K,
                  LPTIA_RGAIN_24K,LPTIA_RGAIN_30K,LPTIA_RGAIN_32K,LPTIA_RGAIN_40K,LPTIA_RGAIN_48K,LPTIA_RGAIN_64K,LPTIA_RGAIN_85K,
                  LPTIA_RGAIN_96K,LPTIA_RGAIN_100K,LPTIA_RGAIN_120K,LPTIA_RGAIN_128K,LPTIA_RGAIN_160K,LPTIA_RGAIN_196K,
                  LPTIA_RGAIN_256K,LPTIA_RGAIN_512K, }
   @param Rf :{LPTIA_RFILTER_DISCONNECT,LPTIA_RFILTER_BYPASS,LPTIA_RFILTER_20K,LPTIA_RFILTER_100K,
               LPTIA_RFILTER_200K,LPTIA_RFILTER_400K,LPTIA_RFILTER_600K,LPTIA_RFILTER_1M}
      - LPTIA_RFILTER_DISCONNECT = 0U; disconnect LPTIA output from LPF pin
      - LPTIA_RFILTER_BYPASS,     bypass resistor of the low pass filter
      - LPTIA_RFILTER_20K,     RFILTER = 20K ohm
      - LPTIA_RFILTER_100K,     RFILTER = 100K ohm
      - LPTIA_RFILTER_200K,     RFILTER = 200K ohm
      - LPTIA_RFILTER_400K,    RFILTER = 400K ohm
      - LPTIA_RFILTER_600K,    RFILTER = 600K ohm
      - LPTIA_RFILTER_1M,      RFILTER = 1000K ohm
   @return register LPTIACON.
*/
uint32_t AfeLpTiaCon(uint8_t uiChan, LPTIA_RLOAD_Type Rload,LPTIA_RGAIN_Type Gain,LPTIA_RF_Type Rf)
{
   uint32_t reg;
   if(uiChan>0)  /*channel 1 configuration*/
   {
      reg = pADI_AFE->LPTIACON1;
      reg &= (~(BITM_AFE_LPTIACON1_TIARF|BITM_AFE_LPTIACON1_TIARL\
               |BITM_AFE_LPTIACON1_TIAGAIN));
      reg |= (Rload<<BITP_AFE_LPTIACON1_TIARL)|(Gain<<BITP_AFE_LPTIACON1_TIAGAIN)\
             |(Rf<<BITP_AFE_LPTIACON1_TIARF);
      pADI_AFE->LPTIACON1 = reg;
      return pADI_AFE->LPTIACON1;
   }
   else  /*channel 0 configuration*/
   {
      reg = pADI_AFE->LPTIACON0;
      reg &= (~(BITM_AFE_LPTIACON0_TIARF|BITM_AFE_LPTIACON0_TIARL\
               |BITM_AFE_LPTIACON0_TIAGAIN));
      reg |= (Rload<<BITP_AFE_LPTIACON0_TIARL)|(Gain<<BITP_AFE_LPTIACON0_TIAGAIN)\
             |(Rf<<BITP_AFE_LPTIACON0_TIARF);
      pADI_AFE->LPTIACON0 = reg;
      return pADI_AFE->LPTIACON0;
   }
}

/**
   @brief uint32_t AfeLpTiaPwrDown(uint8_t Chan, uint32_t Tia_Pa)
          ======power up/down TIA or PA
   @param channel : {CHAN0,CHAN1}
      - 0 or CHAN0, channel 0
      - 1 or CHAN1, channel 1
   @param Tia_Pa :{BITM_AFE_LPTIACON0_PAPDEN|BITM_AFE_LPTIACON0_TIAPDEN}
      - BITM_AFE_LPTIACON0_PAPDEN, use this to power down Potentialstat amplifier
      - BITM_AFE_LPTIACON0_TIAPDEN, use this to power down Low power TIA
      - 0, power up TIA and PA
   @return register LPTIACON.
*/
uint32_t AfeLpTiaPwrDown(uint8_t Chan, uint32_t Tia_Pa)
{
   uint32_t reg;
   if (Chan>0) //channel 1
   {
      reg = pADI_AFE->LPTIACON1;
      reg &= (~(BITM_AFE_LPTIACON0_PAPDEN|BITM_AFE_LPTIACON0_TIAPDEN));
      reg |= Tia_Pa;
      pADI_AFE->LPTIACON1 = reg;
      return pADI_AFE->LPTIACON1;
   }
   else
   {
      reg = pADI_AFE->LPTIACON0;
      reg &= (~(BITM_AFE_LPTIACON0_PAPDEN|BITM_AFE_LPTIACON0_TIAPDEN));
      reg |= Tia_Pa;
      pADI_AFE->LPTIACON0 = reg;
      return pADI_AFE->LPTIACON0;
   }
}

/**
   @brief uint32_t AfeLpTiaAdvanced(uint8_t Chan, uint32_t bandwidth, uint32_t current)
          ======Advanced option that can set ouput stage current and bandwidth of amplifier
   @param Chan : {CHAN0,CHAN1}
      - 0 or CHAN0, channel 0
      - 1 or CHAN1, channel 1
   @param bandwidth: {BANDWIDTH_NORMAL,BANDWIDTH_DOUBLE}
      - BANDWIDTH_NORMAL, amplifier has about 30KHz bandwidth
      - BANDWIDTH_DOUBLE. amplifier has about 60KHz bandwidth
   @param current : {CURRENT_HALF, IBOOST_NOR, IBOOST_INCC, IBOOST_DBLC, IBOOST_INCC_DBLC}
      - CURRENT_HALF,  half amplifier output stage current, about 375 uA
      - CURRENT_NOR, normal mode for amplifier output stage current , about 750uA
      - CURRENT_BOOST, increse output stage current for large load current and big capacitor load. about 2.25mA
   @return register LPTIACON.
*/
uint32_t AfeLpTiaAdvanced(uint8_t Chan, uint32_t bandwidth, uint32_t current)
{
   uint32_t reg;
   if (Chan>0) //channel 1
   {
      reg = pADI_AFE->LPTIACON1;
      reg &= (~(BITM_AFE_LPTIACON0_IBOOST|BITM_AFE_LPTIACON0_HALFPWR));
      reg |= bandwidth|current;
      pADI_AFE->LPTIACON1 = reg;
      return pADI_AFE->LPTIACON1;
   }
   else
   {
      reg = pADI_AFE->LPTIACON0;
      reg &= (~(BITM_AFE_LPTIACON0_IBOOST|BITM_AFE_LPTIACON0_HALFPWR));
      reg |= bandwidth|current;
      pADI_AFE->LPTIACON0 = reg;
      return pADI_AFE->LPTIACON0;
   }
}


/********************************************************************/
/*                  High power TIA & Switch Matrix                  */
/********************************************************************/
/*RTIA can be open */
static const uint8_t RloadTiaCfg[HPTIADE_RLOAD_OPT_NUM][HPTIADE_RTIA_OPT_NUM] =
{
   0x00	,0x18	,0x38	,0x58	,0x60	,0x68  ,0x70  ,0x78  ,0x80  ,0x88   ,0xFF
   ,0x09	,0x21	,0x39	,0x59	,0x61	,0x69  ,0x71  ,0x79  ,0x81  ,0x89   ,0xFF
   ,0x12	,0x2A	,0x4A	,0x5A	,0x62	,0x6A  ,0x72  ,0x7A  ,0x82  ,0x8A   ,0xFF
   ,0x1B	,0x33	,0x4B	,0x5B	,0x63	,0x6B  ,0x73  ,0x7B  ,0x83  ,0x8B   ,0xFF
   ,0x34	,0x3C	,0x54	,0x5C	,0x64	,0x6C  ,0x74  ,0x7C  ,0x84  ,0x8C   ,0xFF
   ,0xFF ,0xFF ,0xFF ,0xFF ,0xFF ,0xFF  ,0xFF  ,0xFF  ,0xFF  ,0xFF   ,0xFF
};

/* RLOAD value of DE path*/
const uint8_t uiValRload[HPTIADE_RLOAD_OPEN] = {0, 10, 30, 50, 100};

/* RTIA value of DE path divided by 10 */
const uint16_t uiValRtia_10[HPTIADE_RLOAD_OPEN][HPTIADE_RTIA_OPEN] =
{
  5, 10, 20, 110, 510, 1010, 2010, 4010, 8010, 16010,
  5, 10, 19, 109, 509, 1009, 2009, 4009, 8009, 16009,
  5, 10, 21, 107, 507, 1007, 2007, 4007, 8007, 16007,
  5, 10, 19, 105, 505, 1005, 2005, 4005, 8005, 16005,
  5, 10, 20, 100, 500, 1000, 2000, 4000, 8000, 16000
};

/**
   @brief uint32_t AfeHpTiaPwrUp(bool_t Flag)
            ======enable or disable TIAEN of AFECON, enable HP TIA
   @param Flag :{true,false}
      -0 or false, disable HP TIA
      -1 or true, enable HP TIA
   @return register pADI_AFE->AFECON;
*/
uint32_t AfeHpTiaPwrUp(bool_t Flag)
{
   if(Flag>0)
   {
      pADI_AFE->AFECON |= BITM_AFE_AFECON_TIAEN;
   }
   else
   {
      pADI_AFE->AFECON &= (~BITM_AFE_AFECON_TIAEN);
   }

   return pADI_AFE->AFECON;
}

/**
   @brief uint32_t AfeHpTiaSeCfg(HPTIASE_RTIA_Type Rtia, uint16_t Ctia, uint16_t DioSel)
          ======configure HP_TIA when it connected to SE node
   @param iRtia : {HPTIA_RTIA_200,HPTIA_RTIA_1K,HPTIA_RTIA_5K,HPTIA_RTIA_10K,HPTIA_RTIA_20K \n
                     HPTIA_RTIA_40K,HPTIA_RTIA_80K,HPTIA_RTIA_160K,}
      - HPTIASE_RTIA_200 = 0U, rtia = 200 ohm
      - HPTIASE_RTIA_1K,  rtia = 1K ohm
      - HPTIASE_RTIA_5K,  rtia = 5K ohm
      - HPTIASE_RTIA_10K, rtia = 10K ohm
      - HPTIASE_RTIA_20K, rtia = 20K ohm
      - HPTIASE_RTIA_40K, rtia = 40K ohm
      - HPTIASE_RTIA_80K, rtia = 80K ohm
      - HPTIASE_RTIA_160K,rtia = 160K ohm
      - HPTIASE_RTIA_OPEN,  all switch open, no inner rtia connected
   @param Ctia :{BITM_HPTIA_CTIA_1PF|BITM_HPTIA_CTIA_2PF|BITM_HPTIA_CTIA_4PF| \n
                  BITM_HPTIA_CTIA_8PF|BITM_HPTIA_CTIA_16PF|BITM_HPTIA_CTIA_2PFS}
      - BITM_HPTIA_CTIA_1PF, (0x0020U)    1pf ctia connected
      - BITM_HPTIA_CTIA_2PF,   (0x0040U)     2pf ctia connected
      - BITM_HPTIA_CTIA_4PF,   (0x0080U)     4pf ctia connected
      - BITM_HPTIA_CTIA_8PF,   (0x0100U)     8pf ctia connected
      - BITM_HPTIA_CTIA_16PF,  (0x0200u)    16pf ctia connected
      - BITM_HPTIA_CTIA_2PFS,  (0x0400u)    second 2pf ctia connected
   @param Diosel : {0, BITM_AFE_HSRTIACON_TIASW6CON}
      - 0, not use diode in parallel with rtia
      - BITM_AFE_HSRTIACON_TIASW6CON, diode in parallel with rtia
   @return register HSRTIACON.
*/
uint32_t AfeHpTiaSeCfg(HPTIASE_RTIA_Type Rtia,uint16_t Ctia, uint16_t DioSel)
{
   pADI_AFE->HSRTIACON = (Rtia|Ctia|DioSel);
   return pADI_AFE->HSRTIACON;
}

/**
   @brief uint32_t AfeHpTiaDeCfg(uint8_t Chan,HPTIADE_RLOAD_Type Load,HPTIADE_RTIA_Type Rtia)
          ======configure HP_TIA when it connected to DE node
   @param Chan :{0,1}
      - 0, configure Rload03 when connected to DE0
      - 1, Configure Rload05 when connected to DE1
   @param Load :{HPTIA_RLOAD_0,HPTIA_RLOAD_10,HPTIA_RLOAD_30,HPTIA_RLOAD_50,HPTIA_RLOAD_100,HPTIADE_RLOAD_OPEN}
   @param Rtia :{HPTIA_RTIA_50,HPTIA_RTIA_100,HPTIA_RTIA_200,HPTIA_RTIA_1K,HPTIA_RTIA_5K, \n
                  HPTIA_RTIA_10K,HPTIA_RTIA_20K,HPTIA_RTIA_40K,HPTIA_RTIA_80K,HPTIA_RTIA_160K,
                  HPTIADE_RTIA_OPEN}
   @return register DE1RESCON or DE0RESCON.
   @note when one of HPTIADE_RLOAD_OPEN and HPTIADE_RTIA_OPEN selected, 0xFF will be configured.
         both RLoad and RTia will be disconnect. nomatter what the other parameter is. So it's
         recommended to call the function as this: AfeHpTiaDeCfg(channel, HPTIADE_RLOAD_OPEN,HPTIADE_RTIA_OPEN)
*/
uint32_t AfeHpTiaDeCfg(uint8_t Chan,HPTIADE_RLOAD_Type Load,HPTIADE_RTIA_Type Rtia)
{
   if(Chan>0)  /*set DE1RESCON, HPTIA connected to DE1 node*/
   {
      pADI_AFE->DE1RESCON = RloadTiaCfg[Load][Rtia];
      return pADI_AFE->DE1RESCON;
    }
   else /*set DE0RESCON, HPTIA connected to DE0 node*/
   {
       pADI_AFE->DE0RESCON = RloadTiaCfg[Load][Rtia];
       return pADI_AFE->DE0RESCON;
   }
}

/**
   @brief uint32_t AfeHpTiaCon(uint32_t BiasSel)
          ======set HSTIACON register: power mode and voltage to bias HPTIA
   @param BiasSel : {HPTIABIAS_1V1,HPTIABIAS_VZERO0,HPTIABIAS_VZERO1}
      - 0, 1.1v reference to bias HPTIA
      - 1, VZERO of LPDAC0 connected to positive input of HPTIA
      - 2, VZERO of LPDAC1 connected to positive input of HPTIA
   @return register HSTIACON.
*/
uint32_t AfeHpTiaCon(uint32_t BiasSel)
{
   pADI_AFE->HSTIACON = BiasSel;
   return pADI_AFE->HSTIACON;
}

/**
   @brief uint8_t AfeSwitchFullCfg(SWITCH_GROUP_Type SwitchGroup,uint32_t SwitchID);
          ======configure AFE switch matrix
   @param SwitchGroup :{SWITCH_GROUP_D,SWITCH_GROUP_P,SWITCH_GROUP_N,SWITCH_GROUP_T}
      -SWITCH_GROUP_D, configure switch D
      -SWITCH_GROUP_P, configure switch P
      -SWITCH_GROUP_N, configure switch N
      -SWITCH_GROUP_T, configure switch T
   @param SwitchID :{SWID_DR0_RCAL0|SWID_D2_AIN1|SWID_D3_AIN2|SWID_D4_AIN3|SWID_D5_CE0|SWID_D6_CE1|SWID_D7_WE0|SWID_D8_WE1,
      SWID_PR0_RCAL0|SWID_P2_AIN1|SWID_P3_AIN2|SWID_P4_AIN3|SWID_P5_RE0|SWID_P6_RE1|SWID_P7_WE0|SWID_P8_DE0|SWID_P9_WE1|SWID_P10_DE1|
      SWID_P11_CE0|SWID_P12_CE1|SWID_PL|SWID_PL2,
      SWID_NR1_RCAL1|SWID_N1_AIN0|SWID_N2_AIN1|SWID_N3_AIN2|SWID_N4_AIN3|SWID_N5_SE0RLOAD|SWID_N6_DE0RLOAD|SWID_N7_SE1RLOAD|SWID_N8_DE1RLOAD
      |SWID_N9_WE0|SWID_NL|SWID_NL2,
      SWID_TR1_RCAL1|SWID_T1_AIN0|SWID_T2_AIN1|SWID_T3_AIN2|SWID_T4_AIN3|SWID_T5_SE0RLOAD|SWID_T7_SE1RLOAD|SWID_T9|SWID_T10|SWID_T11,
      SWID_ALLOPEN}
      select which switch will be operated, only IDs in same group can be selected in the same time.eg.SWID_D3|SWID_D8 or SWID_NR1|SWID_NL2.
   @return 1.
**/
uint8_t AfeSwitchFullCfg(SWITCH_GROUP_Type SwitchGroup,uint32_t SwitchID)
{
   /*following instruction only update register value*/
   switch(SwitchGroup)
   {
   case SWITCH_GROUP_D:
      pADI_AFE->DSWFULLCON = SwitchID;
      break;
   case SWITCH_GROUP_P:
      pADI_AFE->PSWFULLCON = SwitchID;
      break;
   case SWITCH_GROUP_N:
      pADI_AFE->NSWFULLCON = SwitchID;
      break;
   case SWITCH_GROUP_T:
      pADI_AFE->TSWFULLCON = SwitchID;
      break;
   }
   /*update switch matrix, after this switches actually switched on/off on circuit*/
   pADI_AFE->SWCON = BITM_AFE_SWCON_SWSOURCESEL;//update switch,
   return 1;
}

/**
   @brief uint8_t AfeSwitchDPNT(uint32_t switchD,uint32_t switchP,uint32_t switchN,uint32_t switchT);
          ======configure AFE switch matrix
   @param switchD :{SWID_DR0_RCAL0|SWID_D2_AIN1|SWID_D3_AIN2|SWID_D4_AIN3|SWID_D5_CE0|SWID_D6_CE1|SWID_D7_WE0|SWID_D8_WE1|SWID_ALLOPEN}
   @param switchP :{SWID_PR0_RCAL0|SWID_P2_AIN1|SWID_P3_AIN2|SWID_P4_AIN3|SWID_P5_RE0|SWID_P6_RE1|SWID_P7_WE0|SWID_P8_DE0|SWID_P9_WE1|SWID_P10_DE1|
         SWID_P11_CE0|SWID_P12_CE1|SWID_PL|SWID_PL2,|SWID_ALLOPEN}
   @param switchN :{SWID_NR1_RCAL1|SWID_N1_AIN0|SWID_N2_AIN1|SWID_N3_AIN2|SWID_N4_AIN3|SWID_N5_SE0RLOAD|SWID_N6_DE0RLOAD|SWID_N7_SE1RLOAD|SWID_N8_DE1RLOAD
      |  SWID_N9_WE0|SWID_NL|SWID_NL2|SWID_ALLOPEN}
   @param switchT :{SWID_TR1_RCAL1|SWID_T1_AIN0|SWID_T2_AIN1|SWID_T3_AIN2|SWID_T4_AIN3|SWID_T5_SE0RLOAD|SWID_T7_SE1RLOAD|SWID_T9|
         SWID_T10|SWID_T11|SWID_ALLOPEN}
   @return 1.
**/
uint8_t AfeSwitchDPNT(uint32_t switchD,uint32_t switchP,uint32_t switchN,uint32_t switchT)
{
   pADI_AFE->DSWFULLCON = switchD;
   pADI_AFE->PSWFULLCON = switchP;
   pADI_AFE->NSWFULLCON = switchN;
   pADI_AFE->TSWFULLCON = switchT;
   /*update switch matrix, after this switches actually switched on/off on circuit*/
   pADI_AFE->SWCON = BITM_AFE_SWCON_SWSOURCESEL;//update switch,
   return 1;
}

/**@}*/
