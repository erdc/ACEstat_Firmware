#include "ACEstat_gpt.h"
#include "ACEstat_misc.h"

/***************** General-purpose timer configuration functions ********************/

void gpt_config_scanrate(uint16_t mvRate){
   GptLd(pADI_TMR2, scanrate_lookup(mvRate));   //Load timer 2
   
   /**Enable Timer2 for periodic mode, counting down, using HFOSC as clock source*/
   GptCfg(pADI_TMR2,TCTL_CLK_HFOSC, TCTL_PRE_DIV64,
          BITM_TMR_CTL_MODE|
          BITM_TMR_CTL_RLD|
          BITM_TMR_CTL_EN);                    
   NVIC_EnableIRQ(TMR2_EVT_IRQn);               //Enable Timer 2 interrupt source in NVIC
}

void gpt_config_simple(void){
   GptLd(pADI_TMR0, 0x100);      // Load timer 0 with 39.4us period
   GptCfg(pADI_TMR0,TCTL_CLK_HFOSC, TCTL_PRE_DIV256,
          BITM_TMR_CTL_MODE|
          BITM_TMR_CTL_RLD|
          BITM_TMR_CTL_EN);             // Enable Timer0 for periodic mode, counting down, using HFOSC as clock source
   NVIC_EnableIRQ(TMR0_EVT_IRQn);       // Enable Timer 0  interrupt source in NVIC
}

void reset_timer_ctr(void){
  timer_ctr = 0;
}

uint32_t get_timer_ctr(void){
  return timer_ctr;
}
             
void gpt_wait_for_flag(void){
  
  /**Hold until timer timeout flag is set*/
  while(!tmr2_timeout){}                        //tmr2_timeout set in GPT2 interrupt handler
  tmr2_timeout = 0;
}

uint16_t scanrate_lookup(uint16_t mvRate){
  //Use LOADVAL = (0.00054*HFOSC)/(PRESCALE*mvRate) to calculate 
  switch(mvRate){
    case 1: return 0x358EF;
    case 5: return 0xAB63;
    case 10: return 0x55B1;                     //GPT load value for 10 mV/s
    case 20: return 0x2AD8;                     //GPT load value for 20 mV/s
    case 30: return 0x1C90;                     //GPT load value for 30 mV/s
    case 40: return 0x156C;                     //GPT load value for 40 mV/s
    case 50: return 0x1123;                     //GPT load value for 50 mV/s
    case 60: return 0x0E48;                     //GPT load value for 60 mV/s
    case 70: return 0x0C3D;                     //GPT load value for 70 mV/s
    case 80: return 0x0AB6;                     //GPT load value for 80 mV/s
    case 90: return 0x0985;                     //GPT load value for 90 mV/s
    case 100: return 0x0891;                    //GPT load value for 100 mV/s
    case 150: return 0x05B5;                    //GPT load value for 150 mV/s
    case 200: return 0x0448;                    //GPT load value for 200 mV/s
    case 250: return 0x036D;                    //GPT load value for 250 mV/s
    case 300: return 0x02DB;                    //GPT load value for 300 mV/s
    case 350: return 0x0272;                    //GPT load value for 350 mV/s
    case 400: return 0x0224;                    //GPT load value for 400 mV/s
    case 450: return 0x01E7;                    //GPT load value for 450 mV/s
    case 500: return 0x01B6;                    //GPT load value for 500 mV/s
    case 550: return 0x018E;
    case 600: return 0x016D;
    case 650: return 0x0151;
    case 700: return 0x0139;
    case 750: return 0x0124;
    case 800: return 0x0112;
    case 850: return 0x0102;
    case 900: return 0x00F3;
    case 950: return 0x00E6;
    case 1000: return 0x00DB;
    case 1500: return 0x0092;
    case 2000: return 0x006D;
    case 2500: return 0x0057;
    case 3000: return 0x0049;
    case 3500: return 0x003E;
    case 4000: return 0x0036;
    case 4500: return 0x0030;
    case 5000: return 0x002B;
    default: return 0x1123;                     //return 50mV/s by default
  }
  return 0;
}
