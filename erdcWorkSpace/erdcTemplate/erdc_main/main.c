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

void runTest(char mode);
bool restartTest(void);
char getTestMode(void);

int main(void){
  /*setup functions. only run when board powers on*/
  AfeWdtGo(false);
  ClockInit();
  UartInit();
  DioOenPin(pADI_GPIO2,PIN4,1);               // Enable P2.4 as Output to toggle DS2 LED
  DioPulPin(pADI_GPIO2,PIN4,1);               // Enable pull-up
  DioTglPin(pADI_GPIO2,PIN4);                 // LED ON
  delay_10us(10);                             //settling delay
  /*End powerup setup*/
  
  char testMode = 0;
  bool restart = false;
  
  while(1){

    //Test mode selection
    restart=false;    
    printf("Select a test to run:\n");
    printf("(1)Cyclic Voltammetry (CV)\n");
    printf("(2)Square-wave Voltammetry (SWV)\n");
    printf("(3)Electrochemical Impedance Spectroscopy (EIS)\n");

    while(restart==false){
      
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
      
      if(restartTest() == true){        //Prompts the user to either restart or end.  Restarting returns to test mode selection prompts
        restart = true;
      }
      
      else{
        printf("Not running any more tests, use board reset button to restart");
        return 0;
      }
      
    }
  }
  return 0;
}

void runTest(char mode){
  
  bool testComplete = false;
  
  if(mode=='1'){
        while(testComplete==false){
          //if(get_flag()){
              printf("Running CV...\n");
              runCV();
              printf("...CV concluded\n\n");
              
              flag_reset();
              testComplete = true;
              return;
          //}
        }
  }
  
  if(mode=='2'){
        while(testComplete==false){
          //if(get_flag()){
            printf("Running SWV...\n");
            runSWV();  
            printf("...SWV concluded\n\n");
            
            flag_reset();
            testComplete = true;
            return;
          //}
        }
  }
  
  if(mode=='3'){
        printf("\nElectrochemical impedance spectroscopy selected\n");
        getEISFrequencies();
        runEIS();
        printf("...EIS concluded");
        
        flag_reset();
        testComplete = true;
        return;
  }
     
     
  else{
    printf("Invalid Test Mode Parameter Selected\nValid Modes are {1:CV, 2:SWV: 3:EIS}\n");
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

bool restartTest(void){
  bool answer;
  
  printf("\nRun another test?\n");
  printf("(1) Yes\n(2) No\n");
  uint8_t *uBuffer;
  uBuffer=return_uart_buffer();
  
  while(1){
    if(get_flag()){
      if(uBuffer[0]=='1'){answer = true;}
      else{answer = false;}
      flag_reset();
      
      return answer;
    }
  }
}
