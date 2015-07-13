#ifndef TWI_ROUTINES_H
#define TWI_ROUTINES_H

/************************************************************************************
 *  Published on: 13-02-2015                                                        *
 *  Author: jnk0le@hotmail.com                                                      *
 *  https://github.com/jnk0le                                                       *
 *  This library is distributed under MIT license terms                             *
 ************************************************************************************/
 
#ifndef __OPTIMIZE__
	#warning "Compiler optimizations disabled; functions from TWI_routines.h won't work as designed"
#endif

#ifndef F_CPU
	#error F_CPU is undefined, TWI cannot work correctly without this parametr
#endif
 
 #define TWBR_CALC(speed) ( (F_CPU / speed) - 16UL ) / 2UL
#define SLA_W(address)  (address << 1)
#define SLA_R(address)  ((address << 1) + 0x01)
 
void twi_init(uint8_t twbr_value);
void twi_init_presc(uint8_t twbr_value, uint8_t prescaler);
void twistart(void);
void twistop(void);
void twiwrite(uint8_t data);
uint8_t twiread(uint16_t ack);

uint8_t twiread_ACK(void);
uint8_t twiread_NACK(void);

void scan(void);
 
 
#endif