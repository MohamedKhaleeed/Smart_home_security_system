#include "motor.h"
#include <avr/io.h>
#include "types_macros.h"
#include "PWM.h"
void Dc_voidInit(void)
{
	SET_BIT(DDRA,6);
	SET_BIT(DDRA,7);
	CLEAR_BIT(PORTA,6);
	CLEAR_BIT(PORTA,7);
}
void Rotate(States state,uint8 speed)
{
	Timer0_PWM_Init(speed);

	switch(state)
	{
	case CW  : 	SET_BIT(PORTA,6); CLEAR_BIT(PORTA,7); break;
    case CCW : CLEAR_BIT(PORTA,6); SET_BIT(PORTA,7); break;
	case OFF : CLEAR_BIT(PORTA,6); CLEAR_BIT(PORTA,7); break;
	}
}
