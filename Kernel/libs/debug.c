#include "debug.h"
#include "console.h"
#include "string.h"
#include "vargs.h"

void printk_color(real_color_t back, real_color_t fore, const char *format, ...) {
  static char buffer[1024] = {'\0'};
  char num_str[32] = {'\0'};
  va_list args;
  int num_param, len;
  char char_param, *str_param;

  char *iterator = buffer;
  va_start(args, format);
  while (*format) {
    if ('%' == *format) {
      switch (*++format) {
      case 's':
        //fetch string from arguments
        //combine it with buffer
        str_param = va_arg(args, char *);
        strcpy(iterator, str_param);
        len = strlen(str_param);
        iterator += len;
        break;
      case 'd':
        //fetch number from arguments
        //convert it into string
        //combine the string with buffer
        num_param = va_arg(args, int);
        itos(num_param, num_str);
        len = strlen(num_str);
        strcpy(iterator, num_str);
        iterator += len;
        break;
      case 'x':
         num_param = va_arg(args, int);
         itox(num_param, num_str);
         len = strlen(num_str);
         strcpy(iterator, num_str);
         iterator += len;
         break;
      case 'c':
        char_param = (char)va_arg(args, int);
        *iterator++ = char_param;
        break;
      default:
        *iterator++ = '%';
        *iterator++ = *format;
        break;
      }
    } else {
      *iterator++ = *format;
    }
    if (*format == '\0')
      break;
    ++format;
  }
  va_end(args);
  //add end flag to buffer
  *iterator = '\0';
  console_write_color(buffer, back, fore);
}
void printk(const char *format, ...){
  static char buffer[1024] = {'\0'};
  char num_str[32] = {'\0'};
  va_list args;
  int num_param, len;
  char char_param, *str_param;

  char *iterator = buffer;
  va_start(args, format);
  while (*format) {
    if ('%' == *format) {
      switch (*++format) {
      case 's':
        //fetch string from arguments
        //combine it with buffer
        str_param = va_arg(args, char *);
        strcpy(iterator, str_param);
        len = strlen(str_param);
        iterator += len;
        break;
      case 'd':
        //fetch number from arguments
        //convert it into string
        //combine the string with buffer
        num_param = va_arg(args, int);
        itos(num_param, num_str);
        len = strlen(num_str);
        strcpy(iterator, num_str);
        iterator += len;
        break;
      case 'x':
           num_param = va_arg(args, int);
           itox(num_param, num_str);
           len = strlen(num_str);
           strcpy(iterator, num_str);
           iterator += len;
           break;
      case 'c':
        char_param = (char)va_arg(args, int);
        *iterator++ = char_param;
        break;
      default:
        *iterator++ = '%';
        *iterator++ = *format;
        break;
      }
    } else {
      *iterator++ = *format;
    }
    if (*format == '\0')
      break;
    ++format;
  }
  va_end(args);
  //add end flag to buffer
  *iterator = '\0';
  console_write_color(buffer, rc_black, rc_white);
}
