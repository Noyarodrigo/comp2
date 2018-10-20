#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int global=100;
//pthread_mutex_t serie1;
//pthread_mutex_t serie2;
pthread_barrier_t barrera;

void *hilo1(){
	printf("Hola mundo, soy el hilo hilo 1");
	global=200;
	//pthread_mutex_lock(&serie1);
	//pthread_mutex_unlock(&serie2);
	pthread_barrier_wait(&barrera);
	printf("Global: %d\n", global);
	pthread_exit(NULL); //termina este hilo
}

void *hilo2(){
	printf("Hola mundo, soy el hilo hilo 2\n");
	global=300;
	//pthread_mutex_lock(&serie1);
	//pthread_mutex_unlock(&serie2);
	pthread_barrier_wait(&barrera);
	printf("Global: %d\n", global);
	pthread_exit(NULL); //termina este hilo2

}

void *hilo3(){
	printf("Hola mundo, soy el hilo hilo 3\n");
	global=400;
	//pthread_mutex_lock(&serie1);
	//pthread_mutex_unlock(&serie2);
	pthread_barrier_wait(&barrera);
	printf("Global: %d\n", global);
	pthread_exit(NULL); //termina este hilo2

}

int main(int argc, char const *argv[])
{
	printf("Hola mundo, soy el hilo main\n");
	pthread_barrier_init(&barrera,NULL,3);
	pthread_t tid,tid2,tid3; //asigna el espacio de memoria, creo...
	
	pthread_create(&tid, NULL, hilo1,NULL); //crea un hilo y le asigna una funcion
	pthread_create(&tid2, NULL, hilo2, NULL); //crea un hilo y le asigna una funcion
	pthread_create(&tid2, NULL, hilo2, NULL); //crea un hilo y le asigna una funcion

	pthread_join(tid,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	
	printf("Valor final: %d\n",global);
	pthread_exit(NULL); //termina este hilo
	return 0; //cuando ve un return sin importar en que hilo, se termina el proceso general
}