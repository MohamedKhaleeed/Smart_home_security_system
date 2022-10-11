#include "types_macros.h"
#include "avr/io.h"	/* to use Timers Registers */
#include <util/delay.h>

#ifndef UART_H_
#define UART_H_


void UART_init(uint32 baud_rate);

void UART_sendByte(const uint8 data);

uint8 UART_recieveByte(void);
void UART_SendString(char *str);
void UART_TxChar(char ch);

#endif /* UART_H_ */
