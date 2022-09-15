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
		vglobal->buffer[vglobal->currentidx++] = n;
		printf("Produzindo número: %d\n", n);
		sleep((int) (rand() % 4));
	}
}


void *consumidor(void *arg){
	int n;
	estrutura_global *vglobal =  (estrutura_global*) arg;

	while(TRUE){
		n = vglobal->buffer[--vglobal->currentidx];
		printf("Consumindo número: %d\n", n);
		sleep((int) (rand() % 4));
	}
}

