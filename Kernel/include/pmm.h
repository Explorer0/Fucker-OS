#ifndef   INCLDE_PMM_H
#define   INCLDE_PMM_H
#include  "types.h"

#define   PMM_MAX_SIZE     0x20000000
#define   PMM_PAGE_SIZE		 0x1000
#define   PAGE_MAX_COUNT   (PMM_MAX_SIZE/PMM_PAGE_SIZE)+1
#define   PHY_PAGE_MASK		 0xFFFFF000
#define		STACK_SIZE			 8192

typedef
struct multiboot_t {
	uint32_t flags;			// Multiboot 的版本信息
	/**
	 * 从 BIOS 获知的可用内存
	 *
	 * mem_lower和mem_upper分别指出了低端和高端内存的大小，单位是K。
	 * 低端内存的首地址是0，高端内存的首地址是1M。
	 * 低端内存的最大可能值是640K。
	 * 高端内存的最大可能值是最大值减去1M。但并不保证是这个值。
	 */
	uint32_t mem_lower;
	uint32_t mem_upper;

	uint32_t boot_device;		// 指出引导程序从哪个BIOS磁盘设备载入的OS映像
	uint32_t cmdline;		// 内核命令行
	uint32_t mods_count;		// boot 模块列表
	uint32_t mods_addr;

	/**
	 * ELF 格式内核映像的section头表。
	 * 包括每项的大小、一共有几项以及作为名字索引的字符串表。
	 */
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;

	/**
	 * 以下两项指出保存由BIOS提供的内存分布的缓冲区的地址和长度
	 * mmap_addr是缓冲区的地址，mmap_length是缓冲区的总大小
	 * 缓冲区由一个或者多个下面的大小/结构对 mmap_entry_t 组成
	 */
	uint32_t mmap_length;
	uint32_t mmap_addr;

	uint32_t drives_length; 	// 指出第一个驱动器结构的物理地址
	uint32_t drives_addr; 		// 指出第一个驱动器这个结构的大小
	uint32_t config_table; 		// ROM 配置表
	uint32_t boot_loader_name; 	// boot loader 的名字
	uint32_t apm_table; 	    	// APM 表
	uint32_t vbe_control_info;
	uint32_t vbe_mode_info;
	uint32_t vbe_mode;
	uint32_t vbe_interface_seg;
	uint32_t vbe_interface_off;
	uint32_t vbe_interface_len;
} __attribute__((packed)) multiboot_t;
typedef
struct mmap_entry_t{
  uint32_t size;
  uint32_t base_addr_low;
  uint32_t base_addr_high;
  uint32_t length_low;
  uint32_t length_high;
  uint32_t type;
} __attribute__((packed)) mmap_entry_t;


extern multiboot_t *mboot_ptr_tmp;
extern multiboot_t *glb_mboot_ptr;

uint32_t phy_page_count;
extern uint32_t *kern_start;
extern uint32_t *kern_end;
extern uint32_t kern_stack_top;

void show_memory_map();
void init_pmm();
uint32_t pmm_alloc_page();
void pmm_free_page(uint32_t page);
#endif
