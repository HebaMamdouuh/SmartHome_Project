/********************************************************/
/********************************************************/
/*************** Author: Adel Hani	  *******************/
/*************** Layer: HAL			  *******************/
/*************** SWC: LED			  *******************/
/*************** Date: 2/2/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/


#include "BIT_Math.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "Led_interface.h"



/*****************************************************************/
/******************* Public Function for Pin LED *****************/
/*****************************************************************/

void LED_voidPinInit(void) {
	DIO_SetPin_Direction(LedOfBuzzer_PORT,LedOfBuzzer_PIN,PIN_OUTPUT); // Set LedOfBuzzer pin as output
	DIO_SetPin_Direction(HomeLed_PORT,HomeLed_PIN,PIN_OUTPUT); // Set LedOfHome pin as output
	DIO_SetPin_Direction(DoorLed_PORT,DoorLed_PIN,PIN_OUTPUT); // Set LedOfDoor pin as output
}

void LED_voidPinTurnOn(u8 LedPin) {
	if(LedPin == LedOfBuzzer_PIN)
	{
    	DIO_SetPinValue(LedOfBuzzer_PORT,LedOfBuzzer_PIN,PIN_HIGH); // Turn LedOfBuzzer on
	}
	else if(LedPin == HomeLed_PIN)
	{
    	DIO_SetPinValue(HomeLed_PORT,HomeLed_PIN,PIN_HIGH); // Turn LedOfHome on
	}
	else if(LedPin == DoorLed_PIN)
	{
    	DIO_SetPinValue(DoorLed_PORT,DoorLed_PIN,PIN_HIGH); // Turn LedOfDoor on
	}
}

void LED_voidPinTurnOff(u8 LedPin) {
	if(LedPin == LedOfBuzzer_PIN)
	{
    	DIO_SetPinValue(LedOfBuzzer_PORT,LedOfBuzzer_PIN,PIN_LOW); // Turn LedOfBuzzer off
	}
	else if(LedPin == HomeLed_PIN)
	{
    	DIO_SetPinValue(HomeLed_PORT,HomeLed_PIN,PIN_LOW); // Turn LedOfHome off
	}
	else if(LedPin == DoorLed_PIN)
	{
    	DIO_SetPinValue(DoorLed_PORT,DoorLed_PIN,PIN_LOW); // Turn LedOfDoor off
	}
}
