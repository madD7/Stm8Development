/**************************************** MAD Engineers ****************************************

  MAD Engineers
  Copyright (c) 2014

Description	: 

Revision History **************************************************************************
** Date ** ** Coder ** ***** Remarks ******************************************************
* DDMMYY * ** madD7 ** * Originator                                                       *

*/



#ifndef		__STM8S_SDCC_H_     //Replace filename
#define		__STM8S_SDCC_H_     //Replace filename



/* Include Files **************************************************************************
 * @{
 */

/*
 * @}
 */


/* Data Types & Variables *****************************************************************
 * @{
 */

/*============================== Interrupt vector Handling ========================*/
#ifdef INTERRUPT_HANDLER
 #undef		INTERRUPT_HANDLER
#endif 
#define		INTERRUPT_HANDLER(a,b)		void a(void) __interrupt (b)

#ifdef INTERRUPT_HANDLER_TRAP
 #undef INTERRUPT_HANDLER_TRAP
#endif
#define		INTERRUPT_HANDLER_TRAP(a)	void a(void) __trap

#ifdef enableInterrupts
 #undef enableInterrupts
#endif 
#define enableInterrupts()    {__asm__ ("rim");}  /* enable interrupts */

#ifdef disableInterrupts
 #undef disableInterrupts
#endif
#define disableInterrupts()   {__asm__ ("sim");}  /* disable interrupts */ 

#ifdef rim
 #undef rim
#endif
#define rim()                 {__asm__ ("rim");}  /* enable interrupts */

#ifdef sim
 #undef sim
#endif
#define sim()                 {__asm__ ("sim");}  /* disable interrupts */

#ifdef nop
 #undef nop
#endif
#define nop()                 {__asm__ ("nop");}  /* No Operation */

#ifdef trap
 #undef trap
#endif
#define trap()                {__asm__ ("trap");} /* Trap (soft IT) */
 
#ifdef wfi
 #undef wfi
#endif
#define wfi()                 {__asm__ ("wfi");}  /* Wait For Interrupt */

#ifdef halt
 #undef halt
#endif
#define halt()                {__asm__ ("halt");} /* Halt */


/*
 * @}
 */



/* Functions ******************************************************************************
 * @{
 */


/*
 * @}
 */


#endif


/* ~~~~~ END OF FILE ~~~~~ */

