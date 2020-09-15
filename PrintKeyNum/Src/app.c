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
Description	: 
Input		: 
Output		: None
Returns		: 
Notes		: None
*/
static void LoopTest2()
{
	uint8_t PosCntr=0;
	uint8_t SegCntr=0;
	uint8_t value=0;

	for ( PosCntr=0; PosCntr < SSD_DISPLAY_USED; PosCntr++)
	{
		for (SegCntr=0; SegCntr < SSD_SEG_G; SegCntr++)
		{
			value |= SegmentValue[SegCntr];
			TM1637_WrByte(PosCntr, value);
		}

		for (SegCntr=0; SegCntr < SSD_SEG_G; SegCntr++)
        {
            value &= ~SegmentValue[SegCntr];
            TM1637_WrByte(PosCntr, value);
        }	
	}
}

/***************************************************************************************
Description	: C entry point
Input		: 
Output		: None
Returns		: 
Notes		: None
*/
void main(void)
{
	uint16_t cntr=0;
	uint8_t bytes=0;
	uint8_t PosCntr=0;
	uint8_t key=0;

	GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
	TM1637_Init();

	LoopTest2();

	while(TRUE)
	{
		GPIO_WriteReverse( GPIOB, GPIO_PIN_5);	
		_ms_delay(1000);

		TM1637_GetKey(&key);

		if ( key < KEY_NUM_F)
		{
			TM1637_WrByte(1, SSD_CLEAR);
			TM1637_WrByte(1, DigitToSegment[key]);
			TM1637_DisplayOn(MAX_BRIGHTNESS, ENABLE);
		}

		key=0;
		//TM1637_WrByte(1, key);
        //TM1637_DisplayOn(MAX_BRIGHTNESS, ENABLE);
	}
}

/*
 * @}
 */





/* ~~~~~ END OF FILE ~~~~~ */

