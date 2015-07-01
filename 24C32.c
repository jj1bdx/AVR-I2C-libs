#include <TWI_routines.h>

void eewrite(uint8_t device, uint16_t addr, uint8_t dat)
{
	while(1)
	{
		twistart();
		twiwrite(device);
		
		if ( (TWSR & 0xF8) != TW_MT_SLA_NACK) break;
		
		twistop();
	}

	twiwrite(addr >> 8);
	twiwrite(addr);

	twiwrite(dat);
	twistop();
}

uint8_t eeread(uint8_t device, uint16_t addr)
{
	uint8_t dat;
	
	while(1)
	{
		twistart();
		twiwrite(device);
		
		if ( (TWSR & 0xF8) != TW_MT_SLA_NACK) break;
		
		twistop();
	}
	
	twiwrite(addr >> 8); 
	twiwrite(addr); 

	twistart();
	twiwrite(device+1);
	dat = twiread(0); //0 - NOACK
	twistop();
	
	return dat;
}

void ee_write_page(uint8_t device, uint16_t addr, uint8_t len, uint8_t *buf) // check dadasheet for maximum page size
{
	while(1)
	{
		twistart();
		twiwrite(device);
		
		if ( (TWSR & 0xF8) != TW_MT_SLA_NACK) break;
		
		twistop();
	}
	
	twiwrite(addr >> 8);
	twiwrite(addr);
	
	while(len--) twiwrite(*buf++);
	
	twistop();
}

void ee_read_page(uint8_t device, uint16_t addr, uint16_t len, uint8_t *buf) 
{
	while(1)
	{
		twistart();
		twiwrite(device);
		
		if ( (TWSR & 0xF8) != TW_MT_SLA_NACK) break;
		
		twistop();
	}
	
	twiwrite(addr >> 8);
	twiwrite(addr);
	
	twistart();
	twiwrite(device+1);
	
	do
		*buf++ = twiread( --len );
	while( len );
	
	twistop();
}

