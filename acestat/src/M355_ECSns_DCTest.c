/**
 *****************************************************************************
   @addtogroup EC sensor
   @{
   @file     M355_ECSns_DCTest.c
   @brief    Set of Electrochemical sensor functions.
   @par Revision History:
   @version  V0.1
   @author   ADI
   @date     Sept 2016
   @par Revision History:
   - V0.1, August 2016: initial version.
   - V0.2, March 2018:
      - Register/bit naming changes
      - HS DAC update calculation changes

   DC current measurement example code.
   UART baud rate - 57600.
   ADuCM355 periodiclly wakeup in 937.5mS
   ADC measure 12 data in 200K sps after wake up, since ADC chopped, it's recommended
   to average each two data.
   CO Sensor expected in Channel 0 (3-lead)
   O2 Sensor expected in Channel 1 (3-lead)
All files for ADuCM355 provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/
#include "M355_ECSns_DCTest.h"

#define SENSOR_MEASRUEMENT_SAMPLE 10
uint16_t DC_Result1[SENSOR_MEASRUEMENT_SAMPLE];
uint16_t DC_Result2[SENSOR_MEASRUEMENT_SAMPLE];


SNS_CFG_Type SnsCfg[2] =
{
   /*Sensor Channel 0*/
   {
      SENSOR_CHANNEL_ENABLE,
      CHAN0,
      1100,
      1100,
      LPTIA_RLOAD_10,
      LPTIA_RGAIN_30K,
      LPTIA_RFILTER_1M,
      "CO"
   },
   /*Sensor Channel 1, used to cancel DC offset for channel 0*/
   {
      0,                //disable at the beginning
      CHAN1,
      1500,
      900,               //actual vbias-vzero is determined by offset of channel 0
      LPTIA_RLOAD_10,   //no use in this test
      LPTIA_RGAIN_1K,   //no use in this test
      LPTIA_RFILTER_1M, //no use in this test
      "O2"
   }
};

SNS_CFG_Type * getSnsCfg(uint32_t channel)
{
   return (SNS_CFG_Type *)(&(SnsCfg[channel]));
}

void SensorInit(void)
{
   if((SnsCfg[0].Enable == SENSOR_CHANNEL_ENABLE))
   {
      printf("%s Sensor Initializing\r\n", SnsCfg[0].SensorName);
      SnsInit(SnsCfg);
      for(uint32_t i=0;i<5000;i++)delay_10us(100);
   }
   if((SnsCfg[1].Enable == SENSOR_CHANNEL_ENABLE))
   {
      printf("%s Sensor Initializing\r\n", SnsCfg[1].SensorName);
      SnsInit(&(SnsCfg[1]));
      for(uint32_t i=0;i<5000;i++)delay_10us(100);
   }
}

/**
   @brief uint8_t SnsInit(SNS_CFG_Type *pSnsCfg)
          ======== Mux setup, bias sensor, load sensor parameters
   @param pSnsCfg :{}
         - pointer to sensor configuration parameters
   @return 1.
*/
uint8_t SnsInit(SNS_CFG_Type *pSnsCfg)
{
   uint16_t Cbias,Czero;
   int32_t Vdiff = 0;
   uint32_t channel = pSnsCfg->channel;
   /*********ULP DAC setup************/
   LPDacPwrCtrl(channel,PWR_UP); /*power up DAC*/

   Vdiff = (int32_t)(pSnsCfg->Vbias - pSnsCfg->Vzero);
   Czero = (uint16_t)((pSnsCfg->Vzero - 200)*63.0/2166+0.5); //DAC code for Vzero
   if(Vdiff == 0)   //none-bias sensor
   {
      Cbias = (uint16_t)((pSnsCfg->Vbias - 200)*4095.0/2200+0.5);
      /*short Vzero to Vbias for none-bias sensor*/
      LPDacCfg(channel, LPDACSWNOR, VBIAS6BIT_VZERO6BIT_SHORT, LPDACREF2P5);
   }
   else
   {
      /*adjust Vbias according to Vzero to make sure Vdiff is accurate*/
      Cbias = (uint16_t)(Czero*64 + (int16_t)(Vdiff*4095.0/2200+0.5));
      LPDacCfg(channel,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);
   }
   LPDacWr(channel,Czero,Cbias);

   for(uint32_t i=0;i<50000;i++);//delay for cap on bias(zero) pin

   /***********ULP TIA/PA setup*************/
   AfeLpTiaPwrDown(channel,0);   //power up PA and TIA.
   //AfeLpTiaAdvanced(channel,BANDWIDTH_NORMAL,CURRENT_BOOST);
   AfeLpTiaSwitchCfg(channel,SWMODE_SHORT);  /*short TIA feedback with diode for Sensor setup*/
   AfeLpTiaCon(channel,(LPTIA_RLOAD_Type)(pSnsCfg->Rload),  \
              (LPTIA_RGAIN_Type)(pSnsCfg->Rtia), (LPTIA_RF_Type)(pSnsCfg->Rfilter));

   for(uint32_t i=0;i<50000;i++);//delay for sensor setup

   AfeLpTiaSwitchCfg(channel,SWMODE_NORM);  /*TIA switch to normal mode for measurement*/

   return 1;
}


/**
   @brief uint8_t SnsMeasure(uint8_t channel, uint16_t *pResult, uint16_t iNumber)
          ======== start DC measurement
   @param channel :{0,1}
         - 0 Sensor channel 0
         - 1 Sensor channel 1
   @param pResult: the pointer to array which stored measured data.
   @param iNumber: {0-65535}
         -  Data number will be measured
   @return 1.
*/

/*
uint8_t SnsMeasure(uint8_t channel, uint16_t *pResult, uint16_t iNumber)
{
   if(channel>0)
      AfeAdcChan(MUXSELP_LPTIA1_LPF,MUXSELN_VSET1P1);
   else
      AfeAdcChan(MUXSELP_LPTIA0_LPF,MUXSELN_VSET1P1);
   AfeSysCfg(ENUM_AFE_PMBW_LP,ENUM_AFE_PMBW_BW50);
   AfeAdcPgaCfg(GNPGA_1,0);
   AfeAdcChopEn(1);
   AfeAdcPwrUp(BITM_AFE_AFECON_ADCEN);
   AfeAdcFiltCfg(SINC3OSR_4,SINC2OSR_178,LFPBYPEN_BYP,ADCSAMPLERATE_800K);
   pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
   pADI_AFE->AFECON |= BITM_AFE_AFECON_ADCEN;
   delay_10us(5);  //50uS
   //start ADC conversion
   AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);

   //Read ADC data
   for(uint16_t ix=0;ix<iNumber;ix++)
   {
      while(!(pADI_AFE->ADCINTSTA&BITM_AFE_ADCINTSTA_ADCRDY));
      pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
      pResult[ix] = pADI_AFE->ADCDAT;
   }

   //power down ADC
   AfeAdcPwrUp(0);
   AfeAdcGo(ADCIDLE);

   return 1;
}


void DC_measure(uint32_t cycles)
{
   uint32_t avg = 0;
   RtcCfgCR0(BITM_RTC_CR0_CNTEN,1);
   printf("<F>DC_Test<S>BeforeAndAfterCal" EOL);
   for(uint32_t i=0;i<cycles-1;i++)
   {
      PwrCfg(ENUM_PMG_PWRMOD_HIBERNATE,MONITOR_VBAT_EN,0);
      if((SnsCfg[0].Enable == SENSOR_CHANNEL_ENABLE))
         SnsMeasure(SnsCfg[0].channel,DC_Result1,SENSOR_MEASRUEMENT_SAMPLE);
      delay_10us(100);  //delay for ADC channel switch
      if((SnsCfg[1].Enable == SENSOR_CHANNEL_ENABLE))
         SnsMeasure(SnsCfg[1].channel,DC_Result2,SENSOR_MEASRUEMENT_SAMPLE);
      AfePwrCfg(AFE_HIBERNATE);        // AFE die entering hibernate

      if((SnsCfg[0].Enable == SENSOR_CHANNEL_ENABLE))
      {
         for(uint16_t ix=0;ix<SENSOR_MEASRUEMENT_SAMPLE;ix++)
         {
            avg += DC_Result1[ix];
         }
         avg = ((avg<<1)/SENSOR_MEASRUEMENT_SAMPLE+1)>>1;
         printf(" %d",avg);
         avg = 0;
      }
      if((SnsCfg[1].Enable == SENSOR_CHANNEL_ENABLE))
      {
         for(uint16_t ix=0;ix<SENSOR_MEASRUEMENT_SAMPLE;ix++)
         {
            avg += DC_Result2[ix];
         }
         avg = ((avg<<1)/SENSOR_MEASRUEMENT_SAMPLE+1)>>1;
         printf(" %d",avg);
      }
      printf(EOL);
   }
   RtcCfgCR0(BITM_RTC_CR0_CNTEN,0);
}

void RtcPeriodicallyWakeUpInit(void)
{
   RtcCfgCR0(BITM_RTC_CR0_CNTEN,0);//disable RTC
   //set initial count value
   RtcSetCnt(0);
   //set prescaler
   RtcSetPre(WAKEUP_PERIOD);
   //Modulo-60 RTC alarm configure
   RtcCfgCR0(BITM_RTC_CR0_MOD60ALMEN|BITM_RTC_CR0_MOD60ALMINTEN,1);//enable mod60 module, enable mod60 alarm
   RtcSetMod60Alarm(0);//set mod60 alarm time
   RtcCfgCR1(BITM_RTC_CR1_CNTMOD60ROLLINTEN,1);
   RtcIntClrSR0(BITM_RTC_SR0_MOD60ALMINT); //clear interrupt source
   // Enable RTC interrupt in NVIC
   NVIC_EnableIRQ(RTC1_EVT_IRQn);
   //Globle enable for the RTC1
   RtcCfgCR0(BITM_RTC_CR0_CNTEN,1);
}

void RTC1_Int_Handler(void)
{
   AfePwrCfg(AFE_ACTIVE);
   if(pADI_RTC1->SR0 & BITM_RTC_SR0_ALMINT) // alarm interrupt
   {
      RtcIntClrSR0(BITM_RTC_SR0_ALMINT); //clear interrupt source
   }
   if(pADI_RTC1->SR2 & BITM_RTC_SR2_PSINT) // prescaled, modulo-1 interrupt
   {
      RtcIntClrSR2(BITM_RTC_SR2_PSINT); //clear interrupt source
   }
   if(pADI_RTC1->SR2 & BITM_RTC_SR2_CNTINT)
   {
      RtcIntClrSR2(BITM_RTC_SR2_CNTINT); //clear interrupt
   }
   if(pADI_RTC1->SR0 & BITM_RTC_SR0_MOD60ALMINT) // mod60 alarm interrupt
   {
      RtcIntClrSR0(BITM_RTC_SR0_MOD60ALMINT); //clear interrupt
   }
   if(pADI_RTC1->SR2 & BITM_RTC_SR2_CNTMOD60ROLLINT)
   {
      RtcIntClrSR2(BITM_RTC_SR2_CNTMOD60ROLLINT); //clear interrupt
   }
   AfeWdtKick();  // restart wdt 
}
*/



/**@}*/
