/***********************************************************************
code fragment. implementation of switching vzero with vbias voltage

   RAMP Wave generation
   Ramp Wave amplitude range is from (RAMP_LOW_LEVEL-RAMP_HIGH_LEVEL) to (RAMP_HIGH_LEVEL-RAMP_LOW_LEVEL),
   maximin range is +/-1800mV, when RAMP_LOW_LEVEL = 200mV, and RAMP_HIGH_LEVEL = 2000mV
   step width is controlled by timer0 in this example.
   6bit DAC (VZERO)
   _______           ______      +++++++++++++++RAMP_HIGH_LEVEL
          |         |
          |         |
          |_________|            +++++++++++++++RAMP_LOW_LEVEL
   12bit DAC (VBIAS)

Voltage waveform seen on RE pin (similar on SE/DE pin):
        / |                          | \
     /    |                          |    \
  /       |                          |       \
          |           /  \           |
          |        /        \        |
          |    /              \      |
          |/                     \   |
   Ramp Wave as seen via current waveform and also VRE-VDE (or VRE-VSE)
_                       _
 |_                   _|
   |_               _|
     |_           _|
       |_       _|
         |_   _|
           |_|

*/

void cv_ramp_parameters_changing_voltage(uint16_t v1, uint16_t v2, uint16_t sweepDirection, uint32_t RGAIN, uint16_t sweepRate, uint16_t burstSamples){
  
  uint16_t SETTLING_DELAY = 5;
  GptCfgVoltammetry(sweepRate); //configure general-purpose digital timer to use chosen sweeprate
  int RTIA = RTIA_VAL_LOOKUP(RGAIN);
  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  //DAC Variables
  uint16_t cBias;
  uint16_t cZero;
  uint16_t maxVoltage = 1800;
  uint16_t cZeroHigh6bit = (maxVoltage-200)/34.38;
  uint16_t cZeroLow6bit = 0;
  uint16_t cZeroHigh12bit = (maxVoltage-200)/0.54-10;
  uint16_t cZeroLow12bit = 0;
  uint16_t v1_12bit = 2*(v1-200)/0.54-10;
  uint16_t v2_12bit = 2*(v2-200)/0.54-10;
  
  //Ramp points down
  if(sweepDirection==0){
    //Ramp start
    cZero = cZeroHigh6bit;      //Start VZERO at high level
    for(cBias = cZeroHigh12bit - v1_12bit ; cBias < cZeroHigh12bit ; ++cBias){
        LPDacWr(CHAN0, cZero, cBias);
        delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
        GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
        if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
          szADCSamples[sampleCount]=burstSample(burstSamples, 1);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 2);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 0);
          sampleCount++;
        }
    }
    cZero = cZeroLow6bit;       //Switch to low-level zero voltage
    for(cBias = cZeroLow12bit ; cBias < v2_12bit ; ++cBias){
        LPDacWr(CHAN0, cZero, cBias);
        delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
        GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
        if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
          szADCSamples[sampleCount]=burstSample(burstSamples, 1);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 2);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 0);
          sampleCount++;
        }
    }
    for(cBias = v2_12bit ; cBias > cZeroLow12bit ; --cBias){
        LPDacWr(CHAN0, cZero, cBias);
        delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
        GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
        if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
          szADCSamples[sampleCount]=burstSample(burstSamples, 1);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 2);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 0);
          sampleCount++;
        }
    }
    cZero = cZeroHigh6bit;      //Switch back to high-level zero voltage
    for(cBias = cZeroHigh12bit ; cBias > cZeroHigh12bit-v1_12bit ; --cBias){
        LPDacWr(CHAN0, cZero, cBias);
        delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
        GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
        if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
          szADCSamples[sampleCount]=burstSample(burstSamples, 1);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 2);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 0);
          sampleCount++;
        }
    }
    //Ramp end
  }
  
  //Ramp points up
  else{
    //Ramp start
    cZero = cZeroLow6bit;      //Start VZERO at low level
    for(cBias = v1_12bit ; cBias > cZeroLow12bit ; --cBias){
        LPDacWr(CHAN0, cZero, cBias);
        delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
        GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
        if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
          szADCSamples[sampleCount]=burstSample(burstSamples, 1);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 2);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 0);
          sampleCount++;
        }
    }
    cZero = cZeroHigh6bit;       //Switch to high-level zero voltage
    for(cBias = cZeroHigh12bit ; cBias > cZeroHigh12bit - v2_12bit ; --cBias){
        LPDacWr(CHAN0, cZero, cBias);
        delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
        GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
        if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
          szADCSamples[sampleCount]=burstSample(burstSamples, 1);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 2);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 0);
          sampleCount++;
        }
    }
    for(cBias = cZeroHigh12bit - v2_12bit ; cBias < cZeroHigh12bit ; ++cBias){
        LPDacWr(CHAN0, cZero, cBias);
        delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
        GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
        if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
          szADCSamples[sampleCount]=burstSample(burstSamples, 1);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 2);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 0);
          sampleCount++;
        }
    }
    cZero = cZeroLow6bit;      //Switch back to low-level zero voltage
    for(cBias = cZeroLow12bit ; cBias < v1_12bit ; ++cBias){
        LPDacWr(CHAN0, cZero, cBias);
        delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
        GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
        if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
          szADCSamples[sampleCount]=burstSample(burstSamples, 1);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 2);
          sampleCount++;
          szADCSamples[sampleCount]=burstSample(burstSamples, 0);
          sampleCount++;
        }
    }
    //Ramp end
  }
  //Open the RE/CE connections to put the sensor in "open circuit" state
  int ocMask = (1<<2)|(1<<3)|(1<<4)|(1<<10);
  AfeLpTiaSwitchCfg(CHAN0, SWMODE_RAMP&(!ocMask));

  printCVResults(v1,v2,sampleCount,RTIA);
}
