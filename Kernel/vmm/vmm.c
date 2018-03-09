#include "vmm.h"
#include "debug.h"
#include "idt.h"
#include "pmm.h"
#include "string.h"

pgd_t pd_kern[PGD_SIZE] __attribute__((aligned(PAGE_SIZE)));
static pte_t pt_kern[PTE_COUNT][PTE_SIZE] __attribute__((aligned(PAGE_SIZE)));

void init_vmm() {
  uint32_t pt_first_idx = PGD_INDEX(PAGE_OFFSET);
  uint32_t i, j, page = 0;
  pte_t *pt_tmp = (pte_t *)pt_kern;
  for (i = 0; i < PTE_COUNT * PTE_SIZE; i++) {
    pt_tmp[i] = (i << 12) | PAGE_PRESENT | PAGE_WRITE;
  }
  // for (i = 0; i < PTE_COUNT; i++) {
  //   for (j = 0; j < PTE_SIZE; j++) {
  //     pt_kern[i][j] = (page << 12) | PAGE_PRESENT | PAGE_WRITE;
  //     page++;
  //   }
  // }
  for (i = pt_first_idx, j = 0; j < PTE_COUNT; i++, j++) {
    pd_kern[i] =
        ((uint32_t)&pt_kern[j] - PAGE_OFFSET) | PAGE_PRESENT | PAGE_WRITE;
  }
  register_interrupt_handler(14, &page_fault);
  switch_pgd((pgd_t *)((uint32_t)&pd_kern - PAGE_OFFSET));
}
void switch_pgd(pgd_t *pd) { asm volatile("mov %0, %%cr3" : : "r"(pd)); }
void page_fault(pre_regs_t *regs) {
  uint32_t cr2;
  asm volatile("mov %%cr2, %0" : "=r"(cr2));
  printk("Page fault at 0x%x, virtual fault address 0x%x", regs->eip, cr2);
  printk("Error code: %x\n", regs->err_code);
  if (!(regs->err_code & 0x1)) {
    printk("Page was not present.\n");
  }
  if (regs->err_code & 0x2) {
    printk("Write error.\n");
  } else {
    printk("Read error.\n");
  }

  if (regs->err_code & 0x4) {
    printk("In user mode.\n");
  } else {
    printk("In kernle mode.\n");
  }

  if (regs->err_code & 0x8) {
    printk("Reserved bits being overwritten.\n");
  }
  if (regs->err_code & 0x10) {
    printk("The fault occurred during an instruction fetch.\n");
  }

  while (1)
    ;
}
void map(pgd_t *pd_now, uint32_t virtual_addr, uint32_t physical_addr,
         uint32_t flags) {
  pte_t physical_page = physical_addr & PAGE_MASK;
  //when we get the address of Page-Table, must erase flags setted, then add PAGE_OFFSET
  pte_t *pt_now = (pte_t *)(pd_now[PGD_INDEX(virtual_addr)]&PAGE_MASK);

  if (!pt_now) {
    pt_now = (pte_t *)pmm_alloc_page();
    pd_now[PGD_INDEX(virtual_addr)] =
        (uint32_t)pt_now | PAGE_PRESENT | PAGE_WRITE;

    pt_now = (pte_t *)((uint32_t)pt_now + PAGE_OFFSET);
    bzero(pt_now, PAGE_SIZE);
  } else {
    pt_now = (pte_t *)((uint32_t)pt_now + PAGE_OFFSET);
  }
  pt_now[PTE_INDEX(virtual_addr)] = physical_page | flags;

  asm volatile ("invlpg (%0)" : : "a" (virtual_addr));
}
void umap(pgd_t *pd_now, uint32_t virtual_addr) {
  pte_t *pt_now = (pte_t*)(pd_now[PGD_INDEX(virtual_addr)]&PAGE_MASK);
  if (!pt_now)
    return;
  pt_now = (pte_t *)((uint32_t)pt_now + PAGE_OFFSET);
  pt_now[PTE_INDEX(virtual_addr)] = 0;

  asm volatile("invlpg (%0)" : : "a"(virtual_addr));
}
uint32_t get_mapping(pgd_t *pd_now, uint32_t virtual_addr,
                     uint32_t *physical_addr);
