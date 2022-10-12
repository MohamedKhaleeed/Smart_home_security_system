#include "BLUETOOTH.h"
#include "avr/io.h" /* To use the UART Registers */
#include "types_macros.h" /* To use the macros like SET_BIT */


void UART_init(uint32 baud_rate)
{
	uint16 ubrr_value = 0;

	UCSRA = (1<<U2X);


	UCSRB = (1<<RXEN) | (1<<TXEN);


	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);

	ubrr_value = (uint16)(((F_CPU / (baud_rate * 8UL))) - 1);

	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}


void UART_sendByte(const uint8 data)
{

	while(BIT_IS_CLEAR(UCSRA,UDRE))
	{}


	UDR = data;

}


uint8 UART_recieveByte(void)
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}


    return UDR;
}

void UART_SendString(char *str)
{
	unsigned char j=0;

	while (str[j]!=0)		/* Send string till null */
	{
		UART_sendByte(str[j]);
		j++;
	}
}
void led(void)
{	    						UART_SendString("LED ");

	}
void on(void)
{	    						UART_SendString(" on \r\n  ");

	}
void off(void)
{	    						UART_SendString(" off \r\n  ");

	}
