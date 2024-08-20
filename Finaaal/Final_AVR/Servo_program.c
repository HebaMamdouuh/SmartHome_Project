
#include "BIT_Math.h"
#include "STD_TYPES.h"
#include "Mapping_interface.h"
#include "Servo_interface.h"
#include "DIO_interface.h"
#include "TIMER1_interface.h"
#include "TIMER_interface.h"
#include "TIMER_config.h"
#include "TIMER_private.h"

void SERVO_voidInit(u8 Copy_u8IDPin)
{
	GIE_voidEnable();

	Timer0_voidInit();
	Timer0_voidInterruptEnable();
	Timer0_voidSetPrescalerValue(PRESCALER_init);


	TIM1_voidInit();
	TIM1_voidEnable(PRESCALER_init);
	TIM1_voidSetIcuRegValue(20000);


	if (Copy_u8IDPin == SERVO_OC1B_PIN4)
	{
		DIO_SetPin_Direction(SERVO_PORTD, SERVO_OC1B_PIN4, SERVO_OUTPUT);
	}

	else if (Copy_u8IDPin == SERVO_OC1A_PIN5)
	{
		DIO_SetPin_Direction(SERVO_PORTD, SERVO_OC1A_PIN5, SERVO_OUTPUT);
	}
}



void SERVO_voidSetDegreeRotate(u8 Copy_u8IDPin ,u8 Copy_u8AngleValue)
{

	if (Copy_u8IDPin == SERVO_OC1A_PIN5)
	{
		TIM1_voidSetCmpARegValue(MAPPING_s32GetOutput(MIN_ANGLE, MAX_ANGLE, MIN_TIME_ON, MAX_TIME_ON, Copy_u8AngleValue));
	}

	else if (Copy_u8IDPin == SERVO_OC1B_PIN4)
	{
		TIM1_voidSetCmpARegValue(MAPPING_s32GetOutput(MIN_ANGLE, MAX_ANGLE, MIN_TIME_ON, MAX_TIME_ON, Copy_u8AngleValue));
	}

}
