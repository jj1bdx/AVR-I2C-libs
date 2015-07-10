#ifndef EE_24C32_H
#define EE_24C32_H

/************************************************************************************
 *  Published on: 13-02-2015                                                        *
 *  Author: jnk0le@hotmail.com                                                      *
 *  https://github.com/jnk0le                                                       *
 *  This library is distributed under MIT license terms                             *
 ************************************************************************************/

#include <TWI_routines.h>

void eewrite(uint8_t device, uint16_t addr, uint8_t dat);
uint8_t eeread(uint8_t device, uint16_t addr);
void eereadto(uint8_t device, uint16_t addr, uint8_t *dat);

void ee_write_page(uint8_t device, uint16_t addr, uint8_t len, uint8_t *buf);
void ee_read_page(uint8_t device, uint16_t addr, uint16_t len, uint8_t *buf);

#endif