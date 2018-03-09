#include "pmm.h"
#include "debug.h"

static uint32_t pmm_page_stack[PAGE_MAX_COUNT];
static uint32_t pmm_stack_top;
void show_memory_map() {
  uint32_t mmap_addr = glb_mboot_ptr->mmap_addr;
  uint32_t mmap_len = glb_mboot_ptr->mmap_length;

  mmap_entry_t *mmap_iterator = (mmap_entry_t *)(glb_mboot_ptr->mmap_addr);

  for (; mmap_iterator < mmap_addr + mmap_len; mmap_iterator++) {
    printk("base addr= 0x%x\t length=0x%x\t type=%d\n",
           mmap_iterator->base_addr_low, mmap_iterator->length_low,
           mmap_iterator->type);
  }
}
void init_pmm() {
  uint32_t mmap_addr = glb_mboot_ptr->mmap_addr;
  uint32_t mmap_len = glb_mboot_ptr->mmap_length;
  mmap_entry_t *mmap_iterator = (mmap_entry_t *)(glb_mboot_ptr->mmap_addr);

  for (; mmap_iterator < mmap_addr + mmap_len; mmap_iterator++) {
    if (mmap_iterator->type == 0x1 &&
        mmap_iterator->base_addr_low >= 0x100000) {
      uint32_t page;
      if (kern_end >= mmap_iterator->base_addr_low &&
          kern_end <=mmap_iterator->base_addr_low + mmap_iterator->length_low) {
        page = kern_end;
      } else {
        page = mmap_iterator->base_addr_low;
      }
      if (0 != (page % PMM_PAGE_SIZE)) {
        page &= PHY_PAGE_MASK;
        page += 0x1000;
      }

      while (page < mmap_iterator->base_addr_low + mmap_iterator->length_low &&
             phy_page_count < PAGE_MAX_COUNT) {
        phy_page_count++;
        pmm_free_page(page);
        page += PMM_PAGE_SIZE;
      }
    }
  }
}
uint32_t pmm_alloc_page() {
  if (pmm_stack_top > 0) {
    return pmm_page_stack[--pmm_stack_top];
  } else {
    printk("Allocate out of memory!\n");
    return 0xFFFFFFFF;
  }
}
void pmm_free_page(uint32_t page) {
  if (pmm_stack_top < phy_page_count)
    pmm_page_stack[pmm_stack_top++] = page;
  else
    printk("Free out of memory!\n");
}
