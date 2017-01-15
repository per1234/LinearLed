/*
 Name:		LinearLedLib.h
 Created:	8/31/2016 12:29:31 AM
 Author:	Mattias Alnervik
 Editor:	http://www.visualmicro.com
*/

#include <avr/pgmspace.h>
#ifndef _LinearLedLib_h
#define _LinearLedLib_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class linearLed {
public:
	linearLed(int pin);
	void setLedVal(int val);
	void use10bitMode();
	int getCurrRealVal();
private:
	int _timer;
	int _pin;
	int _inVal;
	bool _use10bit;
};

#endif

