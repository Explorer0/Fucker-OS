#ifndef   INCLDE_VMM_H
#define   INCLDE_VMM_H
#include  "types.h"
#include  "idt.h"
#include  "pmm.h"

//virtual offset address
#define    PAGE_OFFSET      0xC0000000
#define    PAGE_PRESENT     0x1
#define    PAGE_WRITE       0x2
#define    PAGE_USER        0X4
#define    PAGE_SIZE        0x1000
#define    PAGE_MASK        0xFFFFF000
//get index of virtual address in Page-Directory
#define    PGD_INDEX(x)     ((x>>22) & 0x3FF)
//get index of virtual address in Page-Table
#define    PTE_INDEX(x)     ((x>>12) & 0x3FF)
//get offset of virtual address in page
#define    OFFSET_INDEX(x)  (x & 0xFFF)

//page directory entry
typedef    uint32_t         pgd_t;
//page table entry
typedef    uint32_t         pte_t;
#define    PGD_SIZE         PAGE_SIZE/sizeof(pte_t)
#define    PTE_SIZE         PAGE_SIZE/sizeof(uint32_t)
#define    PTE_COUNT        128
//page directory
extern     pgd_t pd_kern[PGD_SIZE];

void init_vmm();
void switch_pgd(pgd_t *pd);
void map(pgd_t *pd_now, uint32_t virtual_addr, uint32_t physical_addr,uint32_t flags);
void umap(pgd_t *pd_now, uint32_t virtual_addr);
uint32_t get_mapping(pgd_t *pd_now, uint32_t virtual_addr, uint32_t *physical_addr);

void page_fault(pre_regs_t *regs);
#endif
