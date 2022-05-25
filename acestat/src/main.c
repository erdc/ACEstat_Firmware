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

/**ERDC Libraries*/
#include "craabUtil.h" 
#include "voltammetry.h"
#include "eis.h"

void runTest(char mode);
int getTestMode(void);

/**     
        First two digits of version number match ACEstat PCB version, 
        3rd digit represents firmware iteration for that board version
*/
char* version = "1.7.3";

int main(void){
  /**Setup functions. only run when board powers on*/
  AfeWdtGo(false);
  ClockInit();
  UartInit();
  delay_10us(10);

  /*End powerup setup*/
  
  int testMode = 0;
  
  set_printing_mode(PRINT_MODE_RAW);

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
  
  if(mode==MODE_CV_DEBUG){
    runCV(1);                //CV test with preset parameters for quicker debugging
    printf("[END:CV]");
  }
  if(mode==MODE_CV){
    runCV(0);
    printf("[END:CV]");
  }
  if(mode==MODE_SWV){
    runSWV();
    printf("[END:SWV]");
  }
  if(mode==MODE_CSWV){
    runCSWV();
    printf("[END:CSWV]");
  }
  if(mode==MODE_CA){
    runCA();
    printf("[END:CA]");
  }
  if(mode==MODE_EIS){
    runEIS();
    printf("[END:EIS]");
  }
  if(mode==MODE_OCP){
    runOCP();
    printf("[END:OCP]");
  }
}  

int getTestMode(void){
    char testMode = 0;
	uint8_t *uBuffer;
	uBuffer=return_uart_buffer();
    while(testMode==0){
      if(uart_get_flag()){
        testMode = uBuffer[0];
        uart_flag_reset();
      }
    }
    return (int)testMode-48;
}
