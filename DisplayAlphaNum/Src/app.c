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

#include "app.h"
#include <tm1637.h>
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
Description	: C entry point
Input		: 
Output		: None
Returns		: 
Notes		: None
*/
void main(void)
{
	uint16_t cnt=0;

	GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
	TM1637_Init();

	TM1637_WrByte(0, 0);
	TM1637_WrByte(1, 0);
	TM1637_WrByte(2, 0);
	TM1637_WrByte(3, 0);
	
	// Numeric test
	for (cnt=0; cnt < 10; cnt++)
	{
		TM1637_WrByte(0, DigitToSegment[cnt]);
		_ms_delay(1000);
	}

	// Alpha Numeric test
	for (cnt=16; cnt<43; cnt++)
	{
		TM1637_WrByte(0, DigitToSegment[cnt]);
        _ms_delay(1000);
	}

	while(TRUE)
	{
		GPIO_WriteReverse( GPIOB, GPIO_PIN_5);
		
		_ms_delay(1000);
	}
}

/*
 * @}
 */





/* ~~~~~ END OF FILE ~~~~~ */

