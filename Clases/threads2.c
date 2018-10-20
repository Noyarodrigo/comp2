#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


void *hilo(void * valor ){
	printf("Hola mundo, soy un nuevo hilo, valor de arg: %d\n",(int)valor);
	pthread_exit(NULL); //termina este hilo
}

int main(int argc, char const *argv[])
{
	int retorno;
	int valor;
	printf("Hola mundo, soy el hilo main\n");
	pthread_t tid[6]; //asigna el espacio de memoria, creo...
	for (valor = 1; valor < 6; ++valor)
	{
		retorno = pthread_create(&tid[valor], NULL, hilo,(void *) valor); //crea un hilo y le asigna una funcion
		if (retorno==0){
		printf("Se creo el hilo %d\n",valor);
		}
	}
	for (valor = 1;valor < 6; valor++)
	{
		pthread_join(tid[valor],NULL); //espera que el hilo tid termine, una vez que termina continua
	}
	printf("Ya terminaron los otros hilos\n");
	pthread_exit(NULL); //termina este hilo
	return 0; //cuando ve un return sin importar en que hilo, se termina el proceso general
}
