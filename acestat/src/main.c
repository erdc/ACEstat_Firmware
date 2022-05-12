/**Analog Devices Files*/
#include "ADuCM355.h"
#include "ClkLib.h"
#include "UrtLib.h"
#include "GptLib.h"
#include "AfeWdtLib.h"
#include "DioLib.h"
#include "RstLib.h"
#include "AfeTiaLib.h"
#include "PwrLib.h"
#include "ad5940.h"

/**Standard Libraries*/
#include <stdlib.h>
#include <string.h>

/**ERDC Libraries*/
#include "craabUtil.h" 
#include "voltammetry.h"
#include "eis.h"

void runTest(char mode);
char getTestMode(void);

char* version = "1.7.1";

int main(void){
  /**Setup functions. only run when board powers on*/
  AfeWdtGo(false);
  ClockInit();
  UartInit();
  delay_10us(10);

  /*End powerup setup*/
  
  char testMode = 0;
  
  set_printing_mode(PRINT_MODE_PROCESSED);

  while(1){
    /*****************************
    *1 Cyclic Voltammetry       *
    *2 Square Wave Voltammetry  *
    *3 Cyclic Square Wave       *
    *4 Chronoamperometry        *
    *5 EIS                      *
    ******************************/
    printf("%s%s%s", "[:MAIN:", version, "]\n");
    
    /**User selects a test mode via UART*/
    testMode = getTestMode();         //test mode input, reads only the first character in szInString
    runTest(testMode);
  }
  return 0;
}

void runTest(char mode){
  
  bool testComplete = false;
  
  if(mode=='0'){
    runCV(1);                //quick test with preset parameters for debugging
    printf("[END:CV]");
  }
  if(mode=='1'){
    runCV(0);
    printf("[END:CV]");
  }
  if(mode=='2'){
    runSWV();
    printf("[END:SWV]");
  }
  if(mode=='3'){
    runCSWV();
    printf("[END:CSWV]");
  }
  if(mode=='4'){
    runCA();
    printf("[END:CA]");
  }
  if(mode=='5'){
    getEISFrequencies();
    runEIS();
    printf("[END:EIS]");
  }
  if(mode=='6'){
    runOCP();
    printf("[END:OCP]");
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
