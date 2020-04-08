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

void runTest(char mode){
  
  bool testComplete = false;
  
  if(mode=='1'){
        printf("\nCyclic voltammetry selected\n");
        printf("Enter Starting Voltage and Ending Voltage. Zero is offset at 1100mV\n");
        printf("Also enter a number for max current 0: 4.5mA, 1: 900uA, 2: 180uA,\n 3: 90uA, 4: 45uA, 5: 22.5uA, 6: 11.25uA, 7: 5.625uA\n");
        printf("Ex: 070015004 is -400 to 400 max current 45uA\n");
        while(testComplete==false){
          if(get_flag()){
              printf("Running cyclic voltammetry test\n");
              runCV(return_uart_buffer());
              printf("Cyclic voltammetry test concluded\n\n");
              
              flag_reset();
              testComplete = true;
              return;
          }
        }
  }
  
  if(mode=='2'){
        printf("\nSquarewave voltammetry selected\n");
        printf("Enter Starting Voltage and Ending Voltage. Middle is 1100mV\n");
        printf("Also enter a number for max current 0: 4.5mA, 1: 900uA, 2: 180uA,\n 3: 90uA, 4: 45uA, 5: 22.5uA, 6: 11.25uA, 7: 5.625uA\n");
        printf("Also enter amplitide, and deposition time\n");
        printf("Ex: 070015004100020 is -400 to 400 max current 45uA Amplitude 100 20 second deposition time at the start voltage\n");
        while(testComplete==false){
          if(get_flag()){
            reflectUART();
            printf("Running squarewave voltammetry test\n");
            runSWV(return_uart_buffer());  
            printf("Squarewave voltammetry test concluded\n\n");
            
            flag_reset();
            testComplete = true;
            return;
          }
        }
  }
  
  if(mode=='3'){
        printf("\nElectrochemical impedance spectroscopy selected\n");
        getEISFrequencies();
        runEIS();
        printf("\nElectrochemical impedance spectroscopy test concluded");
        
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
