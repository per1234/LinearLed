/*
 Name:		LinearLedLib.cpp
 Created:	8/31/2016 12:29:31 AM
 Author:	Mattias Alnervik
 Editor:	http://www.visualmicro.com
*/

/*
TODO: Test Arduino MEGA
*/

#include "LinearLedLib.h"
const PROGMEM uint16_t corrValues10bit[] = { 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9, 10, 11, 12, 13, 13, 14, 16, 17, 18, 19, 21, 22, 23, 25, 27, 28, 30, 32, 34, 37, 39, 41, 44, 47, 50, 53, 56, 60, 64, 67, 72, 76, 80, 86, 91, 96, 102, 108, 115, 121, 129, 137, 145, 153, 163, 172, 183, 193, 205, 217, 230, 244, 258, 273, 290, 307, 325, 344, 364, 386, 409, 433, 458, 485, 513, 543, 576, 609, 645, 683, 723, 765, 810, 858, 908, 961, 1009, 1023};
const PROGMEM uint8_t corrValues8bit[] = { 0,1,1,1,1,2,2,2,2,3,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,11,12,13,14,15,16,17,18,19,20,21,23,24,25,27,28,30,31,32,34,36,37,39,41,42,44,46,48,50,52,53,55,58,60,62,64,66,69,71,74,76,79,81,84,87,90,93,96,99,103,106,110,114,118,122,126,130,134,139,144,149,154,160,165,171,177,184,191,198,205,212,220,228,237,246,255};

linearLed::linearLed(int pin)
{
	_pin = pin;
	_timer = digitalPinToTimer(pin);
	_inVal = 0;
}

void linearLed::setLedVal(int percentValue)
{
	pinMode(_pin, OUTPUT);
	_inVal = constrain(percentValue,0,100);
	if (_use10bit) {
		switch (_timer)
		{
		#if defined(__AVR_ATmega168__) ||defined(__AVR_ATmega168P__) ||defined(__AVR_ATmega328P__)
		case TIMER1A: //Pin 9
			TCCR1A = TCCR1A & 0x3C | (1 << WGM10) | (1 << WGM11) | (1 << COM1A1); //Set mode 3 (10 bit), p 136 ATmega datasheet
			TCCR1B = TCCR1B & 0xF8 | ((1 << CS11) | (0 << CS10)); //Set prescaler to 8
			OCR1A = pgm_read_word_near(corrValues10bit + _inVal); //Load value from FLASH, set output pin
			break;
		case TIMER1B: //Pin 10
			TCCR1A = TCCR1A & 0xCC | (1 << WGM10) | (1 << WGM11) | (1 << COM1B1);
			TCCR1B = TCCR1B & 0xF8 | ((1 << CS11) | (0 << CS10));
			OCR1B = pgm_read_word_near(corrValues10bit + _inVal);
			break;
		#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
		case TIMER1A: //Pin 11
			TCCR1A = TCCR1A & 0x3C | (1 << WGM10) | (1 << WGM11) | (1 << COM1A1); //Set registers to 1, set mode 3, sid 136 ATmega datasheet
			TCCR1B = TCCR1B & 0xF8 | ((1 << CS11) | (0 << CS10));
			OCR1A = pgm_read_word_near(corrValues10bit + _inVal);
			break;
		case TIMER1B: //Pin 12
			TCCR1A = TCCR1A & 0xCC | (1 << WGM10) | (1 << WGM11) | (1 << COM1B1);
			TCCR1B = TCCR1B & 0xF8 | ((1 << CS11) | (0 << CS10));
			OCR1B = pgm_read_word_near(corrValues10bit + _inVal);
			break;
		case TIMER1C: //Pin 13
			TCCR1A = TCCR1A & 0xF0 | (1 << WGM10) | (1 << WGM11) | (1 << COM1C1);
			TCCR1B = TCCR1B & 0xF8 | ((1 << CS11) | (0 << CS10));
			OCR1C = pgm_read_word_near(corrValues10bit + _inVal);
			break;
		
		case TIMER3A: //Pin 5
			TCCR3A = TCCR3A & 0x3C | (1 << WGM30) | (1 << WGM31) | (1 << COM3A1);
			TCCR3B = TCCR3B & 0xF8 | ((1 << CS31) | (0 << CS30));
			OCR3A = pgm_read_word_near(corrValues10bit + _inVal);
			break;
		case TIMER3B: //Pin 2
			TCCR3A = TCCR3A & 0xCC | (1 << WGM30) | (1 << WGM31) | (1 << COM3B1);
			TCCR3B = TCCR3B & 0xF8 | ((1 << CS31) | (0 << CS30));
			OCR3B = pgm_read_word_near(corrValues10bit + _inVal);
			break;
		case TIMER3C: //Pin 3
			TCCR3A = TCCR3A & 0xF0 | (1 << WGM30) | (1 << WGM31) | (1 << COM3C1);
			TCCR3B = TCCR3B & 0xF8 | ((1 << CS31) | (0 << CS30));
			OCR3C = pgm_read_word_near(corrValues10bit + _inVal);
			break;

		case TIMER4A: //Pin 6
			TCCR4A = TCCR4A & 0x3C | (1 << WGM40) | (1 << WGM41) | (1 << COM4A1);
			TCCR4B = TCCR4B & 0xF8 | ((1 << CS41) | (0 << CS40));
			OCR4A = pgm_read_word_near(corrValues10bit + _inVal);
			break;
		case TIMER4B: //Pin 7
			TCCR4A = TCCR4A & 0xCC | (1 << WGM40) | (1 << WGM41) | (1 << COM4B1);
			TCCR4B = TCCR4B & 0xF8 | ((1 << CS41) | (0 << CS40));
			OCR4B = pgm_read_word_near(corrValues10bit + _inVal);
			break;
		case TIMER4C: //Pin 8
			TCCR4A = TCCR4A & 0xF0 | (1 << WGM40) | (1 << WGM41) | (1 << COM4C1);
			TCCR4B = TCCR4B & 0xF8 | ((1 << CS41) | (0 << CS40));
			OCR4C = pgm_read_word_near(corrValues10bit + _inVal);
			break;

		case TIMER5A: //Pin 46
			TCCR5A = TCCR5A & 0x3C | (1 << WGM50) | (1 << WGM51) | (1 << COM5A1);
			TCCR5B = TCCR5B & 0xF8 | ((1 << CS51) | (0 << CS50));
			OCR5A = pgm_read_word_near(corrValues10bit + _inVal);
			break;
		case TIMER5B: //Pin 45
			TCCR5A = TCCR5A & 0xCC | (1 << WGM50) | (1 << WGM51) | (1 << COM5B1);
			TCCR5B = TCCR5B & 0xF8 | ((1 << CS51) | (0 << CS50));
			OCR5B = pgm_read_word_near(corrValues10bit + _inVal);
			break;
		case TIMER5C: //Pin 44
			TCCR5A = TCCR5A & 0xF0 | (1 << WGM50) | (1 << WGM51) | (1 << COM5C1);
			TCCR5B = TCCR5B & 0xF8 | ((1 << CS51) | (0 << CS50));
			OCR5C = pgm_read_word_near(corrValues10bit + _inVal);
			break;

		#endif
		default:
			_use10bit = false;
			break;
		}
	}
	if (!_use10bit) {
		analogWrite(_pin, pgm_read_byte_near(corrValues8bit + _inVal));
	}
}

void linearLed::use10bitMode()
{
	#if defined(__AVR_ATmega168__) ||defined(__AVR_ATmega168P__) ||defined(__AVR_ATmega328P__) ||defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	_use10bit = true;
	#endif
}

int linearLed::getCurrRealVal()
{
	if (_use10bit) {
		return pgm_read_word_near(corrValues10bit + _inVal);
	}
	else {
		return pgm_read_byte_near(corrValues8bit + _inVal);
	}
}
