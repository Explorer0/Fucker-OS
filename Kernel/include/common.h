#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H
#include "types.h"
// write a byte into port
void outb(uint16_t port, uint8_t value);
// read a byte from port
uint8_t inb(uint16_t port);
// read a word(double byte) from port
uint16_t inw(uint16_t port);
// enable interruption
void enable_intr();

// disable interruption
void disable_intr();
#endif
