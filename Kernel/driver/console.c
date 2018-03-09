#include "console.h"
#include "common.h"
#include "types.h"
#include "vmm.h"

static uint16_t *video_memory =
    (uint16_t *)(0xB8000+PAGE_OFFSET); // the beginning address of VGA in text-mode
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;
static void move_cursor() {
  uint16_t cursor_location = cursor_y * 80 + cursor_x;
  // To get location of cursor, we need read it from some registers
  // index-reg's port is 0x3D4, it provides High-8 bits of cursor location as
  // it's value is 0x14  atferward we could read/write data from port 0x3D5
  outb(0x3D4, 14);
  outb(0x3D5, cursor_location >> 8);
  // index-reg's port is 0x3D4, it provides Low-8 bits of cursor location as
  // it's value is 0x15
  outb(0x3D4, 15);
  outb(0x3D5, cursor_location);
}
point get_cursor(){
  point cur_cursor;
  cur_cursor.cursor_x=cursor_x;
  cur_cursor.cursor_y=cursor_y;
}
void set_cursor(point target_position){
  cursor_x=target_position.cursor_x;
  cursor_y=target_position.cursor_y;
  move_cursor();
}

void console_clear() {
  uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
  uint16_t blank = 0x20 | (attribute_byte << 8);

  int i;
  for (i = 0; i < 80 * 25; i++) {
    video_memory[i] = blank;
  }
  cursor_x = 0;
  cursor_y = 0;
  move_cursor();
}
static void scroll() {
  uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
  uint16_t blank = 0x20 | (attribute_byte << 8);

  if (cursor_y >= 25) {
    int i;
    for (i = 0 * 80; i < 24 * 80; i++)
      video_memory[i] = video_memory[i + 80];
    for (i = 24 * 80; i < 25 * 80; i++)
      video_memory[i] = blank;

    cursor_y = 24;
  }
}
void console_putc(char c){
  console_putc_color(c,rc_black,rc_white);
}
void console_putc_color(char c, real_color_t back, real_color_t fore) {
  uint8_t back_color = (uint8_t)back;
  uint8_t fore_color = (uint8_t)fore;

  uint8_t attribute_byte = (back_color << 4) | (fore_color & 0X0F);
  uint16_t attribute = attribute_byte << 8;
  // In ancii 0x08 represents backspace
  // In ancii 0x09 represents tab
  if (c == 0x08 && cursor_x) {
    cursor_x--;
  } else if (c == 0x09) {
    cursor_x = (cursor_x + 8) & ~(8 - 1);
  } else if (c == '\r') {
    cursor_x = 0;
  } else if (c == '\n') {
    cursor_x = 0;
    cursor_y++;
  } else if (c >= ' ') {
    video_memory[cursor_y * 80 + cursor_x] = c | attribute;
    cursor_x++;
  }

  if (cursor_x >= 80) {
    cursor_x = 0;
    cursor_y++;
  }
  scroll();
  move_cursor();
}
void console_write(char *cstr) {
  while (*cstr) {
    /* code */
    console_putc_color(*cstr++, rc_black, rc_white);
  }
}
void console_write_color(char *cstr, real_color_t back, real_color_t fore) {
  while (*cstr) {
    /* code */
    console_putc_color(*cstr++, back, fore);
  }
}
void console_write_dec(uint32_t n, real_color_t back, real_color_t fore) {
  char num_str[32] = {NULL};
  // store n in num_str as string
  uint8_t num_index = 0;
  do {
    uint8_t reamainder = (uint8_t)(n % 10);
    num_str[num_index] = (char)(reamainder + '0');
    num_index++;
    n /= 10;
  } while (num_index < 32 && n);
  // reverse the num_str
  uint8_t fore_index, back_index;
  for (fore_index = 0, back_index = num_index - 1; fore_index < back_index;
       fore_index++, back_index--) {
    char swap = num_str[fore_index];
    num_str[fore_index] = num_str[back_index];
    num_str[back_index] = swap;
  }
  console_write_color(num_str, back, fore);
}
void console_write_hex(uint32_t n, real_color_t back, real_color_t fore) {
  //print prefix of Hex
  console_write_color("0x", back, fore);
  if (0 == n) {
    console_putc_color('0', back, fore);
    return;
  }
  //if n is not 0x0, print non-0 characters from high to low(bit)
  int8_t bits;
  char tmp = 0;
  for (bits = 28; bits >= 0; bits -= 4) {
    tmp = (char)((n >> bits) & 0x0000000F);

    if (0 == tmp) {
      continue;
    } else if (tmp >= 0xA) {
      tmp = tmp - 0xA + 'A';
    } else {
      tmp += '0';
    }
    console_putc_color(tmp, back, fore);
  }
}
