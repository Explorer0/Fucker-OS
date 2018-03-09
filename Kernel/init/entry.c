
#include "console.h"
#include "common.h"
#include "debug.h"
#include "string.h"
#include "gdt.h"
#include "idt.h"
#include "pmm.h"
#include "vmm.h"
#include "heap.h"

void kernel_init();
multiboot_t *glb_mboot_ptr;
char kern_stack[STACK_SIZE];
uint32_t kern_stack_top;
uint32_t flag=0;
void thread_func()
{
  while (1) {
    printk("Fuck\n");
  }

}
// temporary Page-Directory, temporary Page-Table, must be aligned in page size
__attribute__((section(".init.data"))) pgd_t *pd_tmp = 0x1000;
__attribute__((section(".init.data"))) pte_t *pt_tmp_backup = 0x2000;
__attribute__((section(".init.data"))) pte_t *pt_tmp = 0x3000;
__attribute__((section(".init.text"))) void kernel_entry() {
  pd_tmp[0] = (uint32_t)pt_tmp_backup | PAGE_PRESENT | PAGE_WRITE;
  pd_tmp[PGD_INDEX(PAGE_OFFSET)] = (uint32_t)pt_tmp | PAGE_PRESENT | PAGE_WRITE;

  uint32_t i;
  for (i = 0; i < PTE_SIZE; i++) {
    pt_tmp[i] = pt_tmp_backup[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
  }

  asm volatile("mov %0, %%cr3" : : "r"(pd_tmp));
  uint32_t cr0;
  asm volatile("mov %%cr0, %0" : "=r"(cr0));
  cr0 |= 0x80000000;
  asm volatile("mov %0, %%cr0" : : "r"(cr0));

  kern_stack_top = ((uint32_t)kern_stack + STACK_SIZE);
  asm volatile("mov %0, %%esp\n\t"
               "xor %%ebp, %%ebp"
               :
               : "r"(kern_stack_top));

  glb_mboot_ptr = mboot_ptr_tmp;
  kernel_init();
}
void kernel_init() {

  init_gdt();
  init_idt();
  init_timer(500);
  init_pmm();
  //after init_vmm(), couldn't use something in .init.data
  init_vmm();
  init_heap();
  init_schedule();

  console_clear();

  console_write("Fucker OS\n");
  char s1[20] = "FuckerMMMM";
  char *s2 = "Shit";
  strcat(s1, s2);
  printk_color(rc_black, rc_white, "Result:%s\t%s\n", s1, s2);

  asm volatile("int $0x3");
  asm volatile("int $0x4");
  printk_color(rc_black, rc_red, "\nThe Count of Physical Memory Page is: %d\n\n", phy_page_count);
  //show_memory_map();
  // uint32_t allc_addr=NULL;
  // printk_color(rc_black,rc_light_brown,"Test Physical Memory Alloc: \n");
  // allc_addr=pmm_alloc_page();
  // printk_color(rc_black,rc_light_brown,"Alloc Physical Addr: %x\n",
  // allc_addr); allc_addr=pmm_alloc_page();
  // printk_color(rc_black,rc_light_brown,"Alloc Physical Addr: %x\n",
  // allc_addr); allc_addr=pmm_alloc_page();
  // printk_color(rc_black,rc_light_brown,"Alloc Physical Addr: %x\n",
  // allc_addr);
  char *fuck_buffer=(char*)kmalloc(100);
  printk("Address of fuck_buffer: 0x%x\n",fuck_buffer);
  int *bitch=(int*)kmalloc(sizeof(int));
  printk("Address of bitch: 0x%x\n",bitch);
  kernel_thread(thread_func,NULL);
  enable_intr();
  while (1) {
      printk("In main thread\n");
  }
  while (1) {
    asm volatile ("hlt");
  }
  return 0;
}
