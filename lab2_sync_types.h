/*
*   DKU Operating System Lab
*           Lab2 (Vehicle Production Problem)
*           Student id : 32191556
*           Student name :Park kyungmi
*
*   lab1_sync_types.h :
*       - lab2 header file.
*       - must contains Vehicle Production Problem's declations.
*
*/

#ifndef _LAB2_HEADER_H
#define _LAB2_HEADER_H

#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <limits.h>

#define QUEUE_EMPTY INT_MIN
#define MAX_SIZE 100

/*
 * You need to Declare functions in  here
 */

typedef struct Node {
	int value;
	struct Node *next;
}Node;

typedef struct car_queue {
	int balance;
	Node *front, *rear;
//	pthread_mutex_t frontLock;
//	pthread_mutex_t rearLock;
}CQ;

void init_Queue(CQ* q) {
	q->balance = 0;
	q->front = NULL;
	q->rear = NULL;
//	pthread_mutex_init(&q->frontLock, NULL);
//	pthread_mutex_init(&q->rearLock, NULL);
}

void put(CQ* q, int item) {
	Node* tmp = malloc(sizeof(Node));
	assert(tmp != NULL);

	tmp->value = item;
	tmp->next = NULL;

//	pthread_mutex_lock(&q->rearLock);
	if (q->rear != NULL)
		q->rear->next = tmp;
	q->rear = tmp;

	if (q->front == NULL)
		q->front = tmp;

	q->balance++;
//	pthread_mutex_unlock(&q->rearLock);

	return;
}

int get(CQ* q) {
	if (q->front == NULL)
		return QUEUE_EMPTY;

//	pthread_mutex_lock(&q->frontLock);
	Node* tmp = q->front;
	int result = tmp->value;
	q->front = q->front->next;

	if (q->front == NULL) {
		q->rear = NULL;
	}

	q->balance--;
//	pthread_mutex_unlock(&q->frontLock);
	free(tmp);
	return result;
}
// Queue ends


#endif /* LAB2_HEADER_H*/

