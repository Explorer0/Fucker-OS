#include "common.h"

inline void outb(uint16_t port, uint8_t value) {
  // outb is a inst of X86
  //%1 represents 'value', %0 represents 'port'
  //'d' mean edx connect with 'port', 'a' mean eax connect with 'value' 'N' mean
  //a number between 0-255
  asm volatile("outb %1, %0" ::"dN"(port), "a"(value));
}
inline uint8_t inb(uint16_t port) {
  uint8_t ret;
  //'=' mean ret is an output operand that only be written
  asm volatile("inb %1, %0" : "=a"(ret) : "dN"(port));

  return ret;
}
inline uint16_t inw(uint16_t port) {
  uint16_t ret;
  asm volatile("inw %1, %0" : "=a"(ret) : "dN"(port));
  return ret;
}
//enable interruption
inline void enable_intr()
{
    asm volatile ("sti");
}
// disable interruption
inline void disable_intr()
{
    asm volatile ("cli" ::: "memory");
}
