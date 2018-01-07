#include "I2C_slave.h"

#define I2C_ADDR 0x10

volatile uint8_t reg_address;

#define SENSOR01	(PINC & (1 << PINC0) ? 1 : 0)
#define SENSOR02	(PINC & (1 << PINC1) ? 1 : 0)
#define SENSOR03	(PINC & (1 << PINC2) ? 1 : 0)
#define SENSOR04	(PINC & (1 << PINC3) ? 1 : 0)
//adc6
#define SENSOR05	(PINE & (1 << PINE2) ? 1 : 0)
//adc7
#define SENSOR06	(PINE & (1 << PINE3) ? 1 : 0)
#define SENSOR07	(PIND & (1 << PIND0) ? 1 : 0)
#define SENSOR08	(PIND & (1 << PIND1) ? 1 : 0)
#define SENSOR09	(PIND & (1 << PIND2) ? 1 : 0)
#define SENSOR10	(PIND & (1 << PIND3) ? 1 : 0)
#define SENSOR11	(PIND & (1 << PIND4) ? 1 : 0)
#define SENSOR12	(PIND & (1 << PIND5) ? 1 : 0)
#define SENSOR13	(PIND & (1 << PIND6) ? 1 : 0)
#define SENSOR14	(PIND & (1 << PIND7) ? 1 : 0)
#define SENSOR15	(PINB & (1 << PINB0) ? 1 : 0)
#define SENSOR16	(PINB & (1 << PINB1) ? 1 : 0)


void I2C_received(uint8_t received_data)
{
	if(received_data == 0xF1){
		reg_address = 0x01;
	}

    if(received_data == 0xF0){
	    reg_address = 0x00;
    }
}

void I2C_requested()

{
	uint8_t response[4];
	static uint8_t loop = 0;
	response[0] = SENSOR01 << 0 | SENSOR02 << 1 | SENSOR03 << 2 | SENSOR04 << 3 | 1 << 4;
	response[1] = SENSOR05 << 0 | SENSOR06 << 1 | SENSOR07 << 2 | SENSOR08 << 3 | 1 << 5;
	response[2] = SENSOR09 << 0 | SENSOR10 << 1 | SENSOR11 << 2 | SENSOR12 << 3 | 1 << 6;
	response[3] = SENSOR13 << 0 | SENSOR14 << 1 | SENSOR15 << 2 | SENSOR16 << 3 | 1 << 7;

	I2C_transmitByte(response[loop++ % 4]);
}

void setup()
{
		DDRB = 0x00;
		PORTB = 0x00;
		DDRC = 0x00;
		PORTC = 0x00;
		DDRD = 0x00;
		PORTD = 0x00;
		DDRE = 0x00;
		PORTE = 0x00;
		

	// set received/requested callbacks
	I2C_setCallbacks(I2C_received, I2C_requested);

	// init I2C
	I2C_init(I2C_ADDR);
}

int main()
{
	setup();

	// Main program loop
	while(1);
}