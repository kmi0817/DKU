/*
*	DKU Operating System Lab
*	    Lab1 (Scheduler Algorithm Simulator)
*	    Student id : 32191556
*	    Student name : 박경미 (Park Kyungmi)
*
*   lab1_sched.c :
*       - Lab1 source file.
*       - Must contains scueduler algorithm test code.
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

#include "lab1_sched_types.h"

/*
 * you need to implement scheduler simlator test code.
 *
 */

int main(int argc, char *argv[]){
    int cnt;
    struct process jobs[MAX_SIZE];
    char name;
    int arrive, service;

    if (argc < 2) {
	    printf("Usage: command the_#_of_process\n");
	    exit(-1);
    }
    cnt = atoi(argv[1]); // the # of jobs

    for (int i = 0; i < cnt; i++) {
        printf("name: ");
        scanf(" %c", &name);
        printf("arrival time: ");
        scanf("%d", &arrive);
        printf("servie time: ");
        scanf("%d", &service);

        jobs[i].name = name;
        jobs[i].arrive_time = arrive;
        jobs[i].service_time = service;
        printf("\n");
    }

    for (int i = 0; i < cnt; i++)
        printf("name: %c, arrive: %d, service: %d\n", jobs[i].name, jobs[i].arrive_time, jobs[i].service_time);

    Sorting_arrive_time(jobs, cnt);

    use_FCFS(jobs, cnt);
    use_SJF(jobs, cnt);
    use_RR(jobs, cnt, 1);
    use_RR(jobs, cnt, 4);
    use_MLFQ(jobs, cnt, 1);
    use_MLFQ(jobs, cnt, 2);
}
