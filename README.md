# LinearLed
A library to get one or several LEDs to dim linear and smooth on your Arduino

## Introduction
You may have noticed that a LED appears to be non-linear when you fade it using analogWrite. The brightness increases quickly for small PWM  values but level out and increases more slowly for bigger values. This phenomenon is caused by our eyes and can be annoying if you want to dim your LED with e.g. a potentiometer or if you just want to fade a LED strip as a nice lighting effect. This library is an attempt to solve this issue by specifying a gamma corrected brightness percentage instead of a duty cycle value. This library have also the ability to set the most common Arduino processors to use 10 bit resolution instead of the standard 8 bit, which yields an even smoother fade.

## Usage
The library is simple to use. First you need to declare an object like:
```C++
linearLed myLed(pinNumber);
```
The variable pinNumber should be the number of the PWM enabled pin that you want to use. To set a brightness value, you simply use
```C++
myLed.setLedVal(brightness);
```
where brightness is a value between 0 and 100.

You can of course have several instances of the library as
```C++
linearLed myOtherLed(anotherPinNumber);
```
and so on.

### Using 10 bit mode
To set your Arduino to use a 10 bit resolution for a smoother fade, use
```C++
myLed.use10bitMode();
```
There are however some difficulties that you need to be aware of. First of all, not all processors are supported. Current supported processors are ATmega168, ATmega168P, ATmega328P, ATmega1280 and ATmega2560, which includes the most common Arduino versions like Uno, Nano, Mini and Mega as well as some legacy versions. Check the documentation of your board to see what processor you have.

Only certain PWM pins have the ability to use the 10 bit resolution. For 168/328 based Arduinos, the only available pins are 9 and 10 (Timer 1). For the Mega versions these are

|Pin number | Timer |
|-----------|-------|
| 2, 3, 5   |   3   |
| 6, 7, 8   |   4   |
| 11, 12, 13|   1   |
|44, 45, 46 |   5   |

If you try to use the 10 bit mode on an unsupported device or pin, the library will automatically fall back to the regular 8 bit mode.

This library are fiddling with some register settings to enable the 10 bit resolution, which alters the behavior of the underlying timer. The most important part with this is that all pins that uses the very same timer (listed above) will all be set to 10 bit and get a changed PWM frequency. So if you have a LED connected pin number 9 on your Arduino Uno and tries to use the 10 bit mode, pin number 10 will also be set to 10 bit even though you only use pin 9!

Any pins connected to the same timer should therefore only be used for this LED controlling purpose if the pin is used as an analog output. So if you dim a LED with 10 bit resolution on pin 9 on your Uno, do not try to control another led without setting .use10bitMode(), nor try to control a servo, nor try to use analogWrite on pin number 10. Doing so will make your Arduino behave unexpectedly. However, you can in that case use pin 10 for both digital input and output, as only the analog output is affected.

### Get the current value
You may want to get the actual PWM value that is applied to a pin at a certain brightness percentage. You can do this by
```C++
myLed.getCurrRealVal()
```
