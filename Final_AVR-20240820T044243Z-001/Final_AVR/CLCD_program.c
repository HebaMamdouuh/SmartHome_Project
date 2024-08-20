/*
 * CLCD_interface.c
 *
 *      Author  : Jimmy
        SWC     : CLCD
        Version : 01
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include <util/delay.h>

 void CLCD_voidSendCommand(u8 Copy_u8Command)
 {
	 /* Set RS For Command */

	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,PIN_LOW);

	 /* Set R/W TO write */

	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,PIN_LOW);

	 /* Send Command */

	 DIO_SetPort_value(CLCD_DATA_PORT,Copy_u8Command) ;

	 /* Enable Pulse */

	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,PIN_HIGH);

	 _delay_ms(2);

	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,PIN_LOW);
 
 }
 
 void CLCD_voidSendData(u8 Copy_u8Data)
  {
 	 /* Set RS For Command */

 	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,PIN_HIGH);

 	 /* Set R/W TO write */

 	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,PIN_LOW);

 	 /* Send Command */

 	 DIO_SetPort_value(CLCD_DATA_PORT,Copy_u8Data) ;

 	 /* Enable Pulse */

 	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,PIN_HIGH);

 	 _delay_ms(2);

 	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,PIN_LOW);

  }

 void CLCD_voidINIT(void)
 {
	 /* wait 50 ms */

	 _delay_ms(50);

	 /* Set Function Set */
	 CLCD_voidSendCommand(Function_Set);
	 _delay_ms(1);
	 /* Display ON/OFF Control - no cursor - no blink */
	 CLCD_voidSendCommand(Display_Control);
	 _delay_ms(1);
	 /* Display Clear */

	 CLCD_voidSendCommand(Display_Clear);
	 _delay_ms(1);
 }
 void CLCD_voidSendString(u8 * Copy_u8String)
 {
	 u8 Local_u8Counter = 0 ;

	while(Copy_u8String[Local_u8Counter] != '\0')
	{
		CLCD_voidSendData(Copy_u8String[Local_u8Counter]);
		Local_u8Counter++ ;
	}

 }

 void CLCD_voidGOTOXY(u8 Copy_u8row , u8 Copy_u8col)
 {
	 u8 Local_u8Address = 0xff;

	 if(Copy_u8row>1)
	 	 {
		 	 Copy_u8row=1;
	 	 }

	 Local_u8Address = 128 + (64 * Copy_u8row) + Copy_u8col  ;
	 CLCD_voidSendCommand(Local_u8Address);
 }


 void CLCD_voidWriteNumber(u32 Copy_u32Number , u8 Copy_u8X , u8 Copy_u8Y ){

 	u8 Local_u8Digits = 0 ;
 	u32  Local_u32TempNumber = Copy_u32Number ;

 	if(Copy_u32Number == 0 ){
 		CLCD_voidGOTOXY(Copy_u8X,Copy_u8Y);
 		CLCD_voidSendData('0');
 	}else {

 	while(Local_u32TempNumber != 0){
 		Local_u32TempNumber /= 10 ;
 		Local_u8Digits++ ;
 	}

 	for(Local_u8Digits ; Local_u8Digits > 0 ; Local_u8Digits-- ){

 		CLCD_voidGOTOXY(Copy_u8X, Copy_u8Y + Local_u8Digits - 1 );

 		switch(Copy_u32Number % 10){
 		case 0 : CLCD_voidSendData('0'); break ;
 		case 1 : CLCD_voidSendData('1'); break ;
 		case 2 : CLCD_voidSendData('2'); break ;
 		case 3 : CLCD_voidSendData('3'); break ;
 		case 4 : CLCD_voidSendData('4'); break ;
 		case 5 : CLCD_voidSendData('5'); break ;
 		case 6 : CLCD_voidSendData('6'); break ;
 		case 7 : CLCD_voidSendData('7'); break ;
 		case 8 : CLCD_voidSendData('8'); break ;
 		case 9 : CLCD_voidSendData('9'); break ;
 		}
 		Copy_u32Number /= 10 ;
 	}
 	}
 }


 void CLCD_clear(void)
 {
	 CLCD_voidSendCommand(Display_Clear);
 }
