#include "ACEstat_inthandlers.h"
#include "ACEstat_misc.h"

/***************** UART flag control for user input parsing********************/

int uart_flag_set(void)
{
	uart_flag=1;
	return uart_flag;
}

int uart_flag_reset(void)
{
	uart_flag=0;
	return 1;
}

/***************** Interrupt handlers ********************/

void AfeAdc_Int_Handler(void){
  uint32_t sta;
  sta = pADI_AFE->ADCINTSTA;
  if(adcModeSel == 1){
    
    if(sta&BITM_AFE_ADCINTSTA_DFTRDY){
      pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_DFTRDY;	//clear DFTRDY interrupt bit
      dftRdy = 1;                               //set dftRdy flag
    }
  }
  else{
    
    if(sta&BITM_AFE_ADCINTSTA_ADCRDY){
      pADI_AFE->ADCINTSTA = BITM_AFE_ADCINTSTA_ADCRDY;  //clear ADCRDY interrupt bit
      ADCRAW = pADI_AFE->ADCDAT;
      set_adc_flag();
    }
  }
}

void GP_Tmr2_Int_Handler(void)
{
   volatile int uiT2STA = 0;
   uiT2STA = GptSta(pADI_TMR2);
   if((uiT2STA&0x0001)==0x0001)                 //timeout event pending
   {
      GptClrInt(pADI_TMR2,BITM_TMR_CLRINT_TIMEOUT);     //clear Timer 2 timeout interrupt
      tmr2_timeout = 1;
   }
}

void GP_Tmr0_Int_Handler(void)
{
   volatile int uiT0STA = 0;
   uiT0STA = GptSta(pADI_TMR0);
   if((uiT0STA&0x0001)==0x0001)  //timeout event pending
   {
      GptClrInt(pADI_TMR0,BITM_TMR_CLRINT_TIMEOUT);// Clear Timer 0 timeout interrupt
      timer_ctr++;
   }
}

void UART_Int_Handler(void)
{
   UrtLinSta(pADI_UART0);
   ucCOMIID0 = UrtIntSta(pADI_UART0);
   if ((ucCOMIID0 & 0xE) == 0xc || (ucCOMIID0 & 0xE) == 0x4)    //receive byte
   {
     
     /**Fill the primary UART software buffer array*/
     iNumBytesInFifo = pADI_UART0->COMRFC;      //read the Num of bytes in FIFO
     for(uint8_t i = 0; i <iNumBytesInFifo;++i){
       ucComRx = UrtRx(pADI_UART0);
       UART_buffer[i]=ucComRx;
     }
     
     /**Check for an excape character to reset the board*/
     if (UART_buffer[0] == 27) {
       NVIC_SystemReset();
     }
     
     UrtFifoClr(pADI_UART0, BITM_UART_COMFCR_RFCLR//Clear the Rx/TX FIFOs
             |BITM_UART_COMFCR_TFCLR);
     uart_flag_set();
   }
}