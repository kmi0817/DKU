/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm function'definition.
*
*/

#include <aio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>

#include <stdbool.h>
#include <limits.h> // for INT_MIN

#include "lab1_sched_types.h"
#define QUEUE_EMPTY INT_MIN
#define MAX_SIZE 100

char* original_ordered_jobs; // jobs' original input order
int RR_first = 0, RR_rear = 0; // For RR Queue...

/*
 * you need to implement FCFS, RR, SJF, MLFQ scheduler. 
 */

// For RR Queue...
int RR_Push(int* qu, int index) {
    if (RR_rear >= MAX_SIZE - 1) {
        printf("Full\n"); return -1;
    }
    qu[RR_rear++] = index;
    return 1;
}
int RR_Pop(int* qu) {
    if (RR_first > RR_rear) {
        printf("empty\n");
        return -1;
    }
    return qu[RR_first++];
}
int RR_is_exist(int* qu, int index) {
    for (int i = RR_first; i < RR_rear; i++)
        if (qu[i] == index)
            return 1;
    return -1;
}

// For Queue
void init_queue(queue* q) {
    q->first = NULL;
    q->rear = NULL;
}

int Push(queue* q, int value) {
    node* newnode = malloc(sizeof(node));

    if (newnode == NULL)
        return -1;

    newnode->value = value;
    newnode->link = NULL;

    if (q->rear != NULL)
        q->rear->link = newnode;
    q->rear = newnode;

    if (q->first == NULL)
        q->first = newnode;

    return 1;
}

int Pop(queue* q) {
    if (q->first == NULL)
        return QUEUE_EMPTY;

    node* tmp = q->first;
    int result = tmp->value;
    q->first = q->first->link;

    if (q->first == NULL)
        q->rear = NULL;

    return result;
}

void Print(queue* q, process* jobs) {
    node* tmp;

    for (tmp = q->first; tmp->link != NULL; tmp = tmp->link)
        printf("%c ", jobs[tmp->value].name);
    printf("%c\n", jobs[tmp->value].name);
}

bool is_empty(queue* q) {
    if (q->first == NULL)
        return true;
    else
        return false;
}

int Size(queue* q) {
    node* tmp;
    int size = 0;

    for (tmp = q->first; tmp->link; tmp = tmp->link)
        size++;
    return ++size;
}

// For Setting
void Set_remain_time(process* jobs, int cnt) {
    for (int i = 0; i < cnt; i++)
        jobs[i].remain_time = jobs[i].service_time;
}

void Set_completed(process* jobs, int cnt) {
    for (int i = 0; i < cnt; i++)
        jobs[i].completed = 0;
}

void Set_sched(process* jobs, int cnt) {
    for (int i = 0; i < cnt; i++)
        jobs[i].sched = 0;
}

void Set_priority(process* jobs, int cnt) {
    for (int i = 0; i < cnt; i++)
        jobs[i].priority = 0;
}

void Set_time_slice(process* jobs, int cnt) {
    for (int i = 0; i < cnt; i++)
        jobs[i].time_slice = 1;
}

void Set_for_print(process* jobs, int cnt) {
    int total = 0;
    for (int i = 0; i < cnt; i++)
        total += jobs[i].service_time;

    for (int k = 0; k < cnt; k++)
        for (int j = 0; j < total; j++)
            jobs[k].for_print[j] = 0;
}

// For Sorting
void Sorting_priority(queue* q, process* jobs) {
    int tmp_q[MAX_SIZE] = { 0, };
    node* tmp;
    int index;

    // copy q to tmp_q
    for (tmp = q->first, index = 0; tmp->link; tmp = tmp->link, index++)
        tmp_q[index] = tmp->value;
    tmp_q[index++] = tmp->value;

    // tmp_q sorting
    for (int repeat = 1; repeat < index; repeat++)
        for (int k = 0; k < index - repeat; k++)
            if (jobs[tmp_q[k]].priority > jobs[tmp_q[k + 1]].priority) {
                int t = tmp_q[k];
                tmp_q[k] = tmp_q[k + 1];
                tmp_q[k + 1] = t;
            }

    // change the value of q
    for (tmp = q->first, index = 0, index = 0; tmp->link; tmp = tmp->link, index++)
        tmp->value = tmp_q[index];
    tmp->value = tmp_q[index];
}

void Sorting_arrive_time(struct process* jobs, int cnt) {
    original_ordered_jobs = malloc(sizeof(char) * cnt);
    for (int i = 0; i < cnt; i++)
        original_ordered_jobs[i] = jobs[i].name;

    for (int repeat = 1; repeat < cnt; repeat++)
        for (int k = 0; k < cnt - repeat; k++)
            if (jobs[k].arrive_time > jobs[k + 1].arrive_time) {
                struct process tmp = jobs[k];
                jobs[k] = jobs[k + 1];
                jobs[k + 1] = tmp;
            }
    return;
}

// For Scheduling Algorithms
void use_FCFS(struct process* jobs, int cnt) {
    printf("\t\t<FCFS>\n");

    Set_remain_time(jobs, cnt);
    Set_completed(jobs, cnt);
    Set_for_print(jobs, cnt);

    int time = jobs[0].arrive_time; // initialize the time
    double ATT = 0.0, ART = 0.0;
    int total_time = 0;

    for (int i = 0; i < cnt; i++) {
        jobs[i].firstTurn_time = time;
        jobs[i].response_time = jobs[i].firstTurn_time - jobs[i].arrive_time;
        time += jobs[i].service_time;
        jobs[i].completion_time = time;
        jobs[i].turnaround_time = jobs[i].completion_time - jobs[i].arrive_time;

        for (int m = jobs[i].firstTurn_time; m < jobs[i].completion_time; m++)
            jobs[i].for_print[m] = 1;
    }

    // for ART, ATT
    for (int j = 0; j < cnt; j++) {
        ATT += (double)jobs[j].turnaround_time;
        ART += (double)jobs[j].response_time;
        total_time += jobs[j].service_time;
    }
    ATT /= cnt;
    ART /= cnt;

    // print processing
    for (int k = 0; k < cnt; k++) {
        printf("%c ", jobs[k].name);
        for (int l = 0; l < total_time; l++) {
            if (jobs[k].for_print[l] == 1)
                printf(" ■");
            else
                printf(" □");
        }
        printf("\n");
    }
    // printf ATT, ART
    printf("**average turnaround time of FCFS: %.2lf\n", ATT);
    printf("**average response time of FCFS: %.2lf\n", ART);

    printf("\n\n");
}

void use_SJF(struct process* jobs, int cnt) {
    printf("\t\t<SJF>\n");

    Set_remain_time(jobs, cnt);
    Set_sched(jobs, cnt);
    Set_completed(jobs, cnt);
    Set_for_print(jobs, cnt);

    int remain_jobs = cnt;
    int current_time;
    int flag;
    int* ready_queue = malloc(sizeof(int) * cnt); // dynamic allocation for the ready queue
    double ATT = 0.0, ART = 0.0;
    int total_time = 0;

    // execution starts
    for (current_time = 0; remain_jobs != 0; current_time++) {
        // Set the array value to -1
        for (int i = 0; i < cnt; i++)
            ready_queue[i] = -1;

        flag = 0; // it shows if there is newly arrived job in the ready queue
        for (int i = 0; i < cnt; i++)
            if (jobs[i].arrive_time <= current_time && jobs[i].completed != 1) {
                flag++;
                ready_queue[i] = i;
            }

        if (flag == 0) continue;

        else { // when there are 2 or more than 2 jobs in the ready queue
            int index; // executing job's index
            int shortest_time = 9999; // it holds the shortest time

            // find the job that has the shortest service_time in the ready queue
            for (int m = 0; m < cnt; m++)
                if (ready_queue[m] != -1 && jobs[ready_queue[m]].service_time < shortest_time) {
                    shortest_time = jobs[ready_queue[m]].service_time;
                    index = m;
                }

            //printf("process %c\t%d worked\tdone\n", jobs[index].name, jobs[index].service_time);
            jobs[index].firstTurn_time = current_time;
            jobs[index].response_time = jobs[index].firstTurn_time - jobs[index].arrive_time;
            current_time += jobs[index].service_time;
            jobs[index].completion_time = current_time;
            jobs[index].turnaround_time = jobs[index].completion_time - jobs[index].arrive_time;
            jobs[index].completed = 1;

            for (int k = jobs[index].firstTurn_time; k < jobs[index].completion_time; k++)
                jobs[index].for_print[k] = 1;

            current_time--; // (quantum - 1) because current_time will be incremented in the for loop header
            remain_jobs--;
        }
    } // execution ends

    for (int j = 0; j < cnt; j++) {
        ATT += (double)jobs[j].turnaround_time;
        ART += (double)jobs[j].response_time;
        total_time += jobs[j].service_time;
    }
    ATT /= cnt;
    ART /= cnt;
    // print processing
    for (int i = 0; i < cnt; i++) {
        printf("%c ", jobs[i].name);
        for (int j = 0; j < total_time; j++) {
            if (jobs[i].for_print[j] == 1)
                printf(" ■");
            else
                printf(" □");
            //printf(" %d", jobs[i].for_print[j]);
        }
        printf("\n");
    }
    printf("**average turnaround time of SJF: %.2lf\n", ATT);
    printf("**average response time of SJF: %.2lf\n", ART);
    printf("\n\n");
}

void use_RR(struct process* jobs, int cnt, int quantum) {
    printf("\t\t<RR: qauntum = %d>\n", quantum);

    Set_remain_time(jobs, cnt);
    Set_completed(jobs, cnt);
    Set_sched(jobs, cnt);
    Set_for_print(jobs, cnt);

    int remain_jobs = cnt;
    int current_time;
    int* ready_queue = malloc(sizeof(int) * MAX_SIZE); // dynamic allocation for ready queue
    int flag; // flag checks if any job is added to ready queue
    int is_first = 1; // 1 means it's first round, 0 menas it's over second round
    int index; // index holds the last scheduled job's index
    double ATT = 0.0, ART = 0.0;
    int total_time = 0;

    // execution starts
    for (current_time = 0; remain_jobs != 0; current_time++) {
        //printf("\n\ncurrent_time: %d\n", current_time);
        flag = 0;
        for (int i = 0; i < cnt; i++) {
            if (RR_is_exist(ready_queue, i) == 1) // if the jobs already exists in the ready queue
                continue; // skip this job

            /* if a job (1) arrived earlier than the current time, (2) didn't complete, and (3) has never scheduled before,
            add it to the ready queue */
            if (jobs[i].arrive_time <= current_time && jobs[i].completed != 1 && jobs[i].sched == 0) {
                flag++; // a job has added to the ready queue
                RR_Push(ready_queue, i);
            }
        }

        if (is_first != 1) { // if it's not the first round
            if (jobs[index].completed != 1) // If the last scheduled job was not completed
                RR_Push(ready_queue, index); // add it to the ready queue again
            flag++; // a job has added to the ready queue
        }

        if (flag == 0) // if nothing was added to the ready queue
            continue; // move to increment in for loop header (current_time++)

        //printf("Before ready queue: ");
        //print(ready_queue);

        index = RR_Pop(ready_queue);

        // for ART
        if (jobs[index].sched == 0) {
            jobs[index].firstTurn_time = current_time;
            jobs[index].response_time = jobs[index].firstTurn_time - jobs[index].arrive_time;
        }

        // 1) if the job's remain_time is longer than time slice
        int now = current_time; // to capture the time when the job scheduled
        if (jobs[index].remain_time > quantum) {
            jobs[index].remain_time -= quantum;
            //printf("process %c\t%d worked\t%d left\n", jobs[index].name, quantum, jobs[index].remain_time);
            current_time += (quantum - 1); // (quantum - 1) because current_time will be incremented in the for loop header

            // for print
            for (int k = now; k < (current_time + 1); k++)
                jobs[index].for_print[k] = 1;
        }
        else { // 2) if the job's remain_time is shorter than time slice
            //printf("process %c\t%d worked\tdone\n", jobs[index].name, jobs[index].remain_time);
            current_time += (jobs[index].remain_time - 1); // same reason above
            jobs[index].remain_time = 0;
            jobs[index].completed = 1; // 1 means it's completed
            remain_jobs--; // discount remain_jobs

            // for ATT
            jobs[index].completion_time = (current_time + 1); // the real current_time is needed to be added 1
            jobs[index].turnaround_time = jobs[index].completion_time - jobs[index].arrive_time;

            //for print
            for (int k = now; k < jobs[index].completion_time; k++)
                jobs[index].for_print[k] = 1;
        }
        jobs[index].sched++; // mark that this job has scheduled before
        is_first = 0; // mark that it's not the first round anymore
    } // execution ends

    for (int j = 0; j < cnt; j++) {
        ATT += (double)jobs[j].turnaround_time;
        ART += (double)jobs[j].response_time;
        total_time += jobs[j].service_time;
    }
    ATT /= cnt;
    ART /= cnt;

    // print processing
    for (int i = 0; i < cnt; i++) {
        printf("%c ", jobs[i].name);
        for (int j = 0; j < total_time; j++) {
            if (jobs[i].for_print[j] == 1)
                printf(" ■");
            else
                printf(" □");
            //printf(" %d", jobs[i].for_print[j]);
        }
        printf("\n");
    }
    printf("**average turnaround time of RR: %.2lf\n", ATT);
    printf("**average response time of RR: %.2lf\n", ART);
    printf("\n\n");
}

void use_MLFQ(struct process* jobs, int cnt, int quantum) {
    printf("\t\t<MLFQ: qauntum = %d*i>\n", quantum);

    Set_remain_time(jobs, cnt);
    Set_completed(jobs, cnt);
    Set_sched(jobs, cnt);
    Set_priority(jobs, cnt);
    Set_time_slice(jobs, cnt);
    Set_for_print(jobs, cnt);

    int remain_jobs = cnt;
    int current_time;
    int is_first = 1;
    int index, original_priority;
    queue ready_queue;
    init_queue(&ready_queue);
    double ATT = 0.0, ART = 0.0;
    int total_time = 0;

    for (current_time = 0; remain_jobs != 0; current_time++) {
        for (int i = 0; i < cnt; i++) { // Check if there are newly arrived jobs
            if (jobs[i].arrive_time <= current_time && jobs[i].completed != 1 && jobs[i].sched == 0)
                Push(&ready_queue, i);
        }

        if (is_first != 1) { // if it's not the first round
            if (jobs[index].completed != 1) { // check if the job that just scheduled is completed
                if (is_empty(&ready_queue) != true) { // if the ready queue is not empty
                    jobs[index].priority++; // lower the priority of the job
                    jobs[index].time_slice *= quantum; // increate the time slice
                }
                Push(&ready_queue, index); // put the job back in the queue
                //printf("\tpriority: %d → %d\n", original_priority, jobs[index].priority);
            }
        }

        // if the ready queue is empty, move to increment in for loop header (current_time++)
        if (is_empty(&ready_queue)) continue;

        // Sort the jobs in the ready queue by priority
        Sorting_priority(&ready_queue, jobs);

        index = Pop(&ready_queue); // index means the scheduling job's index
        original_priority = jobs[index].priority; // capture the original priority of the job

        // for ART
        if (jobs[index].sched == 0) { // if it's the first scheduling
            jobs[index].firstTurn_time = current_time; // mark the first scheduled time
            jobs[index].response_time = jobs[index].firstTurn_time - jobs[index].arrive_time; // calculate the response time
        }

        // 1) if the job's remain_time is longer than time slice
        int now = current_time; // to capture the time when the job scheduled
        if (jobs[index].remain_time > jobs[index].time_slice) {
            jobs[index].remain_time -= jobs[index].time_slice;
            //printf("process %c\t%d worked\t%d left", jobs[index].name, jobs[index].time_slice, jobs[index].remain_time);
            current_time += (jobs[index].time_slice - 1);

            // for print
            for (int k = now; k < (current_time + 1); k++)
                jobs[index].for_print[k] = 1;
        }
        else { // 2) if the job's remain_time is shorter than time slice
            current_time += (jobs[index].remain_time - 1);
            //printf("process %c\t%d worked\tdone", jobs[index].name, jobs[index].remain_time);
            jobs[index].remain_time = 0;
            jobs[index].completed = 1;
            jobs[index].priority = -1;
            remain_jobs--;
            //printf("\tpriority: %d → %d\n", original_priority, jobs[index].priority);

            // for ATT
            jobs[index].completion_time = (current_time + 1); // check the time when the jobs has completed
            jobs[index].turnaround_time = jobs[index].completion_time - jobs[index].arrive_time; // calculate the turnaround time


            // for print
            for (int k = now; k < jobs[index].completion_time; k++)
                jobs[index].for_print[k] = 1;
        }

        jobs[index].sched++;
        is_first = 0; // not the first round any more
    }

    for (int j = 0; j < cnt; j++) {
        ATT += (double)jobs[j].turnaround_time;
        ART += (double)jobs[j].response_time;
        total_time += jobs[j].service_time;
    }
    ATT /= cnt;
    ART /= cnt;

    // print processing
    for (int i = 0; i < cnt; i++) {
        printf("%c ", jobs[i].name);
        for (int j = 0; j < total_time; j++) {
            if (jobs[i].for_print[j] == 1)
                printf(" ■");
            else
                printf(" □");
            //printf(" %d", jobs[i].for_print[j]);
        }
        printf("\n");
    }
    printf("**average turnaround time of MLFQ (time slice = %d*i): %.2lf\n", quantum, ATT);
    printf("**average response time of MLFQ (time slice = %d*i): %.2lf\n", quantum, ART);
    printf("\n\n");
}
