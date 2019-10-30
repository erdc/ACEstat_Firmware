/**
 *****************************************************************************
   @file       AfeTiaLib.h
   @brief      Set of TIA peripheral  functions.
               This library contains operation of Low power TIA, High power TIA, and
               Switch matrix.


   @version    V0.1
	@author     ADI
	@date       August 2016
   @par Revision History:
   - V0.1, August 2016: initial version.


All files provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/
#ifndef TIALIB_H
#define TIALIB_H


#ifdef __cplusplus
extern "C" {
#endif

#include "ADuCM355.h"
#include "adi_types.h"

extern const uint32_t ulprtia_ohm[];
extern const uint32_t hprtiase_ohm[];
extern const uint32_t hprtiade_ohm[];


/* ########################### Definitions and Macro ###################### */
typedef enum
{
   LPTIA_RLOAD_0 = 0U, /*RLOAD = 0 ohm*/
   LPTIA_RLOAD_10,     /*RLOAD = 10 ohm*/
   LPTIA_RLOAD_30,     /*RLOAD = 30 ohm*/
   LPTIA_RLOAD_50,     /*RLOAD = 50 ohm*/
   LPTIA_RLOAD_100,    /*RLOAD = 100 ohm*/
   LPTIA_RLOAD_1600,   /*RLOAD = 1600 ohm*/
   LPTIA_RLOAD_3100,   /*RLOAD = 3100 ohm*/
   LPTIA_RLOAD_3600,   /*RLOAD = 3600 ohm*/
}LPTIA_RLOAD_Type;
typedef enum
{
   LPTIA_RGAIN_DISCONNECT = 0U, /*disconnect LPTIA Gain resistor*/
   LPTIA_RGAIN_200,     /*RGAIN = 200 ohm*/
   LPTIA_RGAIN_1K,     /*RGAIN = 1K ohm*/
   LPTIA_RGAIN_2K,     /*RGAIN = 2K ohm*/
   LPTIA_RGAIN_3K,    /*RGAIN = 3K ohm*/
   LPTIA_RGAIN_4K,   /*RGAIN = 4K ohm*/
   LPTIA_RGAIN_6K,   /*RGAIN = 6K ohm*/
   LPTIA_RGAIN_8K,   /*RGAIN = 8K ohm*/
   LPTIA_RGAIN_10K,     /*RGAIN = 10K ohm*/
   LPTIA_RGAIN_12K,     /*RGAIN = 12K ohm*/
   LPTIA_RGAIN_16K,     /*RGAIN = 16K ohm*/
   LPTIA_RGAIN_20K,    /*RGAIN = 20K ohm*/
   LPTIA_RGAIN_24K,   /*RGAIN = 24K ohm*/
   LPTIA_RGAIN_30K,   /*RGAIN = 30K ohm*/
   LPTIA_RGAIN_32K,   /*RGAIN = 32K ohm*/
   LPTIA_RGAIN_40K,     /*RGAIN = 40K ohm*/
   LPTIA_RGAIN_48K,     /*RGAIN = 48K ohm*/
   LPTIA_RGAIN_64K,     /*RGAIN = 64K ohm*/
   LPTIA_RGAIN_85K,    /*RGAIN = 85K ohm*/
   LPTIA_RGAIN_96K,   /*RGAIN = 96K ohm*/
   LPTIA_RGAIN_100K,   /*RGAIN = 100K ohm*/
   LPTIA_RGAIN_120K,   /*RGAIN = 120K ohm*/
   LPTIA_RGAIN_128K,     /*RGAIN = 128K ohm*/
   LPTIA_RGAIN_160K,    /*RGAIN = 160K ohm*/
   LPTIA_RGAIN_196K,   /*RGAIN = 196K ohm*/
   LPTIA_RGAIN_256K,   /*RGAIN = 256K ohm*/
   LPTIA_RGAIN_512K,   /*RGAIN = 512K ohm*/
}LPTIA_RGAIN_Type;
typedef enum
{
   LPTIA_RFILTER_DISCONNECT = 0U, /*disconnect LPTIA output from LPF pin*/
   LPTIA_RFILTER_BYPASS,     /*bypass resistor of the low pass filter*/
   LPTIA_RFILTER_20K,     /*RFILTER = 20K ohm*/
   LPTIA_RFILTER_100K,     /*RFILTER = 100K ohm*/
   LPTIA_RFILTER_200K,    /*RFILTER = 200K ohm*/
   LPTIA_RFILTER_400K,   /*RFILTER = 400K ohm*/
   LPTIA_RFILTER_600K,   /*RFILTER = 600K ohm*/
   LPTIA_RFILTER_1M,   /*RFILTER = 1Meg ohm*/
}LPTIA_RF_Type;

#define  CHOP_LPTIA  0x20000
#define  CHOP_PA  0x10000


#define   BITM_HPTIA_CTIA_1PF (1<<BITP_AFE_HSRTIACON_CTIACON)    /*1pf ctia connected*/
#define   BITM_HPTIA_CTIA_2PF   (2<<BITP_AFE_HSRTIACON_CTIACON)     /*2pf ctia connected*/
#define   BITM_HPTIA_CTIA_4PF   (4<<BITP_AFE_HSRTIACON_CTIACON)     /*4pf ctia connected*/
#define   BITM_HPTIA_CTIA_8PF   (8<<BITP_AFE_HSRTIACON_CTIACON)     /*8pf ctia connected*/
#define   BITM_HPTIA_CTIA_16PF  (16<<BITP_AFE_HSRTIACON_CTIACON)    /*16pf ctia connected*/
#define   BITM_HPTIA_CTIA_2PFS  (32<<BITP_AFE_HSRTIACON_CTIACON)    /*second 2pf ctia connected*/
#define   BITM_HPTIA_CTIA_31PF  (0x1F<<BITP_AFE_HSRTIACON_CTIACON)    /*31pF ctia connected*/
#define   BITM_HPTIA_CTIA_OPEN   (0)
#define   AMPPOWER_NORM   (0x0000)
#define   AMPPOWER_HIGH   (0x007C)
#define   HPTIABIAS_1V1   (0u)
#define   HPTIABIAS_VZERO0   (1u)
#define   HPTIABIAS_VZERO1   (2u)



typedef enum
{
   HPTIASE_RTIA_200 = 0u,   /*rtia = 200 ohm*/
   HPTIASE_RTIA_1K,     /*rtia = 1K ohm*/
   HPTIASE_RTIA_5K,     /*rtia = 5K ohm*/
   HPTIASE_RTIA_10K,     /*rtia = 10K ohm*/
   HPTIASE_RTIA_20K,    /*rtia = 20K ohm*/
   HPTIASE_RTIA_40K,   /*rtia = 40K ohm*/
   HPTIASE_RTIA_80K,   /*rtia = 80K ohm*/
   HPTIASE_RTIA_160K,   /*rtia = 160K ohm*/
   HPTIASE_RTIA_OPEN,  /*all switch open, no inner rtia connected*/
}HPTIASE_RTIA_Type;
typedef enum
{
   HPTIADE_RTIA_50 = 0U,  /*rtia = 50 ohm*/
   HPTIADE_RTIA_100,   /*rtia = 100 ohm*/   //50 and 100 ohm are not applicable for RTIA02
   HPTIADE_RTIA_200,   /*rtia = 200 ohm*/
   HPTIADE_RTIA_1K,     /*rtia = 1K ohm*/
   HPTIADE_RTIA_5K,     /*rtia = 5K ohm*/
   HPTIADE_RTIA_10K,     /*rtia = 10K ohm*/
   HPTIADE_RTIA_20K,    /*rtia = 20K ohm*/
   HPTIADE_RTIA_40K,   /*rtia = 40K ohm*/
   HPTIADE_RTIA_80K,   /*rtia = 80K ohm*/
   HPTIADE_RTIA_160K,   /*rtia = 160K ohm*/
   HPTIADE_RTIA_OPEN  /*all switch open, no inner rtia connected*/
}HPTIADE_RTIA_Type;
#define HPTIADE_RTIA_OPT_NUM (HPTIADE_RTIA_OPEN+1)
typedef enum
{
   HPTIADE_RLOAD_0 = 0U, /*rload = 0 ohm*/
   HPTIADE_RLOAD_10,     /*rload = 10 ohm*/
   HPTIADE_RLOAD_30,     /*rload = 30 ohm*/
   HPTIADE_RLOAD_50,     /*rload = 50 ohm*/
   HPTIADE_RLOAD_100,    /*rload = 100 ohm*/
   HPTIADE_RLOAD_OPEN
}HPTIADE_RLOAD_Type;
#define HPTIADE_RLOAD_OPT_NUM (HPTIADE_RLOAD_OPEN+1)


//switch matrix Macro
typedef enum
{
   SWITCH_GROUP_D = 0U, /*switch group D*/
   SWITCH_GROUP_P,      /*switch group P*/
   SWITCH_GROUP_N,      /*switch group N*/
   SWITCH_GROUP_T,      /*switch group T*/
}SWITCH_GROUP_Type;

/*switch ID define*/
#define SWID_ALLOPEN	0u
#define SWID_DR0_RCAL0  BITM_AFE_DSWFULLCON_DR0
#define SWID_D2_AIN1   BITM_AFE_DSWFULLCON_D2
#define SWID_D3_AIN2   BITM_AFE_DSWFULLCON_D3
#define SWID_D4_AIN3   BITM_AFE_DSWFULLCON_D4
#define SWID_D5_CE0   BITM_AFE_DSWFULLCON_D5
#define SWID_D6_CE1   BITM_AFE_DSWFULLCON_D6
#define SWID_D7_WE0   BITM_AFE_DSWFULLCON_D7
#define SWID_D8_WE1   BITM_AFE_DSWFULLCON_D8

#define SWID_PR0_RCAL0  BITM_AFE_PSWFULLCON_PR0
#define SWID_P2_AIN1   BITM_AFE_PSWFULLCON_P2
#define SWID_P3_AIN2   BITM_AFE_PSWFULLCON_P3
#define SWID_P4_AIN3   BITM_AFE_PSWFULLCON_P4
#define SWID_P5_RE0   BITM_AFE_PSWFULLCON_P5
#define SWID_P6_RE1   BITM_AFE_PSWFULLCON_P6
#define SWID_P7_WE0   BITM_AFE_PSWFULLCON_P7
#define SWID_P8_DE0   BITM_AFE_PSWFULLCON_P8
#define SWID_P9_WE1   BITM_AFE_PSWFULLCON_P9
#define SWID_P10_DE1  BITM_AFE_PSWFULLCON_P10
#define SWID_P11_CE0  BITM_AFE_PSWFULLCON_P11
#define SWID_P12_CE1  BITM_AFE_PSWFULLCON_P12
#define SWID_PL   BITM_AFE_PSWFULLCON_PL
#define SWID_PL2  BITM_AFE_PSWFULLCON_PL2

#define SWID_NR1_RCAL1  BITM_AFE_NSWFULLCON_NR1
#define SWID_N1_AIN0   BITM_AFE_NSWFULLCON_N1
#define SWID_N2_AIN1   BITM_AFE_NSWFULLCON_N2
#define SWID_N3_AIN2   BITM_AFE_NSWFULLCON_N3
#define SWID_N4_AIN3   BITM_AFE_NSWFULLCON_N4
#define SWID_N5_SE0RLOAD   BITM_AFE_NSWFULLCON_N5
#define SWID_N6_DE0RLOAD   BITM_AFE_NSWFULLCON_N6
#define SWID_N7_SE1RLOAD   BITM_AFE_NSWFULLCON_N7
#define SWID_N8_DE1RLOAD   BITM_AFE_NSWFULLCON_N8
#define SWID_N9_WE0   BITM_AFE_NSWFULLCON_N9
#define SWID_NL   BITM_AFE_NSWFULLCON_NL
#define SWID_NL2  BITM_AFE_NSWFULLCON_NL2

#define SWID_TR1_RCAL1  BITM_AFE_TSWFULLCON_TR1
#define SWID_T1_AIN0   BITM_AFE_TSWFULLCON_T1
#define SWID_T2_AIN1   BITM_AFE_TSWFULLCON_T2
#define SWID_T3_AIN2   BITM_AFE_TSWFULLCON_T3
#define SWID_T4_AIN3   BITM_AFE_TSWFULLCON_T4
#define SWID_T5_SE0RLOAD   BITM_AFE_TSWFULLCON_T5
#define SWID_T7_SE1RLOAD   BITM_AFE_TSWFULLCON_T7
#define SWID_T9   BITM_AFE_TSWFULLCON_T9
#define SWID_T10  BITM_AFE_TSWFULLCON_T10
#define SWID_T11  BITM_AFE_TSWFULLCON_T11
#define SWID_T6_DE0  (1u<<5)
#define SWID_T8_DE1  (1u<<7)

typedef enum
{
   SWITCH_OPEN   = 0U,
   SWITCH_CLOSE,
}SWITCH_STATUS_Type;

#ifndef CHAN0
#define CHAN0  (0x0)
#endif
#ifndef CHAN1
#define CHAN1  (0x1)
#endif


typedef enum
{
   SWMODE_OFF = 0x0,  //ULP TIA off
   SWMODE_NORM = 0x302c,  //normal mode for all types of gas sensors
   SWMODE_NOISECANCEL = 0x306C, //enable noise cancellation, only useful for zero-biased gas sensor
   SWMODE_DIODE = 0x302D, //diode protection
   SWMODE_SHORT = 0x302F, //short switch for very large current to avoid saturation
   SWMODE_AC = 0x3180, //for AC impedance measurement
   SWMODE_RAMP = 0x0094,  //RAMP test on DE/SE
   SWMODE_HPCAPA = 0x0094,  //CAPA test with High power TIA
   SWMODE_LPCAPA = 0x0014,  //CAPA test with Low power TIA
   SWMODE_DUALSNS0 = 0x702C,  //tia0 switch mode for dual gas sensor
   SWMODE_DUALSNS1 = 0x0020,  //tia1 switch mode for dual gas sensor
   SWMODE_EXTRES = 0x322C,   //work mode with external RTIA for all types of gas sensors
   SWMODE_RESISTOR = 0x3820, //Rister measuring in test
   SWMODE_EDASIG = 0x6424,   //EDA signal measurement
   SWMODE_EDARCAL = 0xE034,  //EDA R_CAL measurement
   SWMODE_EDASIG_EXTRES = 0x6624,  //EDA signal measurement with external resitor
   SWMODE_EDARCAL_EXTRES = 0xE234, //EDA R_CAL measurement wiht external resistor
   SWMODE_ECG = 0x0000, //ECG signal measurement mode
   SWMODE_2LEAD = 0x3024,   //3 lead sensor, two lead mode
}ULPTIA_SWMODE_TypeDef;

#define BANDWIDTH_NORMAL         0
#define BANDWIDTH_DOUBLE         0x0010
#define CURRENT_HALF             0x0004
#define CURRENT_NOR              0
#define CURRENT_BOOST            0x0008


#ifndef EOL
#define  EOL   "\r\n"
#endif

#define PRINT_RLOAD(l) printf(#l ",%d,%d" EOL, (int)(uiValRload[(l)]), (l));
#define PRINT_HPRTIA(l,t) printf(#t ",%d0,%d" EOL, ((int)uiValRtia_10[(l)][(t)]), (t));

/* RLOAD value */
extern const uint8_t uiValRload[HPTIADE_RLOAD_OPEN];

/* RTIA value divided by 10 */
extern const uint16_t uiValRtia_10[HPTIADE_RLOAD_OPEN][HPTIADE_RTIA_OPEN];

/* ########################### Function API ######################## */
extern   uint32_t AfeLpTiaPwrDown(uint8_t Chan, uint32_t Tia_Pa);
extern   uint32_t AfeLpTiaCon(uint8_t uiChan, LPTIA_RLOAD_Type Rload,LPTIA_RGAIN_Type Gain,LPTIA_RF_Type Rf);
extern   uint32_t AfeLpTiaSwitchCfg(uint8_t channel,uint16_t Mode);
extern   uint32_t AfeLpTiaAdvanced(uint8_t Chan, uint32_t bandwidth, uint32_t current);

extern   uint32_t AfeHpTiaPwrUp(bool_t Flag);
extern   uint32_t AfeHpTiaSeCfg(HPTIASE_RTIA_Type Rtia,uint16_t Ctia, uint16_t DioSel);
extern   uint32_t AfeHpTiaDeCfg(uint8_t Chan,HPTIADE_RLOAD_Type Load,HPTIADE_RTIA_Type Rtia);
extern   uint32_t AfeHpTiaCon(uint32_t BiasSel);
extern   uint8_t AfeSwitchFullCfg(SWITCH_GROUP_Type SwitchGroup,uint32_t SwitchID);
extern   uint8_t AfeSwitchDPNT(uint32_t switchD,uint32_t switchP,uint32_t switchN,uint32_t switchT);

#ifdef __cplusplus
}
#endif

#endif /*#ifndef TIALIB_H*/
