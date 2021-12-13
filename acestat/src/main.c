//Analog Devices Files
#include "ADuCM355.h"
#include "ClkLib.h"
#include "UrtLib.h"
#include "GptLib.h"
#include "AfeWdtLib.h"
#include "DioLib.h"
#include "RstLib.h"
#include "AfeTiaLib.h"
#include "PwrLib.h"
#include <stdlib.h>
#include <string.h>
#include "ad5940.h"

//ERDC File(s)
#include "craabUtil.h" 
#include "voltammetry.h"
#include "eis.h"

void runTest(char mode);
char getTestMode(void);

char* version = "2021.06.29";

int main(void){
  /*setup functions. only run when board powers on*/
  AfeWdtGo(false);
  ClockInit();
  UartInit();
  delay_10us(10);                             //settling delay
  /*End powerup setup*/
  
  char testMode = 0;
  
  while(1){
    /*****************************
     *1 Cyclic Voltammetry       *
     *2 Square Wave Voltammetry  *
     *3 Cyclic Square Wave       *
     *4 Chronoamperometry        *
     *5 EIS                      *
    ******************************/
    while(1){
      printf("%s%s%s", "[:MAIN:", version, "]");
      
      testMode = getTestMode();         //test mode input, reads only the first character in szInString
      runTest(testMode);
    }
  }
  return 0;
}

void runTest(char mode){
  
  bool testComplete = false;
  
  if(mode=='1'){
        while(testComplete==false){
              runCV();
              printf("[END:CV]");
        }
  }
  
  if(mode=='2'){
        while(testComplete==false){
            runSWV();  
            printf("[END:SWV]");
            testComplete = true;
            return;
        }
  }
  
  if(mode=='4'){
        runCSWV();
        printf("[END:CSWV]");
  }
  
  if(mode=='5'){
        runCA();
        printf("[END:CA]");
  }
  
  if(mode=='3'){
        runEIS();
        printf("[END:EIS]");
  }
}  

char getTestMode(void){
    char testMode = 0;
	uint8_t *uBuffer;
	uBuffer=return_uart_buffer();
    while(testMode==0){
      if(uart_get_flag()){
        testMode = uBuffer[0];
        uart_flag_reset();
      }
    }
    return testMode;
}
