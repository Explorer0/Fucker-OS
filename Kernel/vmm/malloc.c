// #include "malloc.h"
// extern uint32_t kern_start;
// extern uint32_t kern_end;
// uint32_t placement_address = (uint32_t)&kern_end;
//
// uint32_t kmalloc(uint32_t size, bool algin, uint32_t *phys) {
//   if (algin && (!(placement_address & 0x00000FFF))) {
//     placement_address &= 0xFFFFF000;
//     placement_address += 0x1000;
//   }
//   if (phys)
//     *phys = placement_address;
//   uint32_t tmp = placement_address;
//   placement_address += size;
//   return tmp;
// }
// uint32_t kmalloc_a(uint32_t size) { return kmalloc(size, 1, NULL); }
// uint32_t kmalloc_p(uint32_t size, uint32_t *phys) {
//   return kmalloc(size, 0, phys);
// }
// uint32_t kmalloc_ap(uint32_t size, uint32_t *phys) {
//   return kmalloc(size, 1, phys);
// }
