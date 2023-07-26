#include "ACEstat_setup.h"
#include "ACEstat_misc.h"

/***************** UART and Clock setup ********************/

void ClockInit(void)
{
  DigClkSel(DIGCLK_SOURCE_HFOSC);               //digital clock from high-freqeuency oscillator            
  ClkDivCfg(1,1);
  AfeClkSel(AFECLK_SOURCE_HFOSC);               //AFE clock from high-frequency oscillator
  AfeSysClkDiv(AFE_SYSCLKDIV_1);                
}

void UartInit(void)
{
  DioCfgPin(pADI_GPIO0,PIN10,1);                //Setup P0.10 as UART pin
  DioCfgPin(pADI_GPIO0,PIN11,1);                //Setup P0.11 as UART pin
  pADI_UART0->COMLCR2 = 0x3;                    //Set PCLk oversampling rate 32. (PCLK to UART baudrate generator is /32)
  UrtCfg(pADI_UART0,B115200,
         (BITM_UART_COMLCR_WLS|3),0);           //Configure UART for 115200 baud rate
  UrtFifoCfg(pADI_UART0, RX_FIFO_8BYTE,         //Configure the UART FIFOs for 8 bytes deep
             BITM_UART_COMFCR_FIFOEN);
  UrtFifoClr(pADI_UART0, BITM_UART_COMFCR_RFCLR //Clear the Rx/TX FIFOs
             |BITM_UART_COMFCR_TFCLR);
  UrtIntCfg(pADI_UART0,BITM_UART_COMIEN_ERBFI |
            BITM_UART_COMIEN_ETBEI |
            BITM_UART_COMIEN_ELSI);             //Enable Rx, Tx and Rx buffer full Interrupts

  NVIC_EnableIRQ(UART_EVT_IRQn);                //Enable UART interrupt source in NVIC
}
