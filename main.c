#include <stdio.h>
#include <stdlib.h>
#include "bqueue.h"

bQueue q = NULL;

void thread_put()
{
	printf("Sleep for 10 second before put 16 items \n");
	sleep(10);
	int i = 0;
	for (i=0;i<16;i++)
	{
		char * buffer = "hello world\n";
		bqueue_put(q,buffer,strlen(buffer)+1);
	}


	printf("Sleep for 10 second before put 128 items \n");
	sleep(10);
	for (i=0;i<128;i++)
	{
		char * buffer = "hello world\n";
		bqueue_put(q,buffer,strlen(buffer)+1);
	}


}
void thread_get()
{
	int i = 0;
	int * tmp = NULL;
	for (i=0;i<16;i++)
	{
		printf("Get iteration :%d",i);
		char * tmp = (char * ) bqueue_get(q);
		if (tmp)
		{
			printf(" : %s",tmp);
			free(tmp);
			tmp = NULL;
		}
		else
			printf(" NULL \n");
	}
	printf ("task Done for thread_put\n");
}

int main()
{
	List l = NULL;
	list_init(&l);

	int i = 0;
	for (i=0;i<16;i++)
	{
		list_insert_tail(&l,&i,sizeof(int));
	}
	
	list_transverse(l,print_int_element);
	list_destroy(&l);
	bqueue_init(&q,100);

	pthread_t t1;
	pthread_t t2;
	pthread_create(&t1,NULL,thread_put,NULL);		
	pthread_create(&t2,NULL,thread_get,NULL);		

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;

}
