#ifndef   INCLUDE_TASK_H
#define   INCLUDE_TASK_H
#include  "types.h"
#include  "pmm.h"
#include  "vmm.h"

typedef   uint32_t    pid_t;

typedef   struct  task_context{
  uint32_t  esp;
  uint32_t  ebp;
  uint32_t  ebx;
  uint32_t  esi;
  uint32_t  edi;
  uint32_t  flag_reg;
} task_context;
typedef   enum task_state {
  TASK_UNINIT,     //uninitialized
  TASK_SLEEPING,   //sleeping
  TASK_RUNNABLE,   //runnable
  TASK_ZOMBIE,     //zombie
} task_state;
typedef   struct  task_block{
  volatile  task_state state;           //task state
  pid_t     pid;                       //task ID
  task_context context;                //register context of task
  struct task_block *next;
} task_block;
//global task ID
extern pid_t now_pid;
int32_t kernel_thread(int (*func)(void*), void *arg);

void kthread_exit();

#endif
