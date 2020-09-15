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
static void LoopTest1()
{
	uint8_t PosCntr=0;

	TM1637_WrByte(0, SegmentValue[SSD_SEG_F] |
						SegmentValue[SSD_SEG_E]);

	TM1637_WrByte(0, SegmentValue[SSD_SEG_F] |
						SegmentValue[SSD_SEG_E] |
						SegmentValue[SSD_SEG_A] |
						SegmentValue[SSD_SEG_D]);

	TM1637_WrByte(1, SegmentValue[SSD_SEG_A] |
						SegmentValue[SSD_SEG_D]);

	TM1637_WrByte(2, SegmentValue[SSD_SEG_A] | 
						SegmentValue[SSD_SEG_D]);

	TM1637_WrByte(3, SegmentValue[SSD_SEG_A] |
						SegmentValue[SSD_SEG_D]);

	TM1637_WrByte(3, SegmentValue[SSD_SEG_A] |
						SegmentValue[SSD_SEG_B] |
						SegmentValue[SSD_SEG_C] |
						SegmentValue[SSD_SEG_D]);
	
	TM1637_WrByte(3, SegmentValue[SSD_SEG_G]);
	TM1637_WrByte(2, SegmentValue[SSD_SEG_G]);
	TM1637_WrByte(1, SegmentValue[SSD_SEG_G]);
	TM1637_WrByte(0, SegmentValue[SSD_SEG_G]);

	for ( PosCntr=SSD_DISPLAY_USED; PosCntr > 0; PosCntr--)
	{
		TM1637_WrByte(PosCntr, SSD_CLEAR);
	}
}


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

	GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
	TM1637_Init();

	for ( PosCntr=0; PosCntr < SSD_DISPLAY_USED; PosCntr++)
	{
		TM1637_WrByte(PosCntr, SSD_CLEAR);
	}

	TM1637_DisplayOn(MAX_BRIGHTNESS, ENABLE);
	LoopTest1();
	TM1637_DisplayOn(MAX_BRIGHTNESS, ENABLE);
	LoopTest2();

	TM1637_DisplayOn(MAX_BRIGHTNESS, ENABLE);
	for ( PosCntr=0; PosCntr < SSD_DISPLAY_USED; PosCntr++)
    {
        TM1637_WrByte(PosCntr, DigitToSegment[8]);
    }

	for (PosCntr=0;PosCntr < (3); PosCntr++)
	{
		TM1637_DisplayOn(MAX_BRIGHTNESS, ENABLE);
		_ms_delay(75);
		TM1637_DisplayOn(MAX_BRIGHTNESS, DISABLE);
		_ms_delay(50);
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

