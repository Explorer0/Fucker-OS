#include "heap.h"
#include "pmm.h"
#include "vmm.h"

heap_node *heap_list=HEAP_START;
void get_chunk(pgd_t *pd_now, uint32_t virtual_addr, uint32_t size)
{
  uint32_t i,page_count=size/PAGE_SIZE+1;
  uint32_t physical_addr;

  for(i=0;i<page_count;i++,virtual_addr+=PAGE_SIZE){
    physical_addr=pmm_alloc_page();
    virtual_addr&=PAGE_MASK;
    map(pd_now,virtual_addr,physical_addr,PAGE_PRESENT|PAGE_WRITE);
  }
}
void heap_integration()
{
  heap_node *heap_iterator=heap_list->next;
  do {
    if(!(heap_iterator->flags & HEAP_ALLOCATED)&& !(heap_iterator->prev->flags & HEAP_ALLOCATED) && heap_iterator->next!=heap_list){
      heap_node *prev_heap=heap_iterator->prev;
      prev_heap->size+=(heap_iterator->size+sizeof(heap_node));

      prev_heap->next=heap_iterator->next;
      heap_iterator->next->prev=prev_heap;
    }
    heap_iterator=heap_iterator->next;
  } while(heap_iterator!=heap_list);
}
void init_heap()
{
  get_chunk(pd_kern, (uint32_t)heap_list, 100*PAGE_SIZE);
  heap_list->prev=heap_list;
  heap_list->next=heap_list;
  heap_list->flags=0x0;
  heap_list->size=100*PAGE_SIZE-sizeof(heap_node);
}
void *kmalloc(uint32_t size)
{
  heap_node *heap_iterator=heap_list;
  heap_node *tmp_heap=NULL;

  do {
    if(heap_iterator->size>=(size+sizeof(heap_node))){
      tmp_heap=(heap_node*)((uint32_t)heap_iterator+(heap_iterator->size-size));
      tmp_heap->prev=heap_iterator;
      tmp_heap->next=heap_iterator->next;
      tmp_heap->flags&=HEAP_ALLOCATED;
      tmp_heap->size=size;

      heap_iterator->next->prev=tmp_heap;
      heap_iterator->next=tmp_heap;
      heap_iterator->size-=(size+sizeof(heap_node));

      break;
    }
    heap_iterator=heap_iterator->next;
  } while(heap_iterator!=heap_list);
  if(tmp_heap==NULL){
    tmp_heap=(heap_node*)((uint32_t)heap_list->prev+heap_list->prev->size+sizeof(heap_node));
    get_chunk(pd_kern, tmp_heap, size*4);
    tmp_heap->prev=heap_list->prev;
    tmp_heap->next=heap_list;
    heap_list->prev->next=tmp_heap;
    heap_list->prev=tmp_heap;

    tmp_heap=kmalloc(size);
  }
  return (void*)((uint32_t)tmp_heap+sizeof(heap_node));
}
void kfree(void *buffer)
{
  heap_node *tmp_heap=(heap_node*)((uint32_t)buffer+sizeof(heap_node));
  tmp_heap->flags^=HEAP_ALLOCATED;
  if(!(tmp_heap->prev->flags&HEAP_START)){
    heap_node *prev_heap=tmp_heap->prev;
    prev_heap->size+=(tmp_heap->size+sizeof(heap_node));

    prev_heap->next=tmp_heap->next;
    tmp_heap->next->prev=prev_heap;
  }
}
