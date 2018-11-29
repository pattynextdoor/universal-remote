#include <avr/io.h>
#include <util/delay.h>
#include "usart_ATmega1284.h"

#define GREEN (PINC & 0x04)
#define RED (PINC & 0x08)
#define FUNC_L (PINC & 0x10)
#define FUNC_M (PINC & 0x20)
#define FUNC_R (PINC & 0x40)

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRC = 0x00; PORTC = 0xFF;
	
	initUSART(0);
	
    while (1) {
		unsigned char cmd;
		
		PORTA = ~PINC;
		
		switch(PINC) {
			if (FUNC_M) {
				PORTA = 0xFF;
			}
		}
    }
}

