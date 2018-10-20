#include <stdlib.h>
#include <semaphore.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{	
	sem_t sema;
	sem_init(&sema,1,3);
	printf("decremento ... \n");
	sem_wait(&sema);
	printf("decremento ... \n");
	sem_wait(&sema);
	printf("decremento ... \n");
	sem_wait(&sema);
	printf("decremento ... \n");
	sem_wait(&sema);
	printf("decremento ... \n");
	sem_wait(&sema);
	return 0;
}