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
    printf("(1)Cyclic Voltammetry\n");
    printf("(2)Squarewave Voltammetry\n");
    printf("(3)Electrochemical Impedance Spectroscopy\n");

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

