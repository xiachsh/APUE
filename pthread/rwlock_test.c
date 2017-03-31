#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include <pthread.h>



/*
in following function,the rwlock rd can be retrieved twice 
*/

pthread_rwlock_t rd;

void * fn(void * args)
{
	int * ret = malloc(sizeof(int));
	pthread_rwlock_rdlock(&rd);
	printf("FILE: %s Line: %d in\n",__FILE__,__LINE__);
	printf("get spin lock and sleep for 30 secs\n");
	sleep(30);
	pthread_rwlock_unlock(&rd);	
	*ret = 0;
	return ret;
}


int main()
{

	int * ret = NULL;
	pthread_t tid1;
	pthread_t tid2;


	pthread_rwlock_init(&rd,NULL);
	pthread_create(&tid1,NULL,fn,NULL);
	pthread_create(&tid1,NULL,fn,NULL);


	pthread_join(tid1,&ret);
	printf("thread tid1 exit with exit code %d\n",*(int*)ret);
	pthread_join(tid2,&ret);
	printf("thread tid2 exit with exit code %d\n",*(int*)ret);

	return 0;
}
