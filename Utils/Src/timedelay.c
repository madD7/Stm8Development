/**************************************** MAD Engineers ****************************************

  MAD Engineers
  Copyright (c) 2014

Description	: 

Revision History **************************************************************************
** Date ** ** Coder ** ***** Remarks ******************************************************
* DDMMYY * ** madD7 ** * Originator                                                       *

*/



/* Include Files **************************************************************************
 * @{
 */
#include <timedelay.h>

/*
 * @}
 */


/* Variables ******************************************************************************
 * @{
 */


/*
 * @}
 */



/* Functions ******************************************************************************
 * @{
 */
/***************************************************************************************
Description	: Generates exact delay for stm8 operating @ 16MHz
Input		: 
Output		: None
Returns		: 
Notes		: None
*/
void _ms_delay(unsigned int delay)
{
	unsigned long TotalWait = DELAY_MUL * delay;
	volatile unsigned long cntr = 0;				// to prevent compiler from optimising

	for ( cntr=0; cntr<TotalWait; cntr++)
		;
}


/***************************************************************************************
Description	: Approx delay in micro seconds for stm8 operating @ 16MHz 
Input		: 
Output		: None
Returns		: 
Notes		: None
*/
void _us_delay(unsigned int delay)
{
    unsigned long TotalWait = (DELAY_MUL * delay)/MICROS_IN_MILLI;
    volatile unsigned long cntr = 0;                // to prevent compiler from optimising

    for ( cntr=0; cntr<TotalWait; cntr++)
        ;
}


/*
 * @}
 */





/* ~~~~~ END OF FILE ~~~~~ */

