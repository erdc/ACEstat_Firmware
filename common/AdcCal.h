
#include <AfeAdcLib.h>
#include <AfeTiaLib.h>


/*=========================== Function declarations ====================*/
uint32_t AdcOffsetCalInit(uint32_t u32Gain, uint8_t u8PwrMode);
uint32_t AdcGainCalInit(uint32_t u32Gain, uint8_t u8PwrMode);
uint32_t AdcGainCalLP(uint8_t u8Gain);
uint32_t AdcOffsetCalAdjust(uint32_t u32Gain,
                        uint32_t u32FacOffset,
                        int32_t iAdcDat);
uint32_t AdcGainCalAdjust(uint32_t u32PGAGain,
                        uint32_t u32FactoryGain,
                        int32_t iAvgSamples,
                        float fVTarget,
                        float fVref,
                        float fVbiasCap,
                        float kFactor);
float PGAAdjustFactor(void);
uint32_t ReadGainCal(uint32_t u32Gain);



