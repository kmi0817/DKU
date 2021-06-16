/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32191556
*	    Student name : 박경미(Park Kyungmi)
*
*   lab1_sched_types.h :
*       - lab1 header file.
*       - must contains scueduler algorithm function's declations.
*
*/

#ifndef _LAB1_HEADER_H
#define _LAB1_HEADER_H

#include <stdbool.h>
#define MAX_SIZE 100

/*
 * You need to Declare functions in  here
 */

// Struct starts
// For Job
typedef struct process {
    char name;
    int arrive_time;
    int service_time;
    int completed; // 0: didn't completed, 1: completed
    int remain_time;
    int sched; // 0: has never scheduled, 1 or more: has scheduled
    int priority;
    int time_slice;

    int for_print[MAX_SIZE];
    int turnaround_time;
    int completion_time; // the time when the job terminates
    int response_time;
    int firstTurn_time; // the time when the job executes for the first time
} process;

// For Queue
typedef struct node {
    int value;
    struct node* link;
} node;

typedef struct {
    node* first;
    node* rear;
} queue;
// struct ends

// For RR Queue...
int RR_Push(int* qu, int index);
int RR_Pop(int* qu);
int RR_is_exist(int* qu, int index);

// Functions start
// For Queue
void init_queue(queue* q);
int Push(queue* q, int value);
int Pop(queue* q);
void Print(queue* q, process* jobs);
bool is_empty(queue* q);
int Size(queue* q);

// For Setting
void Set_remain_time(process* jobs, int cnt);
void Set_completed(process* jobs, int cnt);
void Set_sched(process* jobs, int cnt);
void Set_priority(process* jobs, int cnt);
void Set_time_slice(process* jobs, int cnt);
void Set_for_print(process* jobs, int cnt);

// For Sorting
void Sorting_priority(queue* q, process* jobs);
void Sorting_arrive_time( process* jobs, int cnt);

// For Scheduling Algorithms
void use_FCFS(struct process* jobs, int cnt);
void use_SJF(struct process* jobs, int cnt);
void use_RR(struct process* jobs, int cnt, int quantum);
void use_MLFQ(process* jobs, int cnt, int quantum);
// Functions end

#endif /* LAB1_HEADER_H*/
