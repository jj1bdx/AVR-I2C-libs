#ifndef EE_24C32_H
#define EE_24C32_H

#include <TWI_routines.h>

void eewrite(uint8_t device, uint16_t addr, uint8_t dat);
uint8_t eeread(uint8_t device, uint16_t addr);

void ee_write_page(uint8_t device, uint16_t addr, uint8_t len, uint8_t *buf);
void ee_read_page(uint8_t device, uint16_t addr, uint16_t len, uint8_t *buf);

#endif