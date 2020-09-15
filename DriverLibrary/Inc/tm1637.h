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
#define SSD_CLEAR						(0b00000000)

#define KEY_0_VALUE						(0b11110111)

// Subtract binary code of K1 SG1 
#define GET_KEY_NUM(x)					((KEY_0_VALUE) - (x)) 

// To Index the Segment Bin Value from array Segment 
typedef enum
{
	SSD_SEG_A=0,
	SSD_SEG_B,
	SSD_SEG_C,
	SSD_SEG_D,
	SSD_SEG_E,
	SSD_SEG_F,
	SSD_SEG_G,
	SSD_SEG_DOT,
	SSD_SEG_CLEAR
}SSD_SEG_Type;


typedef enum
{
	KEY_NUM_0=0,
	KEY_NUM_1,
	KEY_NUM_2,
	KEY_NUM_3,
	KEY_NUM_4,
	KEY_NUM_5,
	KEY_NUM_6,
	KEY_NUM_7,
	KEY_NUM_8,
	KEY_NUM_9,
	KEY_NUM_A,
	KEY_NUM_B,
	KEY_NUM_C,
	KEY_NUM_D,
	KEY_NUM_E,
	KEY_NUM_F
}KEY_NUM_Type;


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

const uint8_t SegmentValue[] = {
	0b00000001,
	0b00000010,
	0b00000100,
	0b00001000,
	0b00010000,
	0b00100000,
	0b01000000,
	0b10000000,
	0b00000000
	};


const uint8_t KeyCodes[] = {		// Inverted values of the binary key codes
	0b11110111,		// K1 SG1		// ~(0x08)
	0b11110110,		// K1 SG2		// ~(0x09)
	0b11110101,		// K1 SG3		// ~(0x0A)
	0b11110100,		// K1 SG4		// ~(0x0B)
	0b11110011,		// K1 SG5		// ~(0x0C)
	0b11110010,		// K1 SG6		// ~(0x0D)
	0b11110001,		// K1 SG7		// ~(0x0E)
	0b11110000,		// K1 SG8		// ~(0x0F)
	0b11101111,		// K2 SG1		// ~(0x10)
	0b11101110,     // K2 SG2		// ~(0x11)
    0b11101101,     // K2 SG3		// ~(0x12)
    0b11101100,     // K2 SG4		// ~(0x13)
    0b11101011,     // K2 SG5		// ~(0x14)
    0b11101010,     // K2 SG6		// ~(0x15)

	};
#else
extern const uint8_t DigitToSegment[];
extern const uint8_t SegmentValue[];
extern const uint8_t KeyCodes[];
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
Status_Type TM1637_WrString(uint8_t Pos, char* pBuf, uint8_t strlen, uint8_t* pDigitsWritten);
Status_Type TM1637_GetKey(uint8_t *pKey);
/*
 * @}
 */


#endif


/* ~~~~~ END OF FILE ~~~~~ */

