/*
	Utilizando pthreads para estudos sobre exclusão mútua e sessão crítica.
	Caso de uso: Produtor vs Consumidor 
	Livro base: Sistemas Operacionais Modernos
*/

#include "mythread.h"


void *produtor(void *arg){
	int n;
	estrutura_global *vglobal = (estrutura_global*) arg;

	while(TRUE){
		n = (int) (rand() % 1000);

		sem_wait(&vglobal->buffer_full);
		pthread_mutex_lock(&vglobal->buffer_mutex);
		vglobal->buffer[vglobal->currentidx++] = n;
		pthread_mutex_unlock(&vglobal->buffer_mutex);
		sem_post(&vglobal->buffer_empty);

		printf("Produzindo número: %d\n", n);
		sleep((int) (rand() % 4));
	}
}


void *consumidor(void *arg){
	int n;
	estrutura_global *vglobal =  (estrutura_global*) arg;

	while(TRUE){

		sem_wait(&vglobal->buffer_empty);
		pthread_mutex_lock(&vglobal->buffer_mutex);
		n = vglobal->buffer[--vglobal->currentidx];
		pthread_mutex_unlock(&vglobal->buffer_mutex);
		sem_post(&vglobal->buffer_full);

		printf("Consumindo número: %d\n", n);
		sleep((int) (rand() % 4));
	}
}

