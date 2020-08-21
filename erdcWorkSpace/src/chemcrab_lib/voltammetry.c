#include "voltammetry.h"

/***************CYCLIC VOLTAMMETRY**************/
void runCV(void){
  setAdcMode(0);

  //printf("Zero voltage between 0000mV - 9999mV : ");
  printf("[:ZVI]");
  uint16_t cvZeroVolt = getParameter(4);
  
  //printf("Starting voltage between 0000mV - 9999mV : ");
  printf("[:SVI]");
  uint16_t cvStartVolt = getParameter(4);
  
  //printf("Vertex voltage between 0000mV - 9999mV : ");
  printf("[:VVI]");
  uint16_t cvVertexVolt = getParameter(4);
  
  //printf("Ending voltage between 0000mV - 9999mV : ");
  printf("[:EVI]");
  uint16_t cvEndVolt = getParameter(4);
  
  //printf("Voltage sweep rate between 000mV/s - 999mV/s : ");
  printf("[:SRI]");
  uint16_t sweepRate = getParameter(3);
  
  //printf("Equilibrium Time 0000ms - 9999ms");
  printf("[:TEI]");
  uint16_t tEquilibrium = getParameter(4);
  
  //printf("Number of samples to take in a burst {2,4,8,16,32,64,128,256,512}");
  //printf("[:BSI]");
  //uint16_t burstSamples = getParameter(3);
  
  //printf("Current Limit:\n");
  //printf("0: 1.125mA\n1: 225uA\n2: 45uA\n3: 22.5uA\n4: 11.25uA\n5: 5.625uA\n6: 2.8uA\n7: 1.4uA\n");
  printf("[:CLI]");
  uint8_t RTIACHOICE = getParameter(1);
  
  //uint8_t* uBuffer = return_uart_buffer();
  //uint8_t RTIACHOICE = uBuffer[0];
  uint32_t RGAIN = RTIA_LOOKUP(RTIACHOICE-48); //PASS INT VAL RATHER THAN ASCII
    
  /*cv ramp setup*/
  AfePwrCfg(AFE_ACTIVE);  //set AFE power mode to active

  LPDacPwrCtrl(CHAN0,PWR_UP);
  LPDacCfg(CHAN0,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);

  /*LPTIA REQUIRED TO HAVE DAC OUTPUT*/
  /*power up PA,TIA,no boost, full power*/
  AfeLpTiaPwrDown(CHAN0,0);
  AfeLpTiaAdvanced(CHAN0,BANDWIDTH_NORMAL,CURRENT_BOOST);
  AfeLpTiaSwitchCfg(CHAN0,SWMODE_SHORT);  /*short TIA feedback for Sensor setup*/
  AfeLpTiaCon(CHAN0,LPTIA_RLOAD_0,LPTIA_RGAIN_96K,LPTIA_RFILTER_1M); 
  delay_10us(1000);
  
  AfeLpTiaSwitchCfg(CHAN0,SWMODE_RAMP);  /*TIA switch to normal*/
  //Open the RE/CE connections to put the sensor in "open circuit" state
  int ocMask = (1<<2)|(1<<3)|(1<<4)|(1<<10);
  AfeLpTiaSwitchCfg(CHAN0, SWMODE_RAMP&(!ocMask));
  
  /*LPTIA REQUIRED TO HAVE DAC OUTPUT*/

  hptia_setup_parameters(RGAIN);
  adcCurrentSetup_hptia();
  /*end cv ramp setup*/
  
  AfeLpTiaSwitchCfg(1,SWMODE_NORM);  /*TIA channel 1 switch to normal mode*/
  AfeLpTiaSwitchCfg(0,SWMODE_RAMP);  /*TIA channel 0 switch to ramp mode*/

  /*RAMP HERE*/
  equilibrium_delay(cvStartVolt, cvZeroVolt, tEquilibrium);
  cv_ramp_parameters(cvZeroVolt,cvStartVolt,cvVertexVolt,cvEndVolt,RGAIN, sweepRate);
  /*END RAMP*/

  turn_off_afe_power_things_down();
  printf("[END:CV]");
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

void cv_ramp_parameters(uint16_t zeroV, uint16_t startV, uint16_t vertexV, uint16_t endV, uint32_t RGAIN, uint16_t sweepRate){
  
  uint16_t SETTLING_DELAY = 5;
  uint16_t cBias, cZero;
  GptCfgVoltammetry(sweepRate); //configure general-purpose digital timer to use chosen sweeprate
  uint16_t cStart = (startV-200)/0.54-10;
  uint16_t cVertex = (vertexV-200)/0.54-10;
  uint16_t cEnd =(endV-200)/0.54-10;
  int RTIA = RTIA_VAL_LOOKUP(RGAIN);
  
  cZero = (zeroV-200)/34.38;
  cBias = cStart;
  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);
  
  uint16_t inc = 1;
  
  //Sweep starts at a negative voltage
  if(startV < vertexV){
    for (cBias = cStart; cBias < cVertex; cBias = cBias + inc){
      LPDacWr(CHAN0, cZero, cBias);         // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1);
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0);
        sampleCount++;
      }
    }
    for (cBias = cVertex; cBias > cEnd; cBias = cBias - inc){
      LPDacWr(CHAN0, cZero, cBias);         // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1);
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0);
        sampleCount++;
      }
    }
  }
  //Sweep starts at a positive voltage
  else{
    for (cBias = cStart; cBias > cVertex; cBias = cBias - inc){
      LPDacWr(CHAN0, cZero, cBias);         // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1);
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0);
        sampleCount++;
      }
    }
    
    for (cBias = cVertex; cBias < cEnd; cBias = cBias + inc){
      LPDacWr(CHAN0, cZero, cBias);         // Set VBIAS/VZERO output voltages
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      GptWaitForFlag();                   //GPT delay to maintain voltage sweeprate
      
      if(cBias%2 == 0){                    //Only store ADC data for every other DAC increment
        szADCSamples[sampleCount]=burstSample(1);
        sampleCount++;
        szADCSamples[sampleCount]=burstSample(0);
        sampleCount++;
      }
    }
  }

  //Open the RE/CE connections to put the sensor in "open circuit" state
  int ocMask = (1<<2)|(1<<3)|(1<<4)|(1<<10);
  AfeLpTiaSwitchCfg(CHAN0, SWMODE_RAMP&(!ocMask));

  printCVResults(cZero,cStart,cVertex,cEnd,sampleCount,RTIA);
}

void printCVResults(float cZero, float cStart, float cVertex, float cEnd, int sampleCount, int RTIA){
  float zeroVoltage = 200+(cZero*34.38);
  //printf("RANGE IS %f to %f to %f\n", cStart*0.54+200-zeroVoltage, cVertex*0.54+200-zeroVoltage, cEnd*0.54+200-zeroVoltage);
  printf("[RANGE:%f,%f,%f]", cStart*0.54+200-zeroVoltage, cVertex*0.54+200-zeroVoltage, cEnd*0.54+200-zeroVoltage);
  //printf("RGAIN VALUE IS %i\n", RTIA);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  uint16_t* szADCSamples = return_adc_buffer();
  float tc, vDiff;
  for(uint32_t i = 0; i < sampleCount; i+=2){
    //vDiff = -1*(szADCSamples[i]*0.54+200-zeroVoltage);
    vDiff = (zeroVoltage/1000) - adc_to_volts(szADCSamples[i]);
    tc = calcCurrent_hptia(szADCSamples[i+1], RTIA);
    //printf("Volt:%f,Current:%f\n", vDiff,tc);
    printf("%f,%f"EOL, vDiff,tc);
  }
  printf("]");
}
/****************END CYCLIC VOLTAMMETRY**********************/

/****************SQUARE WAVE VOLTAMMETRY***************************/
void equilibrium_delay(uint16_t start, uint16_t zero, uint16_t time){
  AfeLpTiaSwitchCfg(CHAN0,SWMODE_RAMP);  /*TIA switch to normal*/
  LPDacWr(CHAN0, (zero-200)/34.38, (start-200)/0.54-10);    //Write the DAC to its starting voltage during the quilibrium period
  delay_10us(100*time);
}

void sqv_ramp_parameters(uint16_t zeroV, uint16_t startV, uint16_t endV, uint32_t RGAIN, uint16_t amplitude, int dep, uint16_t freq){
  uint16_t SETTLING_DELAY = 5;
  uint16_t cBias, cZero;
  
  uint16_t cStart = (startV-200)/0.54-10;
  uint16_t cEnd =(endV-200)/0.54-10;
  int RTIA = RTIA_VAL_LOOKUP(RGAIN);
  
  uint16_t delayVal = (50000/freq/2.58);        //delay required to maintain specified squarewave frequency

  uint16_t amp = (amplitude)/0.54-10;

  cZero = (zeroV-200)/34.38;
  cBias = cStart;

  int sampleCount = 0;
  uint16_t* szADCSamples = return_adc_buffer();
  AfeAdcGo(BITM_AFE_AFECON_ADCCONVEN);

  /*palmsense device does 2 sweeps for some reason only reports one*/
//  for (cBias = cStart; cBias < cEnd; cBias+=10){
//    LPDacWr(CHAN0, cZero, cBias+amp);
//    delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
//    delay_10us(1250); //delay 12.5ms
//    LPDacWr(CHAN0, cZero, cBias-amp);
//    delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
//    delay_10us(1250); //delay 12.5ms
//  }
  
  //Ramp function goes from negative to positive voltage
  if(startV < endV){
    for (cBias = cStart; cBias < cEnd; cBias+=10){
      //Squarewave high
      LPDacWr(CHAN0, cZero, cBias+amp);        //Squarewave peak, voltage = cBias+0.5amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the voltage and current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(1);
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0);
      sampleCount++;           
      
      if(sampleCount>MAX_BUFFER_LENGTH) {         //check for buffer length overflow
        printf("MEMORY OVERFLOW\n");            
        sampleCount=0;
        break;
      }
      
      if(sampleCount>MAX_BUFFER_LENGTH) {         //check for buffer length overflows
        printf("MEMORY OVERFLOW\n");
        sampleCount=0;
        break;
      }
      
      //Squarewave low
      LPDacWr(CHAN0, cZero, cBias-amp);        //Squarewave-low, voltage = cBias-0.5amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the voltage and current at the squarewave LOW side
      szADCSamples[sampleCount]=burstSample(1);
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0);
      sampleCount++;     
      
      if(sampleCount>MAX_BUFFER_LENGTH) {
        printf("MEMORY OVERFLOW\n");
        sampleCount=0;
        break;
      }
    }
  }
  
  //Ramp function goes from positive to negative voltage
  else{
    for (cBias = cStart; cBias > cEnd; cBias = cBias - 10){
      //Squarewave high
      LPDacWr(CHAN0, cZero, cBias+amp);        //Squarewave peak, voltage = cBias+0.5amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the voltage and current at the squarewave HIGH side
      szADCSamples[sampleCount]=burstSample(1);
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0);
      sampleCount++;                       
      
      if(sampleCount>MAX_BUFFER_LENGTH) {         //check for buffer length overflow
        printf("MEMORY OVERFLOW\n");            
        sampleCount=0;
        break;
      }
      
      if(sampleCount>MAX_BUFFER_LENGTH) {         //check for buffer length overflows
        printf("MEMORY OVERFLOW\n");
        sampleCount=0;
        break;
      }
      
      //Squarewave low
      LPDacWr(CHAN0, cZero, cBias-amp);        //Squarewave-low, voltage = cBias-0.5amp
      delay_10us(SETTLING_DELAY);                  // allow LPDAC to settle
      delay_10us(delayVal-SETTLING_DELAY);         //holding delay to maintain squarewave frequency
      
      //Measure the voltage and current at the squarewave LOW side
      szADCSamples[sampleCount]=burstSample(1);
      sampleCount++;
      szADCSamples[sampleCount]=burstSample(0);
      sampleCount++;     
      
      if(sampleCount>MAX_BUFFER_LENGTH) {
        printf("MEMORY OVERFLOW\n");
        sampleCount=0;
        break;
      }
    }  
  }
  printSWVResults(cZero, cStart, cEnd, sampleCount, RTIA);
}

void runSWV(void){
  setAdcMode(0);
  //printf("Zero voltage (0000mV - 9999mV) : ");
  printf("[:ZVI]");
  uint16_t swvZeroVolt = getParameter(4);
  
  printf("[:SVI]");
  //printf("Starting voltage (0000mV - 9999mV) : ");
  uint16_t swvStartVolt = getParameter(4);
  
  //printf("Ending voltage (0000mV - 9999mV) : ");
  printf("[:EVI]");
  uint16_t swvEndVolt = getParameter(4);
  
  printf("[:AMPI]");
  //printf("Squarewave Pk-Pk amplitude (000mV - 999mV) : ");
  uint16_t swvAmp = getParameter(3);
  
  printf("[:FREQI]");
  //printf("Squarewave frequency (00000Hz - 99999Hz) : ");
  uint16_t swvFreq = getParameter(5);
  
  printf("[:TEI]");
  //printf("Deposition time between 0000s and 9999s : ");
  uint16_t tEquilibrium = getParameter(4);
  
  //printf("Current Limit:\n");
  //printf("0: 4.5mA\n1: 900uA\n2: 180uA\n3: 90uA\n4: 45uA\n5: 22.5uA\n6: 11.25uA\n7: 5.625uA\n");
  printf("[:CLI]");
  uint8_t RTIACHOICE = getParameter(1);
  uint32_t RGAIN = RTIA_LOOKUP(RTIACHOICE-48); //-48 because an ascii character is passed. 
  
  AfePwrCfg(AFE_ACTIVE);  //set AFE power mode to active

  LPDacPwrCtrl(CHAN0,PWR_UP);
  //LPDacWr(CHAN0, 62, 62*64);
  LPDacCfg(CHAN0,LPDACSWNOR,VBIAS12BIT_VZERO6BIT,LPDACREF2P5);

  /*LPTIA REQUIRED TO HAVE DAC OUTPUT*/
  /*power up PA,TIA,no boost, full power*/
  AfeLpTiaPwrDown(CHAN0,0);
  AfeLpTiaAdvanced(CHAN0,BANDWIDTH_NORMAL,CURRENT_NOR);
  AfeLpTiaSwitchCfg(CHAN0,SWMODE_SHORT);  /*short TIA feedback for Sensor setup*/
  AfeLpTiaCon(CHAN0,LPTIA_RLOAD_0,LPTIA_RGAIN_96K,LPTIA_RFILTER_1M); 
  delay_10us(200);
  
  AfeLpTiaSwitchCfg(CHAN0,SWMODE_RAMP);  /*TIA switch to ramp mode*/
  /*LPTIA REQUIRED TO HAVE DAC OUTPUT*/

  hptia_setup_parameters(RGAIN);
  adcCurrentSetup_hptia();
  /*end swv ramp setup*/

  /*RAMP HERE*/
  equilibrium_delay(swvStartVolt, swvZeroVolt , tEquilibrium);
  sqv_ramp_parameters(swvZeroVolt,swvStartVolt,swvEndVolt,RGAIN, swvAmp, tEquilibrium, swvFreq);
  /*END RAMP*/

  turn_off_afe_power_things_down();
  NVIC_SystemReset(); //ARM DIGITAL SOFTWARE RESET
}

void printSWVResults(float cZero, float cStart, float cEnd, int sampleCount, int RTIA){
  float zeroVoltage = 200+(cZero*34.38);
  uint16_t* szADCSamples = return_adc_buffer();
  float vDiff, tc;
  printf("[RANGE:%f,%f]", cStart*0.54+200-zeroVoltage, cEnd*0.54+200-zeroVoltage);
  printf("[RGAIN:%i][RESULTS:", RTIA);
  for(uint32_t i = 0; i < sampleCount; i+=4){
    vDiff = (zeroVoltage/1000) - adc_to_volts((szADCSamples[i] + szADCSamples[i+2])/2);
    tc = 0-(calcCurrent_hptia(szADCSamples[i+1],RTIA) - calcCurrent_hptia(szADCSamples[i+3],RTIA));
    printf("%f,%f\n", vDiff, tc);
  }
  printf("]");
}
/*************END SQUARE WAVE VOLTAMMETRY**************************/