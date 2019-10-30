#include "UrtLib.h"

//rewrite putchar to support printf in IAR
int putchar(int c)
{
   UrtTx(pADI_UART0,c);
   while(!(pADI_UART0->COMLSR&BITM_UART_COMLSR_TEMT));
   return c;
}