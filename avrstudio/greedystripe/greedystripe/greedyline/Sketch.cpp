/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */

#include <Wire.h>
//Beginning of Auto generated function prototypes by Atmel Studio
void requestEvent();
//End of Auto generated function prototypes by Atmel Studio

#define STRIPE_ADDRESS 0x10

#define SENSOR01	(PINC & (1 << PINC0))
#define SENSOR02	(PINC & (1 << PINC1))
#define SENSOR03	(PINC & (1 << PINC2))
#define SENSOR04	(PINC & (1 << PINC3))
//adc6
#define SENSOR05	(PINE & (1 << PINE2))
//adc7
#define SENSOR06	(PINE & (1 << PINE3))
#define SENSOR07	(PIND & (1 << PIND0))
#define SENSOR08	(PIND & (1 << PIND1))
#define SENSOR09	(PIND & (1 << PIND2))
#define SENSOR10	(PIND & (1 << PIND3))
#define SENSOR11	(PIND & (1 << PIND4))
#define SENSOR12	(PIND & (1 << PIND5))
#define SENSOR13	(PIND & (1 << PIND6))
#define SENSOR14	(PIND & (1 << PIND7))
#define SENSOR15	(PINB & (1 << PINB0))
#define SENSOR16	(PINB & (1 << PINB1))



void setup() {
	DDRB = 0x00;
	PORTB = 0x00;
	DDRC = 0x00;
	PORTC = 0x00;
	DDRD = 0x00;
	PORTD = 0x00;
	DDRE = 0x00;
	PORTE = 0x00;
	
	Wire.begin(STRIPE_ADDRESS);                // join i2c bus 
	Wire.onRequest(requestEvent); // register event

	
}

void loop() {
	delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
	uint8_t response[2];
	response[0] = SENSOR01 << 0 | SENSOR02 << 1 | SENSOR03 << 2 | SENSOR04 << 3 | SENSOR05 << 4 | SENSOR06 << 5 | SENSOR07 << 6 | SENSOR08 << 7;
	response[1] = SENSOR09 << 0 | SENSOR10 << 1 | SENSOR11 << 2 | SENSOR12 << 3 | SENSOR13 << 4 | SENSOR14 << 5 | SENSOR15 << 6 | SENSOR16 << 7;
	Wire.write(response, 2); // respond with message of 6 bytes
	// as expected by master
}
