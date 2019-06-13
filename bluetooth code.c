/*
 * bluetooth code.c
 *
 * Created: 13-06-2019 11:20:58 AM
 * Author : JAYASURYA
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include<avr/io.h>
#include<inttypes.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define LED PORTB
char buffer[10];
void USARTInit(uint16_t ubrr_value)
{
	//set baudrate
	UBRRL=ubrr_value;
	UBRRH=(ubrr_value>>8);
	UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	//enable the receiver and transmitter
	UCSRB=(1<<RXEN)|(1<<TXEN);
}
char USARTReadChar()
{
	//wait until a data is available
	while(!(UCSRA & (1<<RXC)))
	{
		//do nothing
	}
	return UDR;
}
void USARTWriteChar(char data)
{
	while(!(UCSRA & (1<<UDRE)))
	{
		//do nothing
	}
	UDR=data;
}
int main()
{
	USARTInit(77);
	DDRB=0xff;//PORTB as output
	char data;
	LED = 0;
	while(1)
	{
		data=USARTReadChar();
		if(data=='1')
		{
			LED|=0xff;    /*turn on led*/
			//USART_sendstring("LED_on");/*send status of led*/
		}
		else if(data=='2')
		{
			
			LED=0x00;/*turn off led*/
		}
	}
	return 0;
}
		
