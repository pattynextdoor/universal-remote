#include <avr/io.h>
#include <util/delay.h>
#include "usart_ATmega1284.h"

#define GREEN (PINC & 0x04)
#define RED (PINC & 0x08)
#define FUNC_L (PINC & 0x10)
#define FUNC_M (PINC & 0x20)
#define FUNC_R (PINC & 0x40)
#define MODE (PINC & 0x80)

enum modeStates { mode_init, spotify, twilio, smart_things } modeState;

void modeTick() {
	switch(modeState) {
		case mode_init:
			modeState = spotify;
			break;
		
		case spotify:
			if (MODE) {
				modeState = twilio;
			}
			break;
		
		case twilio:
			if (MODE) {
				modeState = smart_things;
			}
			break;

		case smart_things:
			if (MODE) {
				modeState = spotify;
			}
			break;

		default:
			break;
	}
}

enum menuStates { menu_init, menu_wait, menu_btn_press, menu_btn_release } menuState;

void sendSignal() {
	unsigned char modeOffset;

	if (modeState == spotify) {
		modeOffset = 0;
	}
	else if (modeState == twilio) {
		modeOffset = 10;
	}
	else if (modeState == smart_things) {
		modeOffset = 20;
	}

	if (USART_IsSendReady(0)) {
		switch(PINC) {
			case GREEN:
				USART_Send(4 + modeOffset, 0);
				break;

			case RED:
				USART_Send(5 + modeOffset, 0);
				break;

			case FUNC_L:
				USART_Send(6 + modeOffset, 0);
				break;

			case FUNC_M:
				USART_Send(7 + modeOffset, 0);
				break;

			case FUNC_R:
				USART_Send(8 + modeOffset, 0);
				break;

			default:
				break;		
		}
	}
}

void menuTick() {
	switch(menuState) {
		case menu_init:
			menuState = menu_wait;
			break;

		case menu_wait:
			if (GREEN || RED || FUNC_L || FUNC_M || FUNC_R) {
				menuState = menu_btn_press;
			}
			break;
		
		case menu_btn_press:
			sendSignal();
			if (!(GREEN && RED && FUNC_L && FUNC_M || FUNC_R)) {
				menuState = menu_btn_release;
			}
			break;
		
		case menu_btn_release:
			menuState = menu_wait;
			break;
	}
}

int main(void)
{
	DDRA = 0xFF; PORTA = 0x00;
	DDRC = 0x00; PORTC = 0xFF;

	menuState = menu_init;

	initUSART(0);
	
  while (1) {
		menuTick();	
  }
}

