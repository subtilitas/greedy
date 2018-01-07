#include <util/twi.h>
#include <avr/interrupt.h>

#include "I2C_slave.h"

static void (*I2C_recv)(uint8_t);
static void (*I2C_req)();

void I2C_setCallbacks(void (*recv)(uint8_t), void (*req)())
{
	I2C_recv = recv;
	I2C_req = req;
}

void I2C_init(uint8_t address)
{
	cli();
	// load address into TWI address register
	TWAR0 = address << 1;
	// set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
	TWCR0 = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
	sei();
}

void I2C_stop(void)
{
	// clear acknowledge and enable bits
	cli();
	TWCR0 = 0;
	TWAR0 = 0;
	sei();
}

ISR(TWI0_vect)
{
	switch((TWSR0 & TW_STATUS_MASK))
	{
		case TW_SR_DATA_ACK:
		// received data from master, call the receive callback
		I2C_recv(TWDR0);
		TWCR0 = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		case TW_ST_SLA_ACK:
		// master is requesting data, call the request callback
		I2C_req();
		TWCR0 = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		case TW_ST_DATA_ACK:
		// master is requesting data, call the request callback
		I2C_req();
		TWCR0 = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		case TW_BUS_ERROR:
		// some sort of erroneous state, prepare TWI to be readdressed
		TWCR0 = 0;
		TWCR0 = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
		default:
		TWCR0 = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
		break;
	}
}