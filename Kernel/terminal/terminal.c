#include "terminal.h"
#include "debug.h"
#include "keyboard.h"
#include "console.h"

char getch(){
  KEYCODE key=KEY_UNKNOWN;
  while (key==KEY_UNKNOWN) {
    key=kkybrd_get_last_key();
  }
  kkybrd_discard_last_key();
  return kkybrd_key_to_anscii(key);
}
void  init_terminal(/* arguments */) {
  char cmd[128]={0};
  uint8_t index=0;
  printk("/*******************Termianl-Mode********************/\n");
  printk("Command:> ");
  while (TRUE) {
    char ch=getch();
    if(ch==0x80)
      cmd[index--]='\0';
    else
      cmd[index++]=ch;
    console_write(cmd);
  }
}
