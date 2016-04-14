#include <stdio.h>
#include <stdlib.h>
#include "bqueue.h"

bQueue q = NULL;


int main()
{
	List l = NULL;
	list_init(&l);

	int i = 0;
	bqueue_init(&q,100);

	char * buffer = NULL;
        for (i=0;i<16;i++)
        {
		printf("Iteration :%d\n",i);
               buffer = bqueue_get(q);
		printf("return from bq_get\n");
		if (buffer)
		{
			printf("%s",buffer);
			free(buffer);
			buffer = NULL;
		}
        }


	return 0;
}
