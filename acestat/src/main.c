/**Analog Devices Libraries*/
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
#include "ACEstat_interface.h"
#include "ACEstat_setup.h"
#include "ACEstat_tia.h"
#include "ACEstat_voltammetry.h"
#include "ACEstat_eis.h"
#include "ACEstat_adc.h"
#include "ACEstat_gpt.h"
#include "ACEstat_inthandlers.h"
#include "ACEstat_mux.h"
#include "ACEstat_misc.h"

void runTest(int mode);
int getTestMode(void);

/**     
First two digits of version number match ACEstat PCB version, 
3rd digit represents firmware iteration for that board version
*/
char* version = "1.7.5";

int main(void){
  
  /**Setup functions. only run when board powers on*/
  AfeWdtGo(false);
  ClockInit();
  UartInit();
  delay_10us(10);
  
  /**PRINT_MODE_RAW:            print ADC data directly to UART/USB, convert to voltage/current on application*/
  /**PRINT_MODE_PROCESSED:      convert ADC data on ADuCM355 and print to UART/USB*/
  set_printing_mode(PRINT_MODE_RAW);

  while(1){
    /************************************
    *0 Cyclic Voltammetry Debug         *
    *1 Cyclic Voltammetry               *
    *2 Square Wave Voltammetry          *
    *3 Cyclic Square Wave Voltammetry   *
    *4 Chrono Amperometry               *
    *5 Impedance SPectroscopy           *
    *6 Open-circuit Potentiometry       *
    *************************************/
    
    printf("%s%s%s", "[:MAIN:", version, "]\n");
    
    /**User selects a test mode via UART*/
    runTest(getTestMode());
    
  }
  return 0;
}

void runTest(int mode){
  
  bool testComplete = false;
  
  if(mode==MODE_CV_DEBUG){
    runCV(1);                   //CV test with preset parameters for quicker debugging
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
  if(mode==MODE_OCP){           //Voltage measured between RE and WE of channel 0     
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
