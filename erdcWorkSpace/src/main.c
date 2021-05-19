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

//ERDC File(s)
#include "craabUtil.h" 
#include "voltammetry.h"
#include "eis.h"

void runTest(char mode);
char getTestMode(void);

char* version = "2021.05.11";

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
     *3 EIS                      *
    ******************************/
    while(1){
      printf("%s%s%s", "[:MAIN:", version, "]");     //NEED TO ADD BETTER SYSTEM FOR VERSIONING
      
      testMode = getTestMode();         //test mode input, reads only the first character in szInString
      
      if(testMode=='1'){
        runTest(testMode);              //Cyclic Voltammetry
      }
      
      if(testMode=='2'){  
        runTest(testMode);              //Squarewave Voltammetry 
      }
      
      if(testMode=='3'){
        runTest(testMode);              //Electrochemical Impedance Spectroscopy
      }  
    }
  }
  return 0;
}

void runTest(char mode){
  
  bool testComplete = false;
  
  if(mode=='1'){
        while(testComplete==false){
              printf("[START:CV]");
              runCV();
              printf("[END:CV]");
        }
  }
  
  if(mode=='2'){
        while(testComplete==false){
            printf("[START:SWV]");
            runSWV();  
            printf("[END:SWV]");
            
            flag_reset();
            testComplete = true;
            return;
        }
  }
  
  if(mode=='3'){
        printf("[START:EIS]");
        getEISFrequencies();
        runEIS();
        printf("[END:EIS]");
  }
}  

char getTestMode(void){
    char testMode = 0;
	uint8_t *uBuffer;
	uBuffer=return_uart_buffer();
    while(testMode==0){
      if(get_flag()){
        testMode = uBuffer[0];
        flag_reset();
      }
    }
    return testMode;
}
