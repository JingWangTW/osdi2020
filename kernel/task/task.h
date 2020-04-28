#ifndef __TASK_H
#define __TASK_H

#include "lib/type.h"

typedef enum {
    RUNNING = 1,
    DEAD = 2,
} task_state_t;

typedef struct {

    unsigned long x19;
    unsigned long x20;
    unsigned long x21;
    unsigned long x22;
    unsigned long x23;
    unsigned long x24;
    unsigned long x25;
    unsigned long x26;
    unsigned long x27;
    unsigned long x28;
    unsigned long fp;   // x29
    unsigned long lr;   // x30
    unsigned long sp;

} context_t;

typedef struct {
    
    context_t cpu_context;    
    
    uint64_t task_id;
    task_state_t state;
    void (*func)();    

    uint64_t counter;
    uint64_t priority;  /* at this time, all task has the same priority */

} thread_info_t;

/* defined in task.S */
extern void switch_to ( thread_info_t *, thread_info_t * );
extern void launch_init ( );
extern thread_info_t* get_current_task ();
extern void default_task_start();

/* global variable for other file to use */
extern thread_info_t * IDLE;

void idle ( );
int privilege_task_create ( void(*func)() );
int find_usable_in_pool ();
void context_switch ( thread_info_t * next );
void schedule ( );

#endif