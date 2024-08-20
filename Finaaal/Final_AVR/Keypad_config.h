#ifndef KEYPAD_CONFIG_H
#define KEYPAD_CONFIG_H

#define KPD_PORT        DIO_PORTC

#define KPD_Column0        DIO_PIN0
#define KPD_Column1        DIO_PIN1
#define KPD_Column2        DIO_PIN2
#define KPD_Column3        DIO_PIN3

#define KPD_Row0           DIO_PIN4
#define KPD_Row1           DIO_PIN5
#define KPD_Row2           DIO_PIN6
#define KPD_Row3           DIO_PIN7

#define KPD_Column_Number     4
#define KPD_Row_Number        4

#define KPD_NOT_Pressed      0xff

#define KPD_Arr      /* Based on Hardware Keypad design */                                                                            \
    {                                                                                            \
        {'7', '8', '9', '/'}, {'4', '5', '6', '*'}, {'1', '2', '3', '-'}, { 'C', '0', '=', '+' } \
    }

#endif
