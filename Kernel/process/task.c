#include "task.h"
#include "string.h"
#include "debug.h"
#include "schedule.h"

pid_t now_pid=0;
int32_t kernel_thread(int (*func)(void*), void *arg)
{
  task_block *new_task=(task_block*)kmalloc(STACK_SIZE);
  if(!new_task){
    printk("Out of memory! Failed to create new thread!\n");
    return -1;
  }
  bzero(new_task,STACK_SIZE);
  new_task->state=TASK_RUNNABLE;
  new_task->pid=now_pid++;
  new_task->next=running_task_list;


  uint32_t *stack=((uint32_t)new_task+STACK_SIZE);
  *(--stack)=arg;
  *(--stack)=kthread_exit;
  *(--stack)=func;
  new_task->context.esp=stack;
  new_task->context.flag_reg=0x200;

  task_block *task_iterator=running_task_list;
  while (task_iterator->next!=running_task_list) {
    task_iterator=task_iterator->next;
  }
  task_iterator->next=new_task;

  return new_task->pid;
}
void kthread_exit()
{
  disable_intr();
  //transfer current task block out of running_task_list
  task_block *task_iterator=running_task_list;
  task_block *discard_task=current_task;

  while (task_iterator->next!=current_task) {
    task_iterator=task_iterator->next;
  }
  task_iterator->next=current_task->next;
  current_task=current_task->next;
  //transfer current task block into finished_task_list
  if(finished_task_list==NULL){
    finished_task_list=discard_task;
    discard_task->next=finished_task_list;
  }else{
    task_iterator=finished_task_list;
    while (task_iterator->next!=finished_task_list) {
      task_iterator=task_iterator->next;
    }
    task_iterator->next=discard_task;
  }
  enable_intr();
  while (1) {;}
}
