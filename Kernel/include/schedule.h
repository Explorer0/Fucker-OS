#ifndef   INCLUDE_SCHEDULE_H
#define   INCLUDE_SCHEDULE_H
#include  "types.h"
#include  "task.h"
extern    task_block *running_task_list;
extern    task_block *finished_task_list;
extern    task_block *current_task;
extern    uint32_t flag;

void init_schedule();
//task dispatch
void schedule();
//switch current task
void change_task(task_block *target_task);
//switch task by switch task context
void switch_to_task(task_context *prev, task_context *next);

#endif
