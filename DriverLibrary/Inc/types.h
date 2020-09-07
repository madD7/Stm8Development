/**************************************** MAD Engineers ****************************************

  MAD Engineers
  Copyright (c) 2014

Description	: 

Revision History **************************************************************************
** Date ** ** Coder ** ***** Remarks ******************************************************
* DDMMYY * ** madD7 ** * Originator                                                       *

*/


#ifndef		__TYPES_H_     //Replace filename
#define		__TYPES_H_     //Replace filename


/* Include Files **************************************************************************
 * @{
 */

/*
 * @}
 */


/* Data Types & Variables *****************************************************************
 * @{
 */

/**
 * IO definitions
 *
 * define access restrictions to peripheral registers
 */
#define     __I     			volatile const   /*!< defines 'read only' permissions     */
#define     __O     			volatile         /*!< defines 'write only' permissions    */
#define     __IO    			volatile         /*!< defines 'read / write' permissions  */


/**********************************************************************************************/
/**
 * Type definitions
 */

#ifndef __ARM_DATATTPES_
#define __ARM_DATATTPES_

typedef unsigned long int		uint32_t;
typedef long int                int32_t;

typedef unsigned int            uint16_t;
typedef int                     int16_t;

typedef unsigned char       	uint8_t;
typedef char                    int8_t;
#endif 


/**********************************************************************************************/


#define U8_MAX     				(255)
#define S8_MAX     				(127)
#define S8_MIN     				(-128)
#define U16_MAX    				(65535u)
#define S16_MAX    				(32767)
#define S16_MIN    				(-32768)
#define U32_MAX    				(4294967295uL)
#define S32_MAX    				(2147483647)
#define S32_MIN    				(-2147483648uL)


typedef enum
{
    StatusSuccess       =0,
    StatusInitFail      =1,
    StatusChkSumErr		=2,
    StatusLenMismatch	=3,
    StatusInsuffMem 	=4,
	StatusInvalParam	=5,
	StatusOutOfRange	=6,
    StatusFail          =255
}Status_Type;


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

