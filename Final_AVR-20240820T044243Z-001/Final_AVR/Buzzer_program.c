/********************************************************/
/********************************************************/
/*************** Author: Laila Raafat	  *******************/
/*************** Layer: HAL			  *******************/
/*************** SWC: Buzzer		  *******************/
/*************** Date: 11/2/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/


#include "BIT_Math.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "Buzzer_interface.h"
#include "util/delay.h"


void BUZZ_voidInit(void)
{
	DIO_SetPin_Direction(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
}


void BUZZ_voidTurnOn(void)
{
	DIO_SetPinValue(BUZZER_PORT,BUZZER_PIN,PIN_HIGH);
}


void BUZZ_voidTurnOff(void)
{
	DIO_SetPinValue(BUZZER_PORT,BUZZER_PIN,PIN_LOW);
}


void BUZZ_voidBeep(void) {
	BUZZ_voidTurnOn();
	_delay_ms(10000);
	BUZZ_voidTurnOff();
}
