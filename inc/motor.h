#ifndef MOTOR_H_
#define MOTOR_H_
#include "types_macros.h"
#define DC_MOTOR_PORT1 PORTB
#define DC_MOTOR_PORT2 PORTB

#define DC_MOTOR_PIN0   0
#define DC_MOTOR_PIN1   1


typedef enum{
	CW ,CCW,OFF

}States;
void Dc_voidInit();

void Rotate(States state,uint8 speed);

#endif /* MOTOR_H_ */
