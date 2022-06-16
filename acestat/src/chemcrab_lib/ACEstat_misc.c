#include "ACEstat_misc.h"

/**************TEMP*******************/
static uint32_t clkHclkSpeed  = 6500000u;       //6.5MHz
static uint32_t AfeRootClkSpeed = 16000000u;    //16MHz
static uint32_t AfeSysClkSpeed = 16000000u;     //16MHz

#define  UART_INBUFFER_LEN 16

volatile uint32_t timer_ctr = 0;

#define USE_SINC2_FOR_TEST 0
volatile uint8_t  ucInCnt;
volatile uint32_t ucCOMIID0;
volatile uint32_t iNumBytesInFifo;
uint8_t  ucComRx;
uint8_t szInSring[UART_INBUFFER_LEN];

volatile uint8_t adcRdy = 0;
volatile uint8_t dftRdy = 0;
volatile uint16_t ADCRAW;
uint8_t adcModeSel = 0;
volatile uint8_t uart_flag = 0;

/**
   @brief uint8_t AfeClkSel(uint32_t clkSource)
          ======Select clock source for AFE system
   @param clkSource : {AFECLK_SOURCE_HFOSC,AFECLK_SOURCE_XTAL,AFECLK_SOURCE_EXT}
   @return 1.
   @note set ADC and SYS clock the same source for better performance
   @note when use AFECLK_SOURCE_EXT, update clock speed seperately by calling clockUpdate()
**/

uint8_t AfeClkSel(uint32_t clkSource)
{
   if(clkSource == (pADI_AFECON->CLKSEL&BITM_AFECON_CLKSEL_SYSCLKSEL))
   {
      return 1;
   }
   else
   {
      switch(clkSource)
      {
      case AFECLK_SOURCE_HFOSC:
         while(!(pADI_ALLON->OSCCON&BITM_ALLON_OSCCON_HFOSCOK))
         {
            pADI_ALLON->OSCKEY = OSC_CTL_KEY;
            pADI_ALLON->OSCCON |= BITM_ALLON_OSCCON_HFOSCEN;
            pADI_ALLON->OSCKEY = 0;
            //delay_us(50);
         }
         pADI_AFECON->CLKSEL = clkSource|(clkSource<<BITP_AFECON_CLKSEL_ADCCLKSEL);
         break;
      case AFECLK_SOURCE_XTAL:
         while(!(pADI_ALLON->OSCCON&BITM_ALLON_OSCCON_HFXTALOK))
         {
            pADI_ALLON->OSCKEY = OSC_CTL_KEY;
            pADI_ALLON->OSCCON |= BITM_ALLON_OSCCON_HFXTALEN;
            pADI_ALLON->OSCKEY = 0;
            //delay_us(50);
         }
         pADI_AFECON->CLKSEL = clkSource|(clkSource<<BITP_AFECON_CLKSEL_ADCCLKSEL);
         break;
      case AFECLK_SOURCE_EXT:
         pADI_AGPIO2->CON |= 3<<2;  // EXT_CLK
         pADI_AGPIO2->IEN |= 1<<1;  //AGPIO2.1(PWM1) input
         pADI_AFECON->CLKSEL = clkSource|(clkSource<<BITP_AFECON_CLKSEL_ADCCLKSEL);
         break;
      default:
         break;
      }
      return 1;
   }
}
/**
   @brief uint8_t AfeSysClkDiv(AFE_SYSCLKDIV_TypeDef clkDiv)
          ======set speed of AFE system clock
   @param clkDiv : {AFE_SYSCLKDIV_1,AFE_SYSCLKDIV_2,AFE_SYSCLKDIV_4,AFE_SYSCLKDIV_8}
            - AFE system clock = AFE source clock/clkDiv
   @return 1.
   @note AFE system clock is typically 16MHz, for gas sensor DC current measurement,
      there is an option to decrease clock down to 8MHz or 4MHz. Decreasing AFE system clock in other
      working modes(ex, impedance measurement) haven't been evaluated. Not suggested.
   @note radio of HCLK to AFE system clock must be within the range of 3:1 and 1:3
**/
uint8_t AfeSysClkDiv(AFE_SYSCLKDIV_TypeDef clkDiv)
{
   uint32_t SysSpeed;
   SysSpeed = AfeRootClkSpeed/clkDiv;
   while(!D2DClkSpeedCheck(clkHclkSpeed,SysSpeed))
   {  }  //D2D check fail, iHclkDiv not suitable, cannot go further
   if(clkDiv>1)
   {
      pADI_AFECON->CLKCON0KEY = 0xA815;   //enable clock division to 8MHz,4MHz
   }
   else
   {
      pADI_AFECON->CLKCON0KEY = 0;
   }
   pADI_AFECON->CLKCON0 = (clkDiv<<10) + clkDiv + (pADI_AFECON->CLKCON0 & BITM_AFECON_CLKCON0_ADCCLKDIV);
   clockUpdate(AFESYSCLK_SPEED,SysSpeed);
   return 1;
}

uint8_t AfeHFOsc32M(uint32_t En)
{
   if(En > 0)
   {
      pADI_AFECON->CLKEN1 |= BITM_AFECON_CLKEN1_ACLKDIS;
      pADI_AFE->HPOSCCON &= (~BITM_AFE_HPOSCCON_CLK32MHZEN);
      __disable_irq();
      //delay_us(5);   //No AFE operation here!!
      clockUpdate(AFE_ROOTCLK_SPEED,32000000u);
      clockUpdate(AFESYSCLK_SPEED,2*AfeSysClkSpeed);
      for(uint8_t i=0;i<200;i++);
      __enable_irq();
      pADI_AFECON->CLKEN1 &= (~BITM_AFECON_CLKEN1_ACLKDIS);
   }
   else
   {
      pADI_AFE->HPOSCCON |= BITM_AFE_HPOSCCON_CLK32MHZEN;
      __disable_irq();
      //delay_us(5);   //No AFE operation here!!
      clockUpdate(AFE_ROOTCLK_SPEED,16000000u);
      clockUpdate(AFESYSCLK_SPEED,AfeSysClkSpeed/2);
      for(uint8_t i=0;i<200;i++);
      __enable_irq();
   }
   return 1;
}
/***************END TEMP**************/

volatile uint8_t tmr2_timeout = 0;