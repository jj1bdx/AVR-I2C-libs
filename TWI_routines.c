//**************************************************************
// ****** FUNCTIONS FOR TWI COMMUNICATION *******
//**************************************************************
//Compiler          : AVR-GCC
//Author            : jnk0le@hotmail.com
//                    https://github.com/jnk0le
//Date              : 24 June 2015
//License           : MIT
//**************************************************************

#include <util/twi.h>
#include <TWI_routines.h>
//include "usart.h"

//******************************************************************
//Function  : To initialize TWI bus.
//Arguments : 1. Calculated twbr value.
//Return    :    none
//note      : Use TWBR_CALC(speed) macro to calculate twbr value.
//******************************************************************
	void twi_init(uint8_t twbr_value)
	{
		//TWSR = 0x00;
		TWBR = twbr_value;
		//pullups?
	}
	
//******************************************************************
//Function  : To initialize TWI bus.
//Arguments : 1. Calculated twbr value.
//          : 2. Prescaler for TWI clock (1,4,16,64)
//Return    :    none
//note      : Use TWBR_CALC(speed)/prescaler macro to calculate twbr value.
//******************************************************************
	void twi_init_presc(uint8_t twbr_value, uint8_t prescaler)
	{
		TWBR = twbr_value;
		if (PrescalerValue == 1) TWSR=(0<<TWPS1)|(0<<TWPS0);
		if (PrescalerValue == 4) TWSR=(0<<TWPS1)|(1<<TWPS0);
		if (PrescalerValue == 16) TWSR=(1<<TWPS1)|(0<<TWPS0);
		if (PrescalerValue == 64) TWSR=(1<<TWPS1)|(1<<TWPS0);
		//pullups?
	}

//******************************************************************
//Function  : Sends start condition.
//Arguments : none
//Return    : none
//******************************************************************
	void twistart(void)
	{
		TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
		while (!(TWCR & (1<<TWINT)));
	}

//******************************************************************
//Function  : Sends stop condition.
//Arguments : none
//Return    : none
//******************************************************************
	void twistop(void)
	{
		TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
		while ((TWCR & (1<<TWSTO)));
	}

//******************************************************************
//Function  : To send single byte on TWI bus.
//Arguments : Byte to send.
//Return    : none
//******************************************************************
	void twiwrite(uint8_t data)
	{
		TWDR = data;
		TWCR = (1<<TWINT) | (1<<TWEN);
		while (!(TWCR & (1<<TWINT)));
	}

//******************************************************************
//Function  : To read single byte from TWI bus.
//Arguments : Loop counter 0 = NACK or ACK on any other value.
//Return    : Received byte.
//Note      : This function seems to be smaller than separate ACK'ing and NACK'ing functions.
//******************************************************************
	uint8_t twiread(uint16_t ack) // nack 0
	{
		TWCR = ack ?
		  ((1 << TWINT) | (1 << TWEN) | (1 << TWEA))
		: ((1 << TWINT) | (1 << TWEN)) ;
		
		while (!(TWCR & (1<<TWINT)));
		return TWDR;
	}

//******************************************************************
//Function  : To read single and contiunue receiving by sending ACK.
//Arguments : none
//Return    : Received byte.
//******************************************************************
	uint8_t twiread_ACK(void)
	{
		TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
		
		while (!(TWCR & (1<<TWINT)));
		return TWDR;
	}

//******************************************************************
//Function  : To read single and stop receiving by sending NACK.
//Arguments : none
//Return    : Received byte.
//******************************************************************
	uint8_t twiread_NACK(void)
	{
		TWCR = (1 << TWINT) | (1 << TWEN);
		
		while (!(TWCR & (1<<TWINT)));
		return TWDR;
	}

//******************************************************************
//Function  : To scan i2c bus. 
//Arguments : none
//Return    : none
//******************************************************************
#if defined(USART_H) && defined(DEFAULT_TX_BUFFER_SIZE)
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
				uart_puts_P(" (<< 1 for SLA_W) \t 0b");
				uart_putintr(s, 2);
				uart_puts_P(" 0\r\n");
			}
			twistop();
		}
	}
#else
	void scan(void){}
#endif