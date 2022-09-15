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
		pthread_mutex_lock(&vglobal->buffer_mutex);
		vglobal->buffer[vglobal->currentidx++] = n;
		pthread_mutex_unlock(&vglobal->buffer_mutex);
		printf("Produzindo número: %d\n", n);
		sleep((int) (rand() % 4));
	}
}


void *consumidor(void *arg){
	int n;
	estrutura_global *vglobal =  (estrutura_global*) arg;

	while(TRUE){
		pthread_mutex_lock(&vglobal->buffer_mutex);
		n = vglobal->buffer[--vglobal->currentidx];
		pthread_mutex_unlock(&vglobal->buffer_mutex);
		printf("Consumindo número: %d\n", n);
		sleep((int) (rand() % 4));
	}
}

