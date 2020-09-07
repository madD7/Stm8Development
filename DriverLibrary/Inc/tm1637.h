/**************************************** MAD Engineers ****************************************

  MAD Engineers
  Copyright (c) 2014

Description	: 

Revision History **************************************************************************
** Date ** ** Coder ** ***** Remarks ******************************************************
* DDMMYY * ** madD7 ** * Originator                                                       *

*/

#ifndef		__TM1637_H_     //Replace filename
#define		__TM1637_H_     //Replace filename



/* Include Files **************************************************************************
 * @{
 */
#include <types.h>
/*
 * @}
 */


/* Data Types & Variables *****************************************************************
 * @{
 */

#define MAX_SSD_DISPLAY					(6)

/* DATA COMMAND SETTING (DCS) */
#define DCS_BASE_CMD					(0x40)
#define WRITE_TO_DISPLAY_REG_CMD		(0x40)
#define READ_KEY_SCAN_DATA_CMD			(0x42)

#define AUTO_ADDR_INCR_WITH_CMD			((1<<2))			// Clear the 3rd Bit. Eg: x &= ~AUTO_ADDR_INCR_WITH_CMD; 
#define FIXED_ADDR_MODE_WITH_CMD		((1<<2))
#define NORMAL_MODE_WITH_CMD			((1<<3))			// Clear the 4th Bit. Eg: x &= ~NORMAL_MODE_WITH_CMD; 
#define TEST_MODE_WITH_CMD				((1<<3))			


/* DISPLAY CONTROL (DCR) */
#define DCR_BASE_CMD					(0x80)
#define PULSE_WIDTH_DIV16				(0x80)
#define PULSE_WIDTH_DIV8				(0x81)
#define	PULSE_WIDTH_DIV4				(0x82)
#define	PULSE_WIDTH_10DIV16				(0x83)				// Pulse width = 10/16
#define PULSE_WIDTH_11DIV16				(0x84)				// Pulse width = 11/16
#define PULSE_WIDTH_12DIV16				(0x85)				// Pulse width = 12/16
#define PULSE_WIDTH_13DIV16				(0x86)				// Pulse width = 13/16
#define PULSE_WIDTH_14DIV16				(0x87)				// Pulse width = 14/16

#define TURN_DISPLAY_OFF				(1<<3)				// Clear the 4th bit. 
#define TURN_DISPLAY_ON					(1<<3)

#define PULSE_WIDTH_BIT_MASK			(0x07)
#define BRIGHTNESS_BIT_MASK				(0x07)

#define MAX_BRIGHTNESS					(0x07)

/* ADDRESS COMMAND SETTING (ACS) */
#define ACS_BASE_CMD					(0xC0)
#define DISPLAY0_ADDR					(0xC0)
#define DISPLAY1_ADDR					(0xC1)
#define DISPLAY2_ADDR					(0xC2)
#define DISPLAY3_ADDR					(0xC3)
#define	DISPLAY4_ADDR					(0xC4)
#define DISPLAY5_ADDR					(0xC5)

// Logical OR with the value to display dot on SSD 
#define SHOW_DOT						(0b10000000)

#ifdef		_TM1637_MODULE_
//
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D
// For value position, subtract the ascii char - ascii 0
const uint8_t DigitToSegment[] = {
 // XGFEDCBA
  0b00111111,   // 0
  0b00000110,   // 1
  0b01011011,   // 2
  0b01001111,   // 3
  0b01100110,   // 4
  0b01101101,   // 5
  0b01111101,   // 6
  0b00000111,   // 7
  0b01111111,   // 8
  0b01101111,   // 9
  0b00000000,	// :
  0b00000000,	// ;
  0b00000000,	// <
  0b00000000,	// =
  0b00000000,	// >
  0b00000000,	// ?
  0b00000000,	// @
  0b01110111,   // A
  0b01111100,   // b
  0b00111001,   // C
  0b01011110,   // d
  0b01111001,   // E
  0b01110001,   // F
  0b00111101,	// G
  0b01110100,	// h
  0b00110000,	// I
  0b00011110,	// J
  0b01110101,	// K
  0b00111000,	// L
  0b00010101,	// M
  0b01010100,	// n
  0b00111111,	// O
  0b01110011,	// P
  0b01100111,	// q
  0b01010000,	// r
  0b01101101,	// s
  0b01111000,	// t
  0b00111110,	// U
  0b00011100,	// v
  0b00101010,	// w
  0b01110110,	// x
  0b01101110,	// Y
  0b01001011	// Z
  };

const uint8_t CheckSegments[] = {
	0b00000001,
	0b00000010,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b10000000
	};
#else
extern const uint8_t DigitToSegment[];
extern const uint8_t CheckSegments[];
#endif 

/*
 * @}
 */



/* Functions ******************************************************************************
 * @{
 */
void TM1637_Init();
Status_Type TM1637_DisplayOn(uint8_t val, uint8_t status);
Status_Type TM1637_WrByte(uint8_t Pos, uint8_t byte);
Status_Type TM1637_WrString(uint8_t Pos, uint8_t* pBuf, uint8_t strlen, uint8_t* pDigitsWritten);

/*
 * @}
 */


#endif


/* ~~~~~ END OF FILE ~~~~~ */

