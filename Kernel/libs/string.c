#include "string.h"
#include "console.h"

inline void memcpy(uint8_t *dest, const uint8_t *src, uint32_t len) {
  for (; len > 0; len--) {
    *dest++ = *src++;
  }
}
inline void memset(void *dest, uint8_t val, uint32_t len) {
  uint8_t *dst = (uint8_t *)dest;
  for (; len > 0; len--) {
    *dst++ = val;
  }
}
inline void bzero(void *dest, uint32_t len) { memset(dest, 0, len); }
int strcmp(const char *str1, const char *str2) {
  int i = 0;
  for (; str1[i] != 0 && str2[i] != 0; i++) {
    if (str1[i] > str2[i])
      return 1;
    else if (str1[i] < str2[i])
      return -1;
  }
  if (str1[i] == 0 && str2[i] != 0)
    return -1;
  else if (str1[i] != 0 && str2[i] == 0)
    return 1;
  else
    return 0;
}
char *strcpy(char *dest, const char *src) {
  int i;
  for (i = 0; src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  dest[i]='\0';
  return dest;
}
char *strcat(char *dest, const char *src) {
  char *iterator = dest;
  while (*iterator != '\0') {
    iterator++;
  }
  while (*src != '\0') {
    *iterator++ = *src++;
  }
  *iterator = '\0';
  return iterator;
}
int strlen(const char *src) {
  int len;
  for (len = 0; src[len] != '\0'; len++)
    ;
  return len;
}
void uitos(uint32_t n, char *dest) {
  // convert unsigned number into string
  uint8_t num_index = 0;
  do {
    uint8_t reamainder = (uint8_t)(n % 10);
    dest[num_index++] = (char)(reamainder + '0');
    n /= 10;
  } while (n);
  dest[num_index] = '\0';
  // reverse the dest
  uint8_t fore_index, back_index;
  for (fore_index = 0, back_index = num_index - 1; fore_index < back_index;
       fore_index++, back_index--) {
    char swap = dest[fore_index];
    dest[fore_index] = dest[back_index];
    dest[back_index] = swap;
  }
}
void itos(int32_t n, char *dest) {
  // convert signed number into string
  uint32_t n_abs;
  if (n < 0) {
    *dest++ = '-';
    n_abs = (uint32_t)(0 - n);
  } else {
    n_abs = (uint32_t)n;
  }
  uitos(n_abs, dest);
}
void itox(uint32_t n, char *dest){
  //if n is not 0x0, print non-0 characters from high to low(bit)
  int8_t bits;
  char tmp = 0;
  for (bits = 28; bits >= 0; bits -= 4) {
    tmp = (char)((n >> bits) & 0x0000000F);

    if (tmp >= 0xA) {
      tmp = tmp - 0xA + 'A';
    } else {
      tmp += '0';
    }
    *dest++=tmp;
  }
  *dest='\0';
}
