
#include "ACEstat_eis.h"
#include "ACEstat_misc.h"

/**EIS Helper functions/variables, provided by Analog devices*/
#define APPBUFF_SIZE 512
uint32_t AppBuff[APPBUFF_SIZE];

int32_t ImpedanceShowResult(uint32_t *pData, uint32_t DataCount)
{
  float freq;
  
  fImpPol_Type *pImp = (fImpPol_Type*)pData;
  AppIMPCtrl(IMPCTRL_GETFREQ, &freq);
  
  printf("%.2f,", freq);
  /*Process data*/
  for(int i=0;i<DataCount;i++)
  {
    printf("%f,%f\n",pImp[i].Magnitude,pImp[i].Phase*180/MATH_PI);
  }
  return 0;
}

static int32_t AD5940PlatformCfg(void)
{
  CLKCfg_Type clk_cfg;

  AD5940_Initialize();
  /* Platform configuration */
  /* Step1. Configure clock */
  clk_cfg.ADCClkDiv = ADCCLKDIV_1;
  clk_cfg.ADCCLkSrc = ADCCLKSRC_HFOSC;
  clk_cfg.SysClkDiv = SYSCLKDIV_1;
  clk_cfg.SysClkSrc = SYSCLKSRC_HFOSC;
  clk_cfg.HfOSC32MHzMode = bFALSE;
  clk_cfg.HFOSCEn = bTRUE;
  clk_cfg.HFXTALEn = bFALSE;
  clk_cfg.LFOSCEn = bTRUE;
  AD5940_CLKCfg(&clk_cfg);
  
  /* Step3. Interrupt controller */
  AD5940_INTCCfg(AFEINTC_1, AFEINTSRC_ALLINT, bTRUE);           /* Enable all interrupt in Interrupt Controller 1, so we can check INTC flags */
  AD5940_INTCCfg(AFEINTC_0, AFEINTSRC_DATAFIFOTHRESH, bTRUE);   /* Interrupt Controller 0 will control GP0 to generate interrupt to MCU */
  AD5940_INTCClrFlag(AFEINTSRC_ALLINT);

  AD5940_SleepKeyCtrlS(SLPKEY_UNLOCK);  /* Allow AFE to enter sleep mode. */
  return 0;
}

/**Modified from AD SDK version to allow passing of some user defined test parameters*/
AppIMPCfg_Type* AD5940ImpedanceStructInit()
{
  AppIMPCfg_Type *pImpedanceCfg;
  
  AppIMPGetCfg(&pImpedanceCfg);
  /* Step1: configure initialization sequence Info */
  pImpedanceCfg->SeqStartAddr = 0;
  pImpedanceCfg->MaxSeqLen = 512;
  
  pImpedanceCfg->RcalVal = 200.0;
  pImpedanceCfg->SinFreq = 1000.0;
  pImpedanceCfg->FifoThresh = 6;
  pImpedanceCfg->ImpODR = 10;                /* 10 Hz output data rate rate */
  
  /* Configure EC Sensor Parameters */
  /*Sensor is connected to CH0 on EVAL-ADuCM355QSPZ */
  pImpedanceCfg->SensorCh0.LpTiaRf = LPTIARF_1M;         /* 1Mohm Rfilter, 4.7uF cap connected external on AIN4 */
  pImpedanceCfg->SensorCh0.LpTiaRl = LPTIARLOAD_10R;     /* 10ohm Rload */
  pImpedanceCfg->SensorCh0.LptiaRtiaSel = LPTIARTIA_200R;  /* Configure TIA gain resistor*/
  pImpedanceCfg->SensorCh0.Vzero = 1100;                  /* Set Vzero = 1100mV. Voltage on SE0 pin*/
  pImpedanceCfg->SensorCh0.SensorBias = 00;              /* 0V bias voltage */
  
  /* Set switch matrix to connect to sensor in Ch0 for impedance measurement. */
  pImpedanceCfg->DswitchSel = SWD_CE0;
  pImpedanceCfg->PswitchSel = SWP_RE0;
  pImpedanceCfg->NswitchSel = SWN_SE0LOAD;
  pImpedanceCfg->TswitchSel = SWT_SE0LOAD;
  
/* The dummy sensor is as low as 5kOhm. We need to make sure RTIA is 
    small enough that HSTIA won't be saturated. */
  pImpedanceCfg->HstiaRtiaSel = HSTIARTIA_200;	
  
  /* Configure the sweep function. */
  pImpedanceCfg->SweepCfg.SweepEn = bTRUE;
  
  pImpedanceCfg->SweepCfg.SweepStart = 100;	/* Set start frequency*/
  pImpedanceCfg->SweepCfg.SweepStop = 1000;	/* Set final frequency */
  pImpedanceCfg->SweepCfg.SweepPoints = 10;		/* Set number of points for sweep*/
  
  pImpedanceCfg->SweepCfg.SweepLog = bTRUE;
  /* Configure Power Mode. Use HP mode if frequency is higher than 80kHz. */
  pImpedanceCfg->PwrMod = AFEPWR_LP;
  /* Configure filters if necessary */
  pImpedanceCfg->ADCSinc3Osr = ADCSINC3OSR_4;		
  pImpedanceCfg->DftNum = DFTNUM_16384;
  pImpedanceCfg->DftSrc = DFTSRC_SINC3;
  
  return pImpedanceCfg;
}
/**End Analog Devices' EIS Helper functions/variables*/

void runEIS(void){

  /**Get the EIS frequency ranges as floats over UART*/
  printf("[:FSTARTI]");
  float start_freq = get_frequency();            
  printf("[:FSTOPI]");                    
  float stop_freq = get_frequency(); 
  printf("[:NUMPOINTSI]");
  int num_points = get_parameter(3);
  printf("[START:EIS]");
  
  uint32_t temp;  
  AD5940_MCUResourceInit(0);
  
  /**Setup ADuCM355 impedance spectroscopy test, based on Analog Devices' application example*/
  AD5940PlatformCfg();                  //Configure AFE and system variables for EIS
  
  /**Create configuration object for EIS test with generic parameters*/
  AppIMPCfg_Type* testCfg = AD5940ImpedanceStructInit();          //Initialize struct to store EIS test parameters
  
  /**Modify test object with user parameters (hardcoded for now while debugging)*/
  testCfg->SweepCfg.SweepStart = 1;
  testCfg->SweepCfg.SweepStop = 75000;
  testCfg->SweepCfg.SweepPoints = 30;
  
  AppIMPInit(AppBuff, APPBUFF_SIZE);    /* Initialize IMP application. Provide a buffer, which is used to store sequencer commands */
  AppIMPCtrl(IMPCTRL_START, 0);          /* Control IMP measurment to start. Second parameter has no meaning with this command. */
  
  uint16_t ctr = 0;
  
  while(ctr < num_points)
  {
    if(AD5940_GetMCUIntFlag())
    {
      AD5940_ClrMCUIntFlag();
      temp = APPBUFF_SIZE;
      AppIMPISR(AppBuff, &temp);
      ImpedanceShowResult(AppBuff, temp);
      ++ctr;
    }
  }
  printf("[END:EIS]");
  NVIC_SystemReset();                   //ARM DIGITAL SOFTWARE RESET
}
