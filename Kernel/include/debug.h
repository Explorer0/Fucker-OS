#ifndef   INCLUDE_DEBUG_H
#define   INCLUDE_DEBUG_H
#include "types.h"
#include "console.h"
//A function like printf, but it only support '%d','%s','%c', and not allow '%%'
void printk_color(real_color_t back, real_color_t fore, const char *format, ...);
void printk(const char *format, ...);
#endif
