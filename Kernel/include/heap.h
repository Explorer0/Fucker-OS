#ifndef   INCLUDE_HEAP_H
#define   INCLUDE_HEAP_H
#include  "types.h"

#define   HEAP_START      0xE0000000
#define   HEAP_ALLOCATED  0x1
typedef   struct heap_node{
  struct heap_node *prev;
  struct heap_node *next;
  uint8_t   flags;
  uint32_t  size;
} heap_node;

void init_heap();
void *kmalloc(uint32_t size);
void kfree(void *buffer);

#endif
