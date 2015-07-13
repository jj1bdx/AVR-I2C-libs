//**************************************************************
// ****** FUNCTIONS FOR I2C EEPROMs INTERFACING *******
//**************************************************************
//Compiler          : AVR-GCC
//Target devices    : EEPROMs 24C32 - 24C512
//Author            : jnk0le@hotmail.com
//                    https://github.com/jnk0le
//Date              : 24 June 2015
//License           : MIT
//**************************************************************

#include "TWI_routines.h"
#include "24C32.h"

//******************************************************************
//Function  : To write single byte into EEPROM memory.
//Arguments : 1. SLA_W device address.
//          : 2. 16 bit internal address of the location to be written.
//          : 3. One byte of data to be written into EEPROM.
//Return    :    none
//******************************************************************
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

//******************************************************************
//Function  : To read single byte from the EEPROM memory.
//Arguments : 1. SLA_W device address.
//          : 2. 16 bit internal address of the location to read.
//Return    :    Byte containing the read data.
//******************************************************************
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
		//dat = twiread_NACK();
		twistop();
		
		return dat;
	}

//******************************************************************
//Function  : Read single byte from the EEPROM, into given location of system memory.
//Arguments : 1. SLA_W device address.
//          : 2. 16 bit internal address of the location to read.
//          : 3. Pointer of the location to load byte from EEPROM.
//Return    :    none
//******************************************************************
	void eereadto(uint8_t device, uint16_t addr, uint8_t *dat)
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
		*dat = twiread(0); //0 - NOACK
		//*dat = twiread_NACK();
		twistop();
	}

//******************************************************************
//Function  : Write an EEPROM page from a given array.
//Arguments : 1. SLA_W device address.
//          : 2. 16 bit initial address of the location to write
//          : 3. Number of bytes to write.
//          : 4. Pointer to array containing data.
//Return    :    none
//Note      : Page Write mode allows for multiple writes in one cycle, provided that all bytes
//          : fits up to the end of the row, otherwise a condition known as 'roll-over' will occur.
//          : That means the most significant memory address bits have to be the same, during one page write.
//          : Check datasheet of specified memory, for more details about the row size (eg. 32 bytes for the C32 & C64, 64 for C128).
//******************************************************************
	void ee_write_page(uint8_t device, uint16_t addr, uint8_t len, uint8_t *buf)
	{
		while(1) // wait until device is unconciscious
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

//******************************************************************
//Function  : Read a burst of bytes from an EEPROM memory.
//Arguments : 1. SLA_W device address.
//          : 2. 16 bit initial address of the the location to read
//          : 3. Number of bytes to read.
//          : 4. Pointer to array which have to be filled with incoming data.
//Return    :    none
//******************************************************************
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
		
		//while( --len )
		//	*buf++ = twiread_ACK();
		
		//*buf = twiread_NACK();
		
		twistop();
	}
 