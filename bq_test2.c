#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>


#include "bqueue.h"


#define PUT_THREAD_NUM 1
#define GET_THREAD_NUM 4
bQueue q = NULL;
pthread_t tList[GET_THREAD_NUM];

void thread_func(void )
{
	int retVal = 0;
	int tid = pthread_self();
	struct timespec t = {0,10};
	printf("in %s %d tid:%ld\n",__FILE__,__LINE__,tid);
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	while (1) {
     	   int * item = bqueue_get(q);	
	   printf ("\tGet %d from blocking Queue in tid %ld\n",*item,tid);
	   nanosleep(&t,NULL);
	}
	pthread_exit(&retVal);
}


int main()
{
	int i = 0;
	int *retRev = NULL;
	
	bqueue_init(&q,100);	

	for (;i<GET_THREAD_NUM;i++){
		pthread_create(&(tList[i]),NULL,thread_func,NULL);
	}	
	int j = 0;
	for (j=0;j<GET_THREAD_NUM;j++) {
	for (i=0;i<100;i++){
		bqueue_put(q,&i,sizeof(int));
	}
		printf("main thread,had put 100 items into queue,wait for 10 sec");
		sleep(10);
	}


	/*
	for (i=0;i<GET_THREAD_NUM;i++){
		pthread_join(tList[i],&retRev);
		if ((*retRev) == 0) 
			printf("%ld exit successfully\n");
		else 
			printf("%ld exit with non-zero code\n");
	}
	*/
	
	for (i=0;i<GET_THREAD_NUM;i++) {
		pthread_cancel(tList[i]);
	}
	bqueue_destroy(&q);
	return 0;
	
}
