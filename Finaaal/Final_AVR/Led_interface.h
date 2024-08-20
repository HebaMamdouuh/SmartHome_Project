/********************************************************/
/********************************************************/
/*************** Author: Laila Raafat	  *******************/
/*************** Layer: HAL			  *******************/
/*************** SWC: LED			  *******************/
/*************** Date: 2/2/2023 	  *******************/
/*************** Version: 1.00		  *******************/
/********************************************************/
/********************************************************/


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

/********************************************************/
/******************* Public Macros **********************/
/********************************************************/
//  LED Port Macros
#define LedOfBuzzer_PORT     DIO_PORTB
#define LedOfBuzzer_PIN      DIO_PIN5

#define HomeLed_PORT         DIO_PORTB
#define HomeLed_PIN          DIO_PIN6

#define DoorLed_PORT         DIO_PORTB
#define DoorLed_PIN          DIO_PIN7
void LED_voidPinInit(void);


void LED_voidPinTurnOn(u8 LedPin);


void LED_voidPinTurnOff(u8 LedPin);


#endif /* LED_INTERFACE_H_ */
