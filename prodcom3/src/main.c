#include "mythread.h"

int main(){

	pthread_t cons[NUMCONS];
	pthread_t prod[NUMPROD];
	estrutura_global vglobal;

	vglobal.currentidx = 0;
	for(int i=0; i<BUFFERSIZE; i++)
		vglobal.buffer[i] = -1;
	
	pthread_mutex_init(&vglobal.buffer_mutex, NULL);
	sem_init(&vglobal.buffer_full, 0, BUFFERSIZE);
	sem_init(&vglobal.buffer_empty, 0, 0);

	srand(time(NULL));
	
	for(int i=0; i<NUMPROD; i++)
		pthread_create(&(prod[i]), NULL, produtor, &vglobal);

	for(int i=0; i<NUMCONS; i++)
		pthread_create(&(cons[i]), NULL, consumidor, &vglobal);
	
	for(int i=0; i<NUMCONS; i++)
		pthread_join(cons[i], NULL);

	for(int i=0; i<NUMPROD; i++)
		pthread_join(prod[i], NULL);

	return 0;
}