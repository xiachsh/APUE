#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include <pthread.h>


pthread_spinlock_t spin;


/*
after launch the thread you can use top to see 
the usage of cpu
*/

void * fn(void * args)
{
	int * ret = malloc(sizeof(int));
	pthread_spin_lock(&spin);
	printf("FILE: %s Line: %d in\n",__FILE__,__LINE__);
	printf("get spin lock and sleep for 30 secs\n");
	sleep(30);
	pthread_spin_unlock(&spin);	
	*ret = 0;
	return ret;
}


int main()
{

	int * ret = NULL;
	pthread_t tid1;
	pthread_t tid2;



	pthread_spin_init(&spin,PTHREAD_PROCESS_SHARED);
	pthread_create(&tid1,NULL,fn,NULL);
	pthread_create(&tid1,NULL,fn,NULL);


	pthread_join(tid1,&ret);
	printf("thread tid1 exit with exit code %d\n",*(int*)ret);
	pthread_join(tid2,&ret);
	printf("thread tid2 exit with exit code %d\n",*(int*)ret);

	return 0;
}
