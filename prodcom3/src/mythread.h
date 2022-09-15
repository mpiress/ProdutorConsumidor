#ifndef MYTHREAD_H 
#define MYTHREAD_H

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>



#define NUMCONS 2
#define NUMPROD 2
#define BUFFERSIZE 1000

#define TRUE 1
#define FALSE 0

typedef struct {

/* This structure is passed to the threads and contains all necessary
   information for computations */

  	int buffer[BUFFERSIZE];
	int currentidx;
	pthread_mutex_t buffer_mutex;
	sem_t buffer_full;
	sem_t buffer_empty;


}estrutura_global;


void *consumidor(void *arg);
void *produtor(void *arg);

#endif
