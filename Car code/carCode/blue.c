#define F_CPU 16000000UL
#include <avr/io.h>
#include <inttypes.h>
#define USART_BAUDRATE 9600
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) 

//initialization of USART

void UART_init(long USART_BAUDRATE)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);	// Turn on transmission and reception 
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);// Use 8-bit char size 
	UBRRL = BAUD_PRESCALE;			// Load lower 8-bits of the baud rate 
	UBRRH = (BAUD_PRESCALE >> 8);		// Load upper 8-bits
}

//Receiving Character
unsigned char USART_RxChar()

{

while ((UCSRB & (1 << RXC)) == 0) //Wait till data is received

return UDR; 
}

void USARTWriteChar(char data)
{
while(!(UCSRA & (1<<UDRE)))
{

}
UDR=data;
} 
int main()
{
USART_init(9600); //PD3 pin5

DDRB=0b11111111;//Motor at PORTB
char data;
while(1)
{
data=UART_RxChar();
switch(data)
{
case ('F') :PORTB=0b00001010; //Forward
break;

case ('L') :PORTB=0b00001001; //Left
break;

case ('R'):PORTB=0b00000110; //Right
break;

case ('B'):PORTB=0b00000101; //Back
break;

case ('S'):PORTB=0b00001111; //Stop
break;
}
}
return 0;
}
