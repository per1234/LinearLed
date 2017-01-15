/*
Name:		DemoLinearLed.ino
Author:	Mattias Alnervik
Editor:	http://www.visualmicro.com
*/


#include "LinearLedLib.h"
byte serIn;
int brightness = 0;
linearLed myLed(13); //Built in LED, without support for 10 bit mode
linearLed myOtherLed(9); //Pin with support for 10 bit mode.

void setup() {
	Serial.begin(115200); //Starts serial communication
	myOtherLed.use10bitMode(); //Sets pin 9 to use 10 bit resolution
}

void loop() {
	if (Serial.available()) {
		serIn = Serial.read(); //Read available data sent to the Arduino
		if (serIn == 43) { //If a plus-sign, +, is received
			brightness++; //Increase the brightness one step
			brightness = constrain(brightness, 0, 100); //Limits brightness to be a value between 0 and 100

			myLed.setLedVal(brightness); //Sets the new brightness value to the LEDs
			myOtherLed.setLedVal(brightness);

			Serial.println("Brightness of LED: " + brightness); //Prints the brightness to the console
			Serial.println("Actual PWM value of myLed: " + myLed.getCurrRealVal()); //The real PWM value
			Serial.println("Actual PWM value of myOtherLed: " + myOtherLed.getCurrRealVal());

		}
		else if (serIn == 45) { //If a minus-sign, -, is received
			brightness--; //Decrease the brightness one step
			brightness = constrain(brightness, 0, 100);

			myLed.setLedVal(brightness);
			myOtherLed.setLedVal(brightness);

			Serial.println("Brightness of LED: " + brightness);
			Serial.println("Actual PWM value of myLed: " + myLed.getCurrRealVal());
			Serial.println("Actual PWM value of myOtherLed: " + myOtherLed.getCurrRealVal());
		}

	}
}
