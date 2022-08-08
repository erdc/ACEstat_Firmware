#include "ACEstat_interface.h"
#include "ACEstat_misc.h"
#include <stdlib.h>

/***************** Output printing mode control********************/
uint8_t printing_mode = PRINT_MODE_RAW;         //default to raw printing mode

void set_printing_mode(uint8_t mode){
  printing_mode = mode;
}

uint8_t get_printing_mode(void){
  return printing_mode;
}

/***************** Check UARt flag ********************/
int uart_get_flag(void)
{
	return uart_flag;
}

/***************** Command-line input parsing functions ********************/

uint8_t* return_uart_buffer(void){
	return UART_buffer;
}

float get_frequency(void){
  
  float freq = 0;
  
  /**Wait for uart_get_flag == 1*/
  while(1){
    if(uart_get_flag()){
      char v[9];
      uint8_t *uBuffer;
      uBuffer=return_uart_buffer();
      
      freq = (float)atof(uBuffer);
      uart_flag_reset();                   
      return freq;
    }
  }
}

int get_parameter(){
  
  int parameter = 0;
  
  /**Wait for uart_get_flag == 1*/
  while(1){
    if(uart_get_flag()){
      uint8_t *uBuffer = return_uart_buffer();
      uart_flag_reset();
      return atoi(uBuffer);
    }
  }
}

uint16_t get_sensor_channel(void){
  printf("[:SCI]");
  char sensChanIn = get_parameter();
  if(sensChanIn > 0){
    return CHAN1;
  }
  return CHAN0;
}
