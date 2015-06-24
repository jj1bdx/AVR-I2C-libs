#ifndef TWI_ROUTINES_H
#define TWI_ROUTINES_H

/************************************************************************************
 *  Published on: 13-02-2015                                                        *
 *  Author: jnk0le@hotmail.com                                                      *
 *  https://github.com/jnk0le                                                       *
 *  This library is distributed under MIT license terms                             *
 ************************************************************************************/
 
#define TWBR_CALC(speed) ( (F_CPU / speed) - 16UL ) / 2UL
#define SLA_W(address)  (address << 1)
#define SLA_R(address)  ((address << 1) + 0x01)
 
void twi_init(uint8_t twbr_value);
void twistart(void);
void twistop(void);
void twiwrite(uint8_t data);
uint8_t twiread(uint16_t ack);
//void scan(void);
 
 
#endif