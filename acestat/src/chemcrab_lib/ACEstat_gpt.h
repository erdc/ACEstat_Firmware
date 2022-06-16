#ifndef ACESTAT_GPT_H
#define ACESTAT_GPT_H

/**Analog Devices ADuCM355 reference libraries*/
#include "ADuCM355.h"
#include "ClkLib.h"
#include "UrtLib.h"
#include "GptLib.h"
#include "AfeAdcLib.h"
#include "AfeWdtLib.h"
#include "DioLib.h"
#include "RstLib.h"
#include "AfeTiaLib.h"
#include "PwrLib.h"
#include "AfeDacLib.h"
#include "ad5940.h"

/***************** General-purpose timer configuration functions ********************/

/**
  *@brief       gpt_config_scanrate: setup general-purpose timer 2 to control voltammetry scanrate
  *@param       mvRate: one of 10,20,30,40,50,100,150,200,250,300,350,400,450,500 mV/s.  Otherwise defaults to 50 mV/s
  *@retval      none
*/
void gpt_config_scanrate(uint16_t mvRate);

/**
  *@brief       gpt_config_simple: setup general-purpose timer 0 to have 39.4us period.  Used for equilibrium delays and chronoamperometry
  *@param       none
  *@retval      none
*/
void gpt_config_simple(void);

/**
  *@brief       reset_timer_ctr: sets timer_ctr to 0 to restart counting
  *@param       none
  *@retval      none
*/
void reset_timer_ctr(void);

/**
  *@brief       get_timer_ctr: gets the current value of timer_ctr
  *@param       none
  *@retval      timer_ctr, used to count GPT cycles for equilibrium timing
*/
uint32_t get_timer_ctr(void);

/**
  *@brief       gpt_wait_for_flag: holds voltammetry test for flag inducating GPT period has passed.  Ensures scanrate is maintained during voltammetry
  *@param       none
  *@retval      none
*/
void gpt_wait_for_flag(void);

/**
  *@brief       scanrate_lookup: gets GPT load value from pre-defined table of scanrates, used to configure GPT 
  *@param       mvRate: one of 10,20,30,40,50,100,150,200,250,300,350,400,450,500 mV/s.  Otherwise defaults to 50 mV/s
  *@retval      hex value to use as GPT LOAD to give desired voltammetry scanrate
*/
uint16_t scanrate_lookup(uint16_t mvRate);

#endif