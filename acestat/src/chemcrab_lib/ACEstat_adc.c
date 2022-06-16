#include "ACEstat_adc.h"
#include "ACEstat_misc.h"

/***************** ADC control and conversion ********************/

#if defined ( __ICCARM__ )
   #pragma location="never_retained_ram"
   uint16_t szADCSamples[MAX_BUFFER_LENGTH];   //32KB SRAM can be used to gather ADC samples,
#elif defined (__CC_ARM)
  uint16_t szADCSamples[MAX_BUFFER_LENGTH] __attribute__((section(".ARM.__at_0x20040000"))); //32KB SRAM can be used to gather ADC samples,
#else
   #pragma message("WARNING: Need to place this variable in a large RAM section using your selected toolchain.")
#endif

void adc_voltage_setup_RE(uint8_t sensor_channel){
    
    /** Initial ADC parameters setup */
    AfeSysCfg(ENUM_AFE_PMBW_LP,ENUM_AFE_PMBW_BW50);
    AfeAdcPgaCfg(GNPGA_1,0);                    //config PGA gain
    
    /** Configure ADC MUX inputs */
    if(sensor_channel > 0){
      AfeAdcChan(MUXSELP_VRE1,MUXSELN_VSET1P1); //select ADC MUX to VRE1(P) and VREFCAP(N)
    }
    else{
      AfeAdcChan(MUXSELP_VRE0,MUXSELN_VSET1P1); //select ADC MUX to VRE0(P) and VREFCAP(N)
    }

    /** Finalize ADC configuration */
    AfeAdcChopEn(1);
    AfeAdcIntCfg(BITM_AFE_ADCINTIEN_ADCRDYIEN); 
    NVIC_EnableIRQ(AFE_ADC_IRQn);               //enable ADC interrupt
    AfeAdcPwrUp(BITM_AFE_AFECON_ADCEN);         
    AfeAdcFiltCfg(SINC3OSR_5,SINC2OSR_178,LFPBYPEN_NOBYP,ADCSAMPLERATE_800K);
    pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
    delay_10us(5);
}

void adc_voltage_setup_SE(uint8_t sensor_channel){
    
    /** Initial ADC parameters setup */
    AfeSysCfg(ENUM_AFE_PMBW_LP,ENUM_AFE_PMBW_BW50);
    AfeAdcPgaCfg(GNPGA_1,0);                    //config PGA gain
    
    /** Configure ADC MUX inputs */
    if(sensor_channel > 0){
      AfeAdcChan(MUXSELP_VSE1,MUXSELN_VSET1P1); //select ADC MUX to VSE1(P) and VREFCAP(N)
    }
    else{
      AfeAdcChan(MUXSELP_VSE0,MUXSELN_VSET1P1); //select ADC MUX to VSE0(P) and VREFCAP(N)
    }
    
    /** Finalize ADC configuration */
    AfeAdcChopEn(1);
    AfeAdcIntCfg(BITM_AFE_ADCINTIEN_ADCRDYIEN);
    NVIC_EnableIRQ(AFE_ADC_IRQn);               //enable ADC interrupt
    AfeAdcPwrUp(BITM_AFE_AFECON_ADCEN);         
    AfeAdcFiltCfg(SINC3OSR_5,SINC2OSR_178,LFPBYPEN_NOBYP,ADCSAMPLERATE_800K);
    pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
    delay_10us(5);
}

void adc_voltage_setup_AIN(uint8_t analog_channel){
    AfeSysCfg(ENUM_AFE_PMBW_LP,ENUM_AFE_PMBW_BW50);
    AfeAdcPgaCfg(GNPGA_1,0);
    
    if(analog_channel == ANALOG_CHAN0){
      AfeAdcChan(MUXSELP_AIN1,MUXSELN_AIN0);
    }
    if(analog_channel == ANALOG_CHAN1){
      AfeAdcChan(MUXSELP_AIN3,MUXSELN_AIN2);
    }
    if(analog_channel == ANALOG_CHAN2){
      AfeAdcChan(MUXSELP_AIN6,MUXSELN_AIN5);
    }
    
    AfeAdcChopEn(1);
    AfeAdcIntCfg(BITM_AFE_ADCINTIEN_ADCRDYIEN);
    NVIC_EnableIRQ(AFE_ADC_IRQn);
    AfeAdcPwrUp(BITM_AFE_AFECON_ADCEN);
    
    AfeAdcFiltCfg(SINC3OSR_5,SINC2OSR_178,LFPBYPEN_BYP,ADCSAMPLERATE_800K);
    pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
    delay_10us(5);
}

void adc_current_setup_lptia(uint8_t sensor_channel){

  AfeAdcPgaCfg(GNPGA_1_5,0);                    //config PGA gain 
  
  /** Configure ADC MUX inputs */
  if(sensor_channel > 0){
    AfeAdcChan(MUXSELP_LPTIA1_P,MUXSELN_LPTIA1_N);      //select ADC MUX to LPTIA1_POS and LPTIA1_NEG
    //AfeAdcChan(MUXSELP_LPTIA1_LPF,MUXSELN_LPTIA1_N);  
  }
  else{
    AfeAdcChan(MUXSELP_LPTIA0_P,MUXSELN_LPTIA0_N);      //select ADC MUX to LPTIA0_POS and LPTIA0_NEG
    //AfeAdcChan(MUXSELP_LPTIA0_LPF,MUXSELN_LPTIA0_N);
  }
  
  /** Finalize ADC configuration */
  AfeAdcChopEn(1);
  AfeAdcIntCfg(BITM_AFE_ADCINTIEN_ADCRDYIEN);
  NVIC_EnableIRQ(AFE_ADC_IRQn);                 //enable ADC interrupt
  AfeAdcPwrUp(BITM_AFE_AFECON_ADCEN);
  AfeAdcFiltCfg(SINC3OSR_5,SINC2OSR_178,LFPBYPEN_NOBYP,ADCSAMPLERATE_800K);
  pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;
  delay_10us(5);
}

float calc_current_lptia(uint16_t adc_data, int RGAIN, int RLOAD){
  /** Conversion formulas from ADuCM355 reference manual */
  int32_t current_adc_scale = adc_data;
  float vv = (current_adc_scale-32768.0)/65536.0*V_ADC_REF_mV*2;
  return vv/(RGAIN-(RLOAD-100)) *1000;
}

float calc_voltage_adc(uint16_t adc_data){
  /** Conversion formulas from ADuCM355 reference manual */
  return (adc_data-32768.0)/65535*3600+1100;
}

uint16_t* return_adc_buffer(void){
	return szADCSamples;
}

uint16_t get_adc_val(void){
  return ADCRAW;
}

void reset_adc_flag(void){
  adcRdy = 0;
}

void set_adc_flag(void){
  adcRdy = 1;
}

void set_adc_mode(uint8_t mode){
  adcModeSel = mode;
}

int oversample_adc(int mode, uint8_t sensor_channel, uint16_t oversample_rate){
  int sum = 0;
  
  /**ADC is sampling from the LPTIA to measure current */
  if(mode == MODE_LPTIA){        
    adc_current_setup_lptia(sensor_channel);
  }
  
  /**ADC is sampling from VREO/VRE1 to reference capacitor*/
  if(mode == MODE_VRE){         
    adc_voltage_setup_RE(sensor_channel);                 
  }
  
  /**ADC is sampling from VZERO to reference capacitor*/
  if(mode == MODE_VZERO){        
    adc_voltage_setup_SE(sensor_channel);  
  }

  /**ADC is sampling from analog input pins*/
  if(mode == MODE_AIN){
    adc_voltage_setup_AIN(sensor_channel);
  }
 
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);          //begin adc conversion
  
  adcRdy = 0;
  /**Record and sum N=oversample_rate samples*/
  for(int i = 0 ; i<oversample_rate ; ++i){
    while(!adcRdy){};
    adcRdy = 0;
    sum = sum + get_adc_val();                  //reading from ADCRAW, which is updated from ADCDAT register
  }

  /**Return average value of N samples*/
  return sum/oversample_rate;
}

float adc_to_voltage(float adc_data){
  /** Conversion formulas from ADuCM355 reference manual*/
  float VREF = 1.82;
  float ADC_MEAS_SHIFT = 0.033;                 //determined empirically 33mV shift to correct ADC error
  float ADCVBIAS_CAP = 1.11 + ADC_MEAS_SHIFT;                         
  return (VREF*((adc_data-32768)/(32768)))+ADCVBIAS_CAP;
}

float adc_to_current(float adcVal, int RTIA){
  /** Conversion formulas from ADuCM355 reference manual*/
  float kFactor = 1.835/1.82;
  float PGA_GAIN = 1.5;
  float fVolt = ((adcVal-32768)/PGA_GAIN)*V_ADC_REF_mV/32768*kFactor;
  return (((fVolt/RTIA*1000)-1));
}

float swv_mov_avg(int width, uint16_t *arr, int pos, uint16_t sample_count, int RTIA){
  
  float sum = 0;
  float ctr = 0;
  
  /**Case where pos is close to beginning of szADCSamples*/
  if(pos < 3*width){
    for(int j=1 ; j<pos+3*width ; j+=3){
      sum += (adc_to_current(arr[j+1],RTIA) - adc_to_current(arr[j],RTIA));
      ++ctr;
    }
  }
  
  /**Case where pos is in the middle of szADCSamples*/
  if(pos>3*width && pos<sample_count-3*width){
    for(int j=pos-3*width ; j<pos+3*width ; j+=3){
      sum += (adc_to_current(arr[j+1],RTIA) - adc_to_current(arr[j],RTIA));
      ++ctr;
    }
  }
  
  /**Case where pos is close to end of szADCSamples*/
  if(pos > sample_count-3*width){
    for(int j=pos-3*width ; j<sample_count ; j+=3){
      sum += (adc_to_current(arr[j+1],RTIA) - adc_to_current(arr[j],RTIA));
      ++ctr;
    }
  }
  
  return sum/ctr;               
}

float cv_mov_avg(int width, uint16_t *arr, int pos, uint16_t sample_count, int RTIA){
  
  float sum = 0;
  float ctr = 0;
  
  /**Case where pos is close to beginning of szADCSamples*/
  if(pos < 2*width){
    for(int j=1 ; j<pos+2*width ; j+=2){
      sum += adc_to_current(arr[j],RTIA);
      ++ctr;
    }
  }
  
  /**Case where pos is in the middle of szADCSamples*/
  if(pos>2*width && pos<sample_count-2*width){
    for(int j=pos-2*width ; j<pos+2*width ; j+=2){
      sum += adc_to_current(arr[j],RTIA);
      ++ctr;
    }
  }
  
  /**Case where pos is close to end of szADCSamples*/
  if(pos > sample_count-2*width){
    for(int j=pos-2*width ; j<sample_count ; j+=2){
      sum += adc_to_current(arr[j],RTIA);
      ++ctr;
    }
  }
  
  return sum/ctr;               
}

/***************** DAC control and conversion ********************/

uint16_t mV_to_DAC(uint16_t mV, uint8_t nBits){
  
  /**Value written to 12bit DAC channel(0.537mV resolution)*/
  if(nBits==12){
    return (int)((mV-200)/0.537);
  }
  /**Value written to 6bit DAC channel(34.38mV resolution)*/
  if(nBits==6){
    return (int)((mV-200)/34.38);
  }
  return 0;
}

float DAC_to_mV(float DAC, uint8_t nBits){
  
  /**Converting to mV from 12b DAC value(0.537mV resolution)*/
  if(nBits==12){
    return (DAC*0.537+200);
  }
  
  /**Converting to mV from 6b DAC value(34.38mV resolution)*/
  if(nBits==6){
    return (DAC*34.38+200);
  }
  return 0;
}

int adjust_DAC(uint16_t vZero, uint16_t vStart, int vDiffTarget, uint8_t sensor_channel){
  /**Set DAC channels to starting values to apply initial diffirential voltage to sensor*/
  LPDacWr(sensor_channel, mV_to_DAC(vZero,6), mV_to_DAC(vStart,12));
  delay_10us(50);                               //DAC settling delay
  
  /**   Measure the differential voltage across the sensor and calculate shift i
        n 12bit channel to compensate for low precision of 6bit channel*/
  float vDiffMeasure = 1000*adc_to_voltage(oversample_adc(2,sensor_channel,16)) - 1000*adc_to_voltage(oversample_adc(1,sensor_channel,16));
  float mvShift = -1*(vDiffTarget - vDiffMeasure);
  return (int)mvShift-4;                        //manual testing shows mvShift is still of by ~4mV
}

/***************** System shutdown control ********************/

void turn_off_afe_power_things_down(void){
  LPDacCfg(0,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);                  
  AfeSwitchFullCfg(SWITCH_GROUP_T,SWID_ALLOPEN);        //open all AFE switches

  power_down_ADC();                                     

  AfeLpTiaPwrDown(CHAN0, BITM_AFE_LPTIACON0_TIAPDEN|BITM_AFE_LPTIACON0_PAPDEN); //power down LPTIA and PA
  AfeHpTiaPwrUp(0);                             //power down hptia
  LPDacPwrCtrl(CHAN0, PWR_DOWN);                //power down DAC
  AfePwrCfg(AFE_HIBERNATE);                     //put analog die to sleep
}

void power_down_ADC(void){
   AfeAdcPwrUp(0);
   AfeAdcGo(ADCIDLE);
}
