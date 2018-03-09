#include  "schedule.h"
#include  "vmm.h"
#include  "string.h"
#include  "common.h"
#include  "debug.h"

task_block *running_task_list=NULL;
task_block *finished_task_list=NULL;
task_block *current_task=NULL;

void init_schedule()
{
  current_task=(task_block*)(kern_stack_top-STACK_SIZE);
  if(!current_task){
    printk("Out of Memory! Failed to initialize schedule.\n");
    return;
  }
  bzero(current_task,sizeof(task_block));
  current_task->state=TASK_RUNNABLE;
  current_task->pid=now_pid++;
  current_task->next=current_task;

  running_task_list=current_task;
}
void schedule()
{
  printk("Changing Task\n");
  if(current_task!=NULL){
    change_task(current_task->next);
  }
}
void change_task(task_block *next)
{
  if(current_task!=next){
    task_block *prev_task=current_task;
    current_task=next;
    switch_to_task(&(prev_task->context),&(current_task->context));
    printk("Task changed!\n");
  }
}
