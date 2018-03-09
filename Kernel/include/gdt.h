#ifndef INCLUDE_GDT_H
#define INCLUDE_GDT_H
#include "types.h"
//packed mean align with original byte, without align optimization
//global descriptor table structure
typedef struct gdt_entry_t {
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t  base_middle;
  uint8_t  access;
  uint8_t  granularity;
  uint8_t  base_high;
} __attribute__((packed)) gdt_entry_t;

//GDTR structure
typedef struct gdt_ptr_t {
  uint16_t limit;               //the count of gdt
  uint32_t base;                //gdt address
} __attribute__((packed)) gdt_ptr_t;

void init_gdt();
//An assembly function to make GDTR point to gdt
extern void gdt_flush(uint32_t);

#endif
