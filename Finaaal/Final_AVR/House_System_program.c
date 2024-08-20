
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "Keypad_interface.h"
#include "Led_interface.h"
#include "Buzzer_interface.h"
#include "Servo_interface.h"
#include "House_System.h"
#include "Keypad_config.h"

#include <util/delay.h> //for delays
#include <string.h>     // For the strcmp function

// Flags
u8 pinEntered = 0, pinCorrect = 0, Door_state = 0, light_state = 0, failed_count = 0, Check = 0;

u8 enteredPin[5]; /*For Password */
u8 enteredUser = 0; /*For UserName */

void init_voidUsers(void)
{
	// Initialize users with default usernames and passwords
	strcpy(users[0].username, "ITI");
	strcpy(users[0].password, "0000");

	strcpy(users[1].username, "Heba");
	strcpy(users[1].password, "1234");

	strcpy(users[2].username, "Laila");
	strcpy(users[2].password, "5678");

	strcpy(users[3].username, "Omar");
	strcpy(users[3].password, "7777");
}

void houseSystem(void)
{

	/* Select the userName */
	CLCD_clear();
	CLCD_voidSendString("1-ITI. 2-Heba.");
	CLCD_voidGOTOXY(1,0);
	CLCD_voidSendString("3-Laila. 4-Omar.");
	_delay_ms(1000);
	do
	{
		enteredUser = KPD_VoidGetPressedKey();
	} while (enteredUser == KPD_NOT_Pressed); // Ignore KPD_NOT_Pressed


	switch (enteredUser)
	{
	case '1':
	{
		CLCD_clear();
		CLCD_voidSendString("Hello ITI.");
		Check = verify_user(users[0].password);
		if(Check)
		{
			Menu();
		}
		break;
	}
	case '2':
	{
		CLCD_clear();
		CLCD_voidSendString("Hello Heba.");
		Check = verify_user(users[1].password);
		if(Check)
		{
			Menu();
		}
		break;
	}
	case '3':
	{
		CLCD_clear();
		CLCD_voidSendString("Hello Laila.");
		Check = verify_user(users[2].password);
		if(Check)
		{
			Menu();
		}
		break;
	}
	case '4':
	{
		CLCD_clear();
		CLCD_voidSendString("Hello Omar.");
		Check = verify_user(users[3].password);
		if(Check)
		{
			Menu();
		}
		break;
	}
	default:
	{
		CLCD_clear();
		CLCD_voidSendString("Invalid Choice");
		_delay_ms(1000);
		houseSystem(); //restart the selection
		break;
	}

	}
}
void House_init()
{
	CLCD_voidINIT();
	KPD_VoidInit();
	LED_voidPinInit();
	BUZZ_voidInit();
	SERVO_voidInit(SERVO_OC1A_PIN5);

}

u8 verify_user(u8 * SavedPass)
{
	// If a PIN has not been entered, ask for the PIN


		CLCD_voidGOTOXY(1, 0);
		CLCD_voidSendString("PIN:");

		// Read the entered PIN from the user
		for (int i = 0; i < 4; i++)
		{
			u8 key = 0;

			do
			{
				key = KPD_VoidGetPressedKey();
			} while (key == KPD_NOT_Pressed); // Ignore KPD_NOT_Pressed

			enteredPin[i] = key;
			CLCD_voidSendData('*'); // Display an asterisk for each entered digit
		}

		enteredPin[4] = '\0'; // Null-terminate the string

		// Set the flag to indicate that a PIN has been entered
		pinEntered = 1;


	// Compare the entered PIN with the correct PIN
	if (strcmp(enteredPin, SavedPass) == 0 ) //|| pinCorrect == 1
	{
		pinCorrect = 1;
		LED_voidPinTurnOn(LedOfBuzzer_PIN); // logged in status
		return 1;
	}
	else
	{

		if (failed_count == Max_Trials)
		{
			// Invalid PIN, display error message and reset the flag
			CLCD_clear();
			CLCD_voidSendString("You have been");
			CLCD_voidGOTOXY(1, 0);
			CLCD_voidSendString("blocked for 10s");
			_delay_ms(10000);
			BUZZ_voidBeep();
			pinEntered = 0;
			failed_count = 0;
			houseSystem();
		}
		else
		{
			// Invalid PIN, display error message and reset the flag
			CLCD_clear();
			CLCD_voidSendString("Invalid PIN");
			_delay_ms(500);
			pinEntered = 0;
			failed_count++;
			houseSystem();
		}
		return 0;
	}
	}


void Menu(void)
{
	u8 selectedOption = 0;

	CLCD_clear();
	CLCD_voidSendString("1-Lock. 2-Light");
	CLCD_voidGOTOXY(1,0);
	CLCD_voidSendString("3-user menu");

	while (1)
	{
		do
		{
			selectedOption = KPD_VoidGetPressedKey();
		} while (selectedOption == KPD_NOT_Pressed);

		// Perform the corresponding action
		switch (selectedOption)
		{

		case '1':
			//   toggleDoorLock();
			CLCD_clear();
			if (Door_state == 0) /* Door is closed */
			{
				Door_state = 1;
				LED_voidPinTurnOn(DoorLed_PIN);
				SERVO_voidSetDegreeRotate(SERVO_OC1A_PIN5, 90);
				CLCD_voidSendString("Door opened. ");
				_delay_ms(500);
				Menu();
			}
			else
			{
				Door_state = 0;
				LED_voidPinTurnOff(DoorLed_PIN);
				SERVO_voidSetDegreeRotate(SERVO_OC1A_PIN5, -90);
				CLCD_voidSendString("Door closed. ");
				_delay_ms(500);
				Menu();
			}
			break;

		case '2':
			//  toggleRoomLights();

			CLCD_clear();

			if (light_state == 0)
			{
				light_state = 1;
				LED_voidPinTurnOn(HomeLed_PIN);
				CLCD_voidSendString("Lights ON.");
				_delay_ms(500);
				Menu();
			}
			else
			{
				light_state = 0;
				LED_voidPinTurnOff(HomeLed_PIN);
				CLCD_voidSendString("Lights OFF.");
				_delay_ms(500);
				Menu();
			}
			break;
		case '3':
			houseSystem();
			break;

		default:
		{
			CLCD_clear();
			CLCD_voidSendString("Invalid option");
			_delay_ms(500);
			CLCD_clear();
			Menu();
			break;
		}
		}
	}
}

