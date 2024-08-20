#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Keypad_interface.h"
#include "Keypad_config.h"


void KPD_VoidInit()
{
    // Set the pin directions for the columns as output
    DIO_SetPin_Direction(KPD_PORT, KPD_Column0, PIN_OUTPUT);
    DIO_SetPin_Direction(KPD_PORT, KPD_Column1, PIN_OUTPUT);
    DIO_SetPin_Direction(KPD_PORT, KPD_Column2, PIN_OUTPUT);
    DIO_SetPin_Direction(KPD_PORT, KPD_Column3, PIN_OUTPUT);

    // Set the pin directions for the rows as input
    DIO_SetPin_Direction(KPD_PORT, KPD_Row0, PIN_INPUT);
    DIO_SetPin_Direction(KPD_PORT, KPD_Row1, PIN_INPUT);
    DIO_SetPin_Direction(KPD_PORT, KPD_Row2, PIN_INPUT);
    DIO_SetPin_Direction(KPD_PORT, KPD_Row3, PIN_INPUT);

    // Set the initial value of the port to all high
    DIO_SetPort_value(KPD_PORT, PORT_HIGH);
}

u8 KPD_VoidGetPressedKey()
{
    u8 Key_Pressed_Value = KPD_NOT_Pressed; // if the value has not been changed from KPD_NOT_Pressed, then no key is pressed
    u8 Key_Pressed_State;                   // used in DIO_VidGetPinValue

    static u8 Column_arr[] = {KPD_Column0, KPD_Column1, KPD_Column2, KPD_Column3};
    static u8 Row_arr[] = {KPD_Row0, KPD_Row1, KPD_Row2, KPD_Row3};
    static u8 Local_Keypad_arr[KPD_Row_Number][KPD_Column_Number] = KPD_Arr;

    for (u8 Column = 0; Column < KPD_Column_Number; Column++)
    {
        // Set the current column pin to low
        DIO_SetPinValue(KPD_PORT, Column_arr[Column], PIN_LOW);

        for (u8 Row = 0; Row < KPD_Row_Number; Row++)
        {
            // Get the state of the current row pin
            DIO_VoidGetPinValue(KPD_PORT, Row_arr[Row], &Key_Pressed_State);

            if (Key_Pressed_State == PIN_LOW) // when a key is pressed it has a low value
            {
                Key_Pressed_Value = Local_Keypad_arr[Row][Column];

                // Wait until the key is released
                while (Key_Pressed_State == PIN_LOW) // polling, while the key is still pressed, don't do anything.
                {
                    DIO_VoidGetPinValue(KPD_PORT, Row_arr[Row], &Key_Pressed_State);
                }
                return Key_Pressed_Value;
            }
        }
        // Set the current column pin back to high
        DIO_SetPinValue(KPD_PORT, Column_arr[Column], PIN_HIGH);
    }

    return Key_Pressed_Value;
}
