/*!
 *****************************************************************************
 * @file:    system.c
 * @brief:   System startup code for ADuCM302x
 * @version: $Revision: 29764 $
 * @date:    $Date: 2015-02-17 00:45:59 -0500 (Tue, 17 Feb 2015) $
 *-----------------------------------------------------------------------------
 *
Copyright (c) 2010-2014 Analog Devices, Inc.

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
  - Modified versions of the software must be conspicuously marked as such.
  - This software is licensed solely and exclusively for use with processors
    manufactured by or for Analog Devices, Inc.
  - This software may not be combined or merged with other code in any manner
    that would cause the software to become subject to terms and conditions
    which differ from those listed here.
  - Neither the name of Analog Devices, Inc. nor the names of its
    contributors may be used to endorse or promote products derived
    from this software without specific prior written permission.
  - The use of this software may or may not infringe the patent rights of one
    or more patent holders.  This license does not release you from the
    requirement that you obtain separate licenses from these patent holders
    to use this software.

THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES, INC. AND CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
TITLE, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
NO EVENT SHALL ANALOG DEVICES, INC. OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, PUNITIVE OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, DAMAGES ARISING OUT OF CLAIMS OF INTELLECTUAL
PROPERTY RIGHTS INFRINGEMENT; PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *****************************************************************************/

/*! \addtogroup SYS_Driver System Interfaces
 *  @{
 */

#include <stdint.h>
#include "adi_config.h"
#include "system.h"
#include <ADuCM355.h>
#ifdef RELOCATE_IVT
extern void __relocated_vector_table;
#else
extern void __vector_table;
#endif
uint32_t SystemCoreClock;

#ifdef ADI_DEBUG
/* not needed unless its debug mode */
uint32_t lfClock = 0u;    /* "lf_clk" coming out of LF mux             */
#endif
uint32_t hfClock = 0u;    /* "root_clk" output of HF mux               */
uint32_t gpioClock = 0u;    /* external GPIO clock                       */

/*!
 * Initialize the system
 *
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System and update the relocate vector table.
 */
void SystemInit (void)
{
   /* Switch the Interrupt Vector Table Offset Register
   * (VTOR) to point to the relocated IVT in SRAM
   */
   // prevents the activation of all exceptions for NMI
   //__set_FAULTMASK(1);  // do all this in safe way
   __disable_irq();
   // switch from boot ROM IVT to application's IVT
   // set the System Control Block, Vector Table Offset Register
#ifdef RELOCATE_IVT
   SCB->VTOR = (uint32_t) &__relocated_vector_table;
#else
   SCB->VTOR = (uint32_t) &__vector_table;
#endif

   // set all three (USGFAULTENA, BUSFAULTENA, and MEMFAULTENA) fault enable bits
   // in the System Control Block, System Handler Control and State Register
   // otherwise these faults are handled as hard faults
   SCB->SHCSR = SCB_SHCSR_USGFAULTENA_Msk |
      SCB_SHCSR_BUSFAULTENA_Msk |
         SCB_SHCSR_MEMFAULTENA_Msk ;

   // flush instruction and data pipelines to insure assertion of new settings
   __ISB();  // MUST OCCURE IMMEDIATELY AFTER UPDATING SCB->CPACR!!!
   __DSB();

   adi_default_setting();
   //__set_FAULTMASK(0); //no exception masked.
   __enable_irq();

}


/*!
 * @brief  This enables or disables  the cache.
 * \n @param  bEnable : To specify whether to enable/disable cache.
 * \n              true : To enable cache.
 * \n
 * \n              false : To disable cache.
 * \n
 * @return none
 *
 */
void adi_system_EnableCache(bool_t bEnable)
{
   pADI_FLCC0_CACHE->KEY = CACHE_CONTROLLER_KEY;
   if(bEnable == true)
   {
      pADI_FLCC0_CACHE->SETUP |=BITM_FLCC_CACHE_SETUP_ICEN;
   }
   else
   {
      pADI_FLCC0_CACHE->SETUP &=(uint32_t)(~(BITM_FLCC_CACHE_SETUP_ICEN));
   }
}

/*!
 * @brief  This enables or disables instruction SRAM
 *
 * @param bEnable: To enable/disable the instruction SRAM.
 * \n              true : To enable cache.
 * \n
 * \n              false : To disable cache.
 * \n
 * @return none
 * @note:  Please note that respective linker file need to support the configuration.
 */
void adi_system_EnableISRAM(bool_t bEnable)
{
   if(bEnable == true)
   {
      pADI_PMG0_TST->SRAM_CTL |=BITM_PMG_TST_SRAM_CTL_INSTREN;
   }
   else
   {
      pADI_PMG0_TST->SRAM_CTL &=(uint32_t)(~(BITM_PMG_TST_SRAM_CTL_INSTREN));
   }
}

/*!
 * @brief  This enables/disable SRAM retention during the hibernation.
 * @param eBank:   Specify which SRAM bank. Only BANK1 and BANK2 are valid.
 * @param bEnable: To enable/disable the  retention for specified  SRAM bank.
 * \n              true : To enable retention during the hibernation.
 * \n
 * \n              false :To disable retention during the hibernation.
 * \n
 * @return : SUCCESS : Configured successfully.
 *           FAILURE :  For invalid bank.
 * @note: Please note that respective linker file need to support the configuration. Only BANK-1 and
          BANK-2 of SRAM is valid.
 */
uint32_t adi_system_EnableRetention(ADI_SRAM_BANK eBank,bool_t bEnable)
{
#ifdef ADI_DEBUG
   if((eBank != ADI_SRAM_BANK_1)&& (eBank != ADI_SRAM_BANK_2))
   {
      return(FAILURE);
   }

#endif
   pADI_PMG0->PWRKEY = PWRKEY_VALUE_KEY;
   if(bEnable == true)
   {
      pADI_PMG0->SRAMRET |= (eBank>>1);
   }
   else
   {
      pADI_PMG0->SRAMRET &=(uint32_t)(~((eBank>>1)));
   }
   return (SUCCESS);
}

void adi_default_setting(void)
{
   pADI_WDT0->CTL &=0xDF;                      // turn off digital die WDT
   *((volatile uint32_t*)0x400C0A28) = 0x08; //Always on: EI2CON
   /*Default clock gate setting*/
   *((volatile uint32_t*)0x400C0410) = 0x001A;
   /*INTC: INTCLR = 0xFFFF, clear boot load done intterrupt*/
   *((volatile uint32_t*)0x400C3004) = 0xFFFF;
   /*INTC: INTSEL0 = 0, disable Boot load done interrupt*/
   *((volatile uint32_t*)0x400C3008) = 0x0000;
   /*Enable input for internal GPIO2.1 for INTC*/
   pADI_GPIO2->IEN |= 0x0002;
   /*pADI_AFE->LPREFBUFCON = 0x0004;  */
   *((volatile uint32_t*)0x400C2050) = 0x0004;
   pADI_ALLON->CLKEN0 = 6; //enable AFE watch-dog timer.
   pADI_AFE->REPEATADCCNV = 1<<BITP_AFE_REPEATADCCNV_NUM;
}
/*@}*/
