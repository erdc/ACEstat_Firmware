#include "ACEstat_interface.h"
#include "ACEstat_misc.h"

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
	return szInSring;
}

int get_voltage_input(void){

  int voltage = 0;
  
  /**Wait for uart_get_flag == 1*/
  while(1){
    if(uart_get_flag()){
      char v[5];
      uint8_t *uBuffer;
      uBuffer=return_uart_buffer();
      for(int i=0 ; i<5 ; ++i){
        v[i] = uBuffer[i];
      }
      
      voltage+=(v[4]-48)*1;
      voltage+=(v[3]-48)*10;
      voltage+=(v[2]-48)*100;
      voltage+=(v[1]-48)*1000;
      
      /**Handling negative input voltages*/
      if(v[0] == '-'){
        voltage = -1*voltage;
      }
      
      uart_flag_reset();                          //reset the UART flag
      return voltage;
    }
  }
}

float get_low_frequency(void){
  
  float freq = 0;
  
  /**Wait for uart_get_flag == 1*/
  while(1){
    if(uart_get_flag()){
      char v[6];
      uint8_t *uBuffer;
      uBuffer=return_uart_buffer();
      for(int i=0 ; i<6 ; ++i){
        v[i] = uBuffer[i];
      }
      
      /**Special case if input is <1Hz*/
      if(v[0]=='.'){
        freq+=(v[5]-48)*0.00001;
        freq+=(v[4]-48)*0.0001;
        freq+=(v[3]-48)*0.001;
        freq+=(v[2]-48)*0.01;
        freq+=(v[1]-48)*0.1;
      }

      else{
        freq+=(v[5]-48)*1;
        freq+=(v[4]-48)*10;
        freq+=(v[3]-48)*100;
        freq+=(v[2]-48)*1000;
        freq+=(v[1]-48)*10000;
        freq+=(v[0]-48)*100000;
      }
      uart_flag_reset();                          //reset the UART flag
      return freq;
    }
  }
}

int get_parameter(int dec){
  
  int parameter = 0;
  
  /**Wait for uart_get_flag == 1*/
  while(1){
    if(uart_get_flag()){
      if(dec==7){
          char v[7];
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          for(int i=0 ; i<dec ; ++i){
            v[i] = uBuffer[i];
          }
          parameter+=(v[6]-48);
          parameter+=(v[5]-48)*10;
          parameter+=(v[4]-48)*100;
          parameter+=(v[3]-48)*1000;
          parameter+=(v[2]-48)*10000;
          parameter+=(v[1]-48)*100000;
          parameter+=(v[0]-48)*1000000;
          uart_flag_reset();                      //reset the UART flag
          return parameter;
      }
      if(dec==6){
          char v[6];
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          for(int i=0 ; i<dec ; ++i){
            v[i] = uBuffer[i];
          }
          parameter+=(v[5]-48);
          parameter+=(v[4]-48)*10;
          parameter+=(v[3]-48)*100;
          parameter+=(v[2]-48)*1000;
          parameter+=(v[1]-48)*10000;
          parameter+=(v[0]-48)*100000;
          uart_flag_reset();                      //reset the UART flag
          return parameter;
      }
      if(dec==5){
          char v[5];
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          for(int i=0 ; i<dec ; ++i){
            v[i] = uBuffer[i];
          }
          parameter+=(v[4]-48);
          parameter+=(v[3]-48)*10;
          parameter+=(v[2]-48)*100;
          parameter+=(v[1]-48)*1000;
          parameter+=(v[0]-48)*10000;
          uart_flag_reset();                      //reset the UART flag
          return parameter;
      }
      if(dec==4){
          char v[4];
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          for(int i=0 ; i<dec ; ++i){
            v[i] = uBuffer[i];
          }
          parameter+=v[3]-48;
          parameter+=(v[2]-48)*10;
          parameter+=(v[1]-48)*100;
          parameter+=(v[0]-48)*1000;
          uart_flag_reset();                      //reset the UART flag
          return parameter;
      }
      if(dec==3){
          char v[3];
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          for(int i=0 ; i<dec ; ++i){
            v[i] = uBuffer[i];
          }
          parameter+=(v[2]-48);
          parameter+=(v[1]-48)*10;
          parameter+=(v[0]-48)*100;
          uart_flag_reset();                      //reset the UART flag
          return parameter;
      }
      
      if(dec==2){
          char v[2];
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          for(int i=0 ; i<dec ; ++i){
            v[i] = uBuffer[i];
          }
          parameter+=(v[1]-48);
          parameter+=(v[0]-48)*10;
          uart_flag_reset();                      //reset the UART flag
          return parameter;
      }
      
      if(dec==1){
          uint8_t *uBuffer;
          uBuffer=return_uart_buffer();
          parameter = uBuffer[0];
          uart_flag_reset();                      //reset the UART flag
          return parameter-48;
      }
    }
  }
}

uint16_t get_sensor_channel(void){
  printf("[:SCI]");
  uint16_t sensChanIn = get_parameter(1)-48;
  if(sensChanIn > 0){
    return CHAN1;
  }
  return CHAN0;
}
