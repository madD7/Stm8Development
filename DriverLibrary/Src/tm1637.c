/**************************************** MAD Engineers ****************************************

  MAD Engineers
  Copyright (c) 2014

Description	: 

Revision History **************************************************************************
** Date ** ** Coder ** ***** Remarks ******************************************************
* DDMMYY * ** madD7 ** * Originator                                                       *

*/


#define _TM1637_MODULE_

/* Include Files **************************************************************************
 * @{
 */
#include <app.h>
#include <tm1637.h>

/*
 * @}
 */


/* Variables ******************************************************************************
 * @{
 */

#define 	TM1637_PORT				GPIOA			// Stm8 PortA

#define		TM1637_CLK_PIN			GPIO_PIN_1		// PA 1 					
#define		TM1637_DATA_PIN			GPIO_PIN_2		// PA 2 

#define 	TM1637_CLK_PIN_LOW()	GPIO_WriteLow(TM1637_PORT, TM1637_CLK_PIN)
#define		TM1637_CLK_PIN_HIGH()	GPIO_WriteHigh(TM1637_PORT, TM1637_CLK_PIN)

#define		TM1637_DATA_PIN_LOW()	GPIO_WriteLow(TM1637_PORT, TM1637_DATA_PIN)
#define		TM1637_DATA_PIN_HIGH()	GPIO_WriteHigh(TM1637_PORT, TM1637_DATA_PIN)

/*
 * @}
 */



/* Functions ******************************************************************************
 * @{
 */

/***************************************************************************************
Description	: Start Transmission 
Input		: 
Output		: None
Returns		: 
Notes		: None
*/
static void TM1637_StartTx()
{
	TM1637_DATA_PIN_HIGH();
	TM1637_CLK_PIN_HIGH();

	_us_delay(BIT_DELAY);

	TM1637_DATA_PIN_LOW();
}


/***************************************************************************************
Description	: Stop Transmission
Input		: 
Output		: None
Returns		: 
Notes		: None
*/
static void TM1637_StopTx()
{	
	TM1637_CLK_PIN_LOW();
	_us_delay(BIT_DELAY);
	TM1637_DATA_PIN_LOW();
	_us_delay(BIT_DELAY);
	TM1637_CLK_PIN_HIGH();
	_us_delay(BIT_DELAY);
	TM1637_DATA_PIN_HIGH();
}


/***************************************************************************************
Description	: 
Input		: 
Output		: None
Returns		: 
Notes		: None
*/
static Status_Type TM1637_GetAck()
{
	uint8_t pinState=1;

	TM1637_CLK_PIN_LOW();
	_us_delay(BIT_DELAY);

	//Read Data pin input
	while (pinState)
		pinState = ( GPIO_ReadInputData(TM1637_PORT) & TM1637_DATA_PIN);
	
	TM1637_CLK_PIN_HIGH();
	_us_delay(BIT_DELAY);
	TM1637_CLK_PIN_LOW();

	return (Status_Type) pinState;
}


/***************************************************************************************
Description	: 
Input		: 
Output		: None
Returns		: 
Notes		: None
*/
static Status_Type TM1637_TxOnlyByte(uint8_t byte)
{
	uint8_t cntr=0;
    Status_Type ackStatus=StatusSuccess;

    for ( cntr=0; cntr < BITS_IN_BYTE; cntr++)
    {
        TM1637_CLK_PIN_LOW();
        _us_delay(BIT_DELAY);

        if ( byte & 0x01 )
            TM1637_DATA_PIN_HIGH();
        else
            TM1637_DATA_PIN_LOW();

        _us_delay(BIT_DELAY);

        TM1637_CLK_PIN_HIGH();
        _us_delay(BIT_DELAY);

        byte = byte >> 1;
    }

    ackStatus = TM1637_GetAck();

	return ackStatus;
}


/***************************************************************************************
Description	: Initialize TM1637 
Input		: 
Output		: None
Returns		: 
Notes		: None
*/
void TM1637_Init()
{
	GPIO_Init(TM1637_PORT, TM1637_CLK_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);
	GPIO_Init(TM1637_PORT, TM1637_DATA_PIN, GPIO_MODE_OUT_PP_HIGH_SLOW);

	TM1637_CLK_PIN_LOW();
	TM1637_DATA_PIN_LOW();
}

/***************************************************************************************
Description	: 
Input		: 
Output		: None
Returns		: 
Notes		: None
*/
Status_Type TM1637_DisplayOn(uint8_t val, uint8_t status)
{
	Status_Type ackStatus=StatusSuccess;
	val &= BRIGHTNESS_BIT_MASK;

	if ( status == ENABLE )
		val |= TURN_DISPLAY_ON; 
	else
		val &= ~TURN_DISPLAY_OFF;

	TM1637_StartTx();
	ackStatus = TM1637_TxOnlyByte( DCR_BASE_CMD | val );
	TM1637_StopTx();

	return ackStatus;
}


/***************************************************************************************
Description	: Write single byte into the TM1637
Input		: None
Output		: None
Returns		: 
Notes		: None
*/
Status_Type TM1637_WrByte(uint8_t Pos, uint8_t byte)
{
	uint8_t cntr=0;
	Status_Type ackStatus=StatusSuccess; 

	if ( Pos > MAX_SSD_DISPLAY )
	{
		return StatusInvalParam;
	}

	// Send Command  
	TM1637_StartTx();
	ackStatus = TM1637_TxOnlyByte(WRITE_TO_DISPLAY_REG_CMD | FIXED_ADDR_MODE_WITH_CMD); 
	TM1637_StopTx();
	if ( ackStatus != StatusSuccess )
		return ackStatus;

	// Send Position Addr
	TM1637_StartTx();
	ackStatus = TM1637_TxOnlyByte( ACS_BASE_CMD + Pos ); 
	if ( ackStatus != StatusSuccess )
	{
		TM1637_StopTx();
		return ackStatus;
	}

	ackStatus = TM1637_TxOnlyByte(byte);
	TM1637_StopTx();
	if ( ackStatus != StatusSuccess )
		return ackStatus;

	// Turn On Display
	//ackStatus = TM1637_DisplayOn(MAX_BRIGHTNESS, ENABLE);

	return ackStatus;
}


/***************************************************************************************
Description	: 
Input		: 
Output		: None
Returns		: 
Notes		: None
*/
Status_Type TM1637_WrString(uint8_t Pos, char* pBuf, uint8_t strlen, uint8_t* pDigitsWritten)
{
	uint8_t byteBuf[MAX_SSD_DISPLAY+1];
	uint8_t cntr=0;
	uint8_t val=0;
	Status_Type ackStatus=StatusSuccess;

	*pDigitsWritten = cntr;

	if ( (strlen + Pos) > MAX_SSD_DISPLAY )
	{
		return StatusInvalParam; 
	}

	// Check valid ascii and reverse the string
	for ( cntr=0; cntr < strlen ; cntr++)
	{
		val = pBuf[strlen-cntr];

		// Check for valid ascii range
		if ( (val >= '0') && (val <= 'Z') )
			byteBuf[cntr] = DigitToSegment[(val-'0')]; 
		// for small ascii alphabets 
		else if ( (val >= 'a') && (val <= 'z') )
			byteBuf[cntr] = DigitToSegment[((val-'a')+'A')];
		else
			return StatusOutOfRange;
	}

	// Send Command  
	TM1637_StartTx();
	ackStatus = TM1637_TxOnlyByte(WRITE_TO_DISPLAY_REG_CMD & ~AUTO_ADDR_INCR_WITH_CMD); 
	TM1637_StopTx();
	if ( ackStatus != StatusSuccess )
		return ackStatus;

	// Send Position Addr
	TM1637_StartTx();
	ackStatus = TM1637_TxOnlyByte( ACS_BASE_CMD + Pos ); 
	if ( ackStatus != StatusSuccess )
	{
		TM1637_StopTx();
		return ackStatus;
	}

	for (cntr=0; cntr<strlen; cntr++)
	{
		ackStatus = TM1637_TxOnlyByte(byteBuf[cntr]);
		TM1637_StopTx();
		if ( ackStatus != StatusSuccess )
			return ackStatus;
		
		*pDigitsWritten = cntr;
	}

	// Turn On Display
	ackStatus = TM1637_DisplayOn(MAX_BRIGHTNESS, ENABLE);
	return ackStatus;
}


/***************************************************************************************
Description	: Get Key value
Input		: 
Output		: None
Returns		: 
Notes		: None
*/
Status_Type TM1637_GetKey(uint8_t *pKey)
{
	uint8_t key=0;	
	uint8_t cntr=0;
	uint8_t pinState=0;
	Status_Type ackStatus=0;

	*pKey = StatusFail;
	// Send Command
    TM1637_StartTx();
    ackStatus = TM1637_TxOnlyByte(READ_KEY_SCAN_DATA_CMD);
	if ( ackStatus != StatusSuccess )
	{
		TM1637_StopTx();
        return ackStatus;
	}

	TM1637_DATA_PIN_HIGH();

	for (cntr=0; cntr<BITS_IN_BYTE; cntr++)
	{
    	TM1637_CLK_PIN_LOW();

		key = key >> 1;
    	_us_delay(BIT_DELAY*5);

    	TM1637_CLK_PIN_HIGH();
    	_us_delay(BIT_DELAY/2);

    	//Read Data pin input
    	pinState = ( GPIO_ReadInputData(TM1637_PORT) & TM1637_DATA_PIN) ;
		if ( pinState )
			key |= (0x80);

		pinState=0;
		_us_delay(BIT_DELAY*5);
	}

	ackStatus = TM1637_GetAck();
    TM1637_StopTx();
	
	*pKey = GET_KEY_NUM(key);

	if ( *pKey > KEY_NUM_F )
		*pKey = StatusFail;

    return ackStatus;
}

/*
 * @}
 */





/* ~~~~~ END OF FILE ~~~~~ */

