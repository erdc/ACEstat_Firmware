#include <stdio.h>
#include <rt_misc.h>
#include "UrtLib.h"

/* We want a warning if semi-hosting libraries are used. */
#pragma import(__use_no_semihosting_swi)

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;

int fputc(int c, FILE *f) {
  UrtTx(pADI_UART0,c);
  while(!(pADI_UART0->COMLSR&BITM_UART_COMLSR_TEMT));
  return c;
}


int fgetc(FILE *f) {
  return (0x0);
}


int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}

/* ARM CC
This function writes a character to the console. 
The console might have been redirected. 
*/
void _ttywrch(int c) {
  UrtTx(pADI_UART0,c);
  while(!(pADI_UART0->COMLSR&BITM_UART_COMLSR_TEMT));
}


void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}


