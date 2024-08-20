/*
 * main.c
 *
 *  Created on: 18 Aug 2024
 *      Author: User
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "Keypad_interface.h"
#include "House_System.h"
#include "CLCD_config.h"
#include "Keypad_config.h"

#include <util/delay.h> /* for delays */
#include <string.h>     /* For the strcmp function */

void main()
{
	DIO_SetPort_Direction(CLCD_CONTROL_PORT,PORT_OUTPUT);
	DIO_SetPort_Direction(CLCD_DATA_PORT,PORT_OUTPUT);
	DIO_SetPort_Direction(KPD_PORT,PORT_OUTPUT);

	/* initialize all components */
	House_init();

	/* Initialise Users */
	init_voidUsers();

	/* Display the "House System" message */
	CLCD_voidSendString("House System");
	_delay_ms(1000);
	CLCD_clear();


	while(1)
	{
		/* call the system */
		houseSystem();

	}
}
