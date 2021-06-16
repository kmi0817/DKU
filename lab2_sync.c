/*
*   DKU Operating System Lab
*           Lab2 (Vehicle production Problem)
*           Student id : 32191556
*           Student name : Park kyungmi
*
*   lab2_sync.c :
*       - lab2 main file.
*       - must contains Vehicle production Problem function's declations.
*
*/

#include <aio.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>

#include "lab2_sync_types.h"

int loops;
int num;
int cLoops = 0;
sem_t empty;
sem_t full;
sem_t mutex;
int item = 0;
int i = 0;
void *producer(void *arg) {
	CQ *q = (CQ *)arg;
	for (; i < loops; i++) {
		sem_wait(&empty);
		sem_wait(&mutex);

		put(q, item);
		printf("produce: %d\n", item++);
		sem_post(&mutex);
		sem_post(&full);
	}
//	printf("\treally produce end\n");
}

void *consumer(void *arg) {
	CQ *q = (CQ *)arg;
	int i, tmp;

	while (cLoops < loops) {
		sem_wait(&full);
		sem_wait(&mutex);
		
		tmp = get(q);
		cLoops++;
		sem_post(&mutex);
		sem_post(&empty);
		printf("\t\tconsume: %d\n",tmp);
	}
//	printf("\treally consume end\n");
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("usage: %s loops #ofThreads\n", argv[0]);
		exit(-1);
	}

	struct timeval startTime, endTime, gap; // for time measure
	
	loops = atoi(argv[1]);
	num = atoi(argv[2]);
//	cLoops = loops;
//	pLoops = loops;

	pthread_t p1[num], c[num];
	
	sem_init(&empty, 0, MAX_SIZE);
	sem_init(&full, 0, 0);
	sem_init(&mutex, 0, 1);

	CQ *qu = (CQ *)malloc(sizeof(CQ));
	init_Queue(qu);
	
	printf("<start> Producer/Consumer Problem\n");
	gettimeofday(&startTime, NULL);
	for(int i = 0; i < num; i++)
		pthread_create(&p1[i], NULL, producer, (void*)qu);
	for (int i = 0; i < num; i++)
		pthread_create(&c[i], NULL, consumer, (void*)qu);
	
	for (int i = 0; i < num; i++)
		pthread_join(p1[i], NULL);
	for (int i = 0; i < num; i++)
		pthread_join(c[i], NULL);
	
	gettimeofday(&endTime, NULL);
	printf("<end> Producer/Consumer Problem\n");

	printf("total produce number = %d\n", loops);
	printf("final balance value = %d\n", qu->balance);
	gap.tv_sec  = endTime.tv_sec - startTime.tv_sec;
	gap.tv_usec = endTime.tv_usec - startTime.tv_usec;
	if (gap.tv_usec < 0) {
		gap.tv_sec = gap.tv_sec - 1;
		gap.tv_usec = gap.tv_usec + 1000000;
	}
	printf("time: %ldsec: %ldusec\n", gap.tv_sec, gap.tv_usec);
	
	return 0;
}

