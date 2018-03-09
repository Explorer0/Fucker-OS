#ifndef   INCLUDE_VARGS_H
#define   INCLUDE_VARGS_H

typedef __builtin_va_list va_list;
//va_list, a type represents argument list
//ap declared as va_list, last is the last certain argument before variable arguments
//return ap the header of variable arguments
#define va_start(ap, last) (__builtin_va_start(ap, last))
//fetch a argument from ap with type description, then return it
#define va_arg(ap, type) (__builtin_va_arg(ap, type))
#define va_end(ap)

#endif
