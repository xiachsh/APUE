#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>

#define THREADS 16

sem_t print_iter;
void thread_func(void * arg)
{
	int i = *((int *) arg);
	pthread_t tid = pthread_self();
	sem_wait(&print_iter);
	printf("hello world :%dth in tid :%ld \n",i,tid);
}


int main(int argc,char **argv)
{
	int i = 0;
	int tmp = 0;
	sem_init(&print_iter,0,0);
	pthread_t threads[THREADS];
	int args[THREADS];
	for (;i<THREADS;i++)
	{
		sem_post(&print_iter);
		args[i] = i;
		pthread_create( &threads[i],NULL,thread_func,&(args[i]));
	}
	for (i=0;i<THREADS;i++)
		pthread_join( threads[i],NULL);
}
