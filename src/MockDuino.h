#ifndef MOCKDUINO_H
#define MOCKDUINO_H

#include <string>
#include <sstream>
#include <stdint.h>
#include "../ArduinoJson/include/ArduinoJson/Arduino/Print.hpp"
#include "fireduino_types.h"

namespace mockduino { // fireduino implementation
	int16_t	digitalRead(int16_t pin);
	void digitalWrite(int16_t dirPin, int16_t value);
	int16_t analogRead(int16_t pin);
	void analogWrite(int16_t pin, int16_t value);
	void pinMode(int16_t pin, int16_t inout);
	void delay(int ms);
	void delayMicroseconds(uint16_t usDelay);
	uint8_t eeprom_read_byte(uint8_t *addr);
	void eeprom_write_byte(uint8_t *addr, uint8_t value);
	Print& get_Print();
	uint8_t serial_read();
	int16_t serial_available();
	void serial_begin(int32_t baud);
	void serial_print(const char *value);
	void serial_print(const char value);
	void serial_print(int16_t value, int16_t format = DEC);
}

typedef class MockSerial : public Print {
	private:
		std::string serialout;
		std::string serialline;

	public:
		void clear();
		void push(uint8_t value);
		void push(int16_t value);
		void push(int32_t value);
		void push(float value);
		void push(std::string value);
		void push(const char * value);
		std::string output();

	public:
		int available();
		void begin(long speed) ;
		uint8_t read() ;
		virtual size_t write(uint8_t value);
		void print(const char value);
		void print(const char *value);
		void print(int value, int format = DEC);
} MockSerial;
extern MockSerial mockSerial;

#define MOCKDUINO_PINS 127
#define MOCKDUINO_MEM 1024

typedef class MockDuino {
	friend void mockduino::delayMicroseconds(uint16_t us);
	friend void mockduino::digitalWrite(int16_t pin, int16_t value);
	friend void mockduino::analogWrite(int16_t pin, int16_t value);
	friend int16_t mockduino::digitalRead(int16_t pin);
	friend int16_t mockduino::analogRead(int16_t pin);
	friend void mockduino::pinMode(int16_t pin, int16_t inout);
	private: 
		int16_t pin[MOCKDUINO_PINS];
        int16_t _pinMode[MOCKDUINO_PINS];
		int32_t pinPulses[MOCKDUINO_PINS];
        int16_t mem[MOCKDUINO_MEM];
		int32_t usDelay;
    public:

    public:
        MockDuino();
		void dump();
		int16_t& MEM(int addr);
		void clear();
		void timer1(int increment=1);
		void delay500ns();
		int16_t getPinMode(int16_t pin);
		int16_t getPin(int16_t pin);
		void setPin(int16_t pin, int16_t value);
		void setPinMode(int16_t pin, int16_t value);
		int32_t pulses(int16_t pin);
		uint32_t get_usDelay() {return usDelay;}
} MockDuino;


#endif