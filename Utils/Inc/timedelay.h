/**************************************** MAD Engineers ****************************************

  MAD Engineers
  Copyright (c) 2014

Description	: 

Revision History **************************************************************************
** Date ** ** Coder ** ***** Remarks ******************************************************
* DDMMYY * ** madD7 ** * Originator                                                       *

*/



#ifndef		__TIMEDELAY_H_     //Replace filename
#define		__TIMEDELAY_H_     //Replace filename



/* Include Files **************************************************************************
 * @{
 */

/*
 * @}
 */


/* Data Types & Variables *****************************************************************
 * @{
 */

// Fine tuned for stm8 operating @ 16MHz
#define  DELAY_MUL		569


#define MICROS_IN_MILLI		(1000)
#define MILLIS_IN_SEC		(1000)
#define MICROS_IN_SEC		(MICROS_IN_MILLI * MILLIS_IN_SEC)
#define SECS_IN_MINUTES		(60)
#define MINS_IN_HOUR		(60)
#define HOURS_IN_DAY		(24)

/*
 * @}
 */



/* Functions ******************************************************************************
 * @{
 */

void _ms_delay(unsigned int delay);
void _us_delay(unsigned int delay);

/*
 * @}
 */


#endif


/* ~~~~~ END OF FILE ~~~~~ */

