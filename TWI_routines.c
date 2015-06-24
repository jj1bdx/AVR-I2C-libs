#include <util/twi.h>
#include <TWI_routines.h>
//include "usart.h"

void twi_init(uint8_t twbr_value)
{
	//TWSR = 0x00;
	TWBR = twbr_value;
}

void twistart(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

void twistop(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
	while ((TWCR & (1<<TWSTO)));
}

void twiwrite(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
}

uint8_t twiread(uint16_t ack) // nack 0
{
	TWCR = ack ?
	  ((1 << TWINT) | (1 << TWEN) | (1 << TWEA))
	: ((1 << TWINT) | (1 << TWEN)) ;
	
	while (!(TWCR & (1<<TWINT)));
	return TWDR;
}

/*
void scan(void)
{
	uart_puts_P("Scanning for devices on i2c bus ...\r\n\n");
	
	for(uint8_t s = 0; s <= 0x7F; s++)
	{
		twistart();
		twiwrite(SLA_W(s));
		
		if(TW_STATUS == TW_MT_SLA_ACK )
		{
			uart_puts_P("Found device at address - 0x");
			uart_put_hex(s);
			uart_puts_P(" (<< 1) \t 0b");
			uart_putintr(s, 2);
			uart_puts_P(" 0\r\n");
			
		}
		twistop();
	}
}*/