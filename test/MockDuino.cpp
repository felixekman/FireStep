#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "FireUtils.hpp"
#include "Arduino.h"
#include "Thread.h"

SerialType Serial;
ArduinoType arduino;


ArduinoType::ArduinoType() {
	clear();
}

void ArduinoType::clear() {
	int novalue = 0xfe;
	Serial.output();	// discard
	for (int i=0; i<ARDUINO_PINS; i++) {
		pin[i] = NOVALUE;
		pinMode[i] = NOVALUE;
	}
	for (int i=0; i<ARDUINO_MEM; i++) {
		mem[i] = NOVALUE;
	}
	memset(pinPulses, 0, sizeof(pinPulses));
	ADCSRA = 0;	// ADC control and status register A (disabled)
	TCNT1 = 0; 	// Timer/Counter1
	CLKPR = 0;	// Clock prescale register
}

void ArduinoType::dump() {
	for (int i=0; i<ARDUINO_MEM; i+=16) {
		int dead = true;
		for (int j=0; j<16; j++) {
			if (mem[i+j] != NOVALUE) {
				dead = false;
				break;
			}
		}
		if (!dead) {
			cout << "MEM" << setfill('0') << setw(3) << i << "\t: ";
			for (int j=0; j<16; j++) {
				cout << setfill('0') << setw(4) << std::hex << mem[i+j] << " ";
				if (j % 4 == 3) {
					cout << "| ";
				}
			}
			cout << endl;
		}
	}
}

void ArduinoType::timer1(int increment) {
	if (TIMER_ENABLED) {
		TCNT1 += increment;
	}
}

void ArduinoType::delay500ns() {
}

void digitalWrite(int pin, int value) {
	ASSERT(0 <= pin && pin < ARDUINO_PINS);
	if (arduino.pin[pin] != value) {
		if (value == 0) {
			arduino.pinPulses[pin]++;
		}
		arduino.pin[pin] = value ? HIGH : LOW;
	}
}

int digitalRead(int pin) {
	ASSERT(0 <= pin && pin < ARDUINO_PINS);
	return arduino.pin[pin];
}

void pinMode(int pin, int inout) {
	arduino.pinMode[pin] = inout;
}

void delay(int ms) {
	arduino.timer1(MS_TIMER_CYCLES(ms));
}
