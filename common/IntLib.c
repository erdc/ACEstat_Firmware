/**
 *****************************************************************************
   @file     IntLib.c
   @brief    Set of External interrupt control functions.
   @version  V0.1
   @author   ADI
   @date     February 2016
   @par Revision History:
   - V0.1, February 2016: initial version.


All files provided by ADI, including this file, are
provided  as is without warranty of any kind, either expressed or implied.
The user assumes any and all risk from the use of this code.
It is the responsibility of the person integrating this code into an application
to ensure that the resulting application performs as required and is safe.

**/
#include  "IntLib.h"

/**
	@brief int EiClr(int iEiNr)
			==========clear external interrupt flag
	@param iEiNr :{BITM_XINT_CLR_IRQ1,BITM_XINT_CLR_UART_RX_CLR}
		- 0x2: BITM_XINT_CLR_IRQ1, External Interrupt 1
		- 0x20: BITM_XINT_CLR_UART_RX_CLR, External UART RX wake-up

	@return 1
	@warning

**/
int EiClr(int iEiNr)
{
   pADI_XINT0->CLR =iEiNr;
   return 1;
}

/**
	@brief int EiCfg(int iEiNr,int iEnable, int iMode)
			==========configures external interrupt
        @param iEiNr :{EXTINT0,EXTINT1,EXTINT2,EXTINT3,EXTUARTRX}
                - 0x00000080: External interrupt 1
                - 0x00100000: EXTUARTRX
        @param iEnable :{INT_DIS,INT_EN}
                - 0x0: INT_DIS for disabled.
                - 0x1: INT_EN for enabled.
        @param iMode :{INT_RISE, INT_FALL, INT_EDGES, INT_HIGH, INT_LOW}
                - 0x0: INT_RISE Rising edge
                - 0x1: INT_FALL Falling edge
                - 0x2: INT_EDGES Rising or falling edge
                - 0x3: INT_HIGH High level
                - 0x4: INT_LOW Low level
	@return 1
	@warning
		the NVIC also needs to be configured
                external interrupts are available regardless of the GPIO configuration
                only ext int 0, 1 and 2 are available in SHUTDOWN mode
**/

int EiCfg(int iEiNr,int iEnable, int iMode)
{
   if (iEnable == INT_DIS)
   {
      pADI_XINT0->CFG0 &= ~(iEiNr);
   }
   else
   {
      pADI_XINT0->CFG0 |= iEiNr;
      switch( iEiNr)
      {
      case EXTINT0:
         pADI_XINT0->CFG0 |= iMode;
         break;
      case EXTINT1:
         pADI_XINT0->CFG0 |= (iMode<<4);
         break;
      case EXTINT2:
         pADI_XINT0->CFG0 |= (iMode<<8);
         break;
      case EXTINT3:
         pADI_XINT0->CFG0 |= (iMode<<12);
	 break;
      case EXTUARTRX:
         pADI_XINT0->CFG0 |= (iMode<<21);
         break;

      default:
         break;
      }
   }
   return pADI_XINT0->CFG0;
}



/**
   @brief int EiSta(void);
         ========== Read the External interrupt status register
   @return value of XINT0->EXT_STAT:
      - BITM_XINT_EXT_STAT_STAT_EXTINT1, External IRQ1.
      - BITM_XINT_EXT_STAT_STAT_UART_RXWKUP, UART RX wake-up
**/
int EiSta(void)
{
   return pADI_XINT0->EXT_STAT;
}

/**@}*/

