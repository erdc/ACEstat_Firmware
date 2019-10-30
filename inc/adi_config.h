#if !defined (__CC_ARM)
#define RELOCATE_IVT 1             // Map interrupt vector table into SRAM - Comment out to map to flash
#endif

/* ISRAM is enable by default and can be disabled by below macro */
#define ADI_DISABLE_INSTRUCTION_SRAM

/* To enable the  cache. Please note taht linker description  file need to
   have appropriate memeory mapping.  */
/* #define ENABLE_CACHE */
