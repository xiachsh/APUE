#include <stdio.h>
#include <stdlib.h>

#include "bqueue.h"


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


	bQueue q = NULL;
	bqueue_init(&q,100);
	int x = 0;
	bqueue_get(q,&x);

	return 0;

}
