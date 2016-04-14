#ifndef __BQUEUE__
#define __BQUEUE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef void (*fnt) (void * data);
typedef struct _listNode
{
	void * data;
	struct _listNode* next;
} ListNode, * List;


typedef struct _bqueue
{
	int max;
	int size;
	pthread_mutex_t m_size;
	pthread_cond_t c_empty;
	pthread_cond_t c_full; 
	List l;
} * bQueue;

void list_destroy(List *l)
{
	List cur = (*l);
	List tmp;
	while (cur)
	{
		tmp = cur;
		cur=cur->next;
		free(tmp->data);
		tmp->data = NULL;
		free(tmp);
	}
	*l = NULL;
}

void list_init(List *l)
{
	list_destroy(l);
}

void list_insert_tail(List *l,void * data,int len)
{
	ListNode * node = malloc(sizeof(ListNode));
	node->data = malloc(sizeof(char) * len);
	node->next = NULL;
	memcpy(node->data,data,len);
	
 	List cur = (*l);
	if (cur)
	{
		while (cur->next)
		{
			cur=cur->next;
		}				
		cur->next = node;
	}
	else
	{
		*l = node;		
	}
}

void * list_remove_head(List *l)
{
	void * point ;
	List node = (*l);
	if (node)
	{
		point = node->data;	
		*l = node->next;
		free(node);
	}
	else
		point = NULL;
	return point;

} 
void list_transverse(List l,fnt function)
{
	List node = l;
	while(node)
	{
		function(node->data);
		node = node->next;
	}
	printf("\n");
}

void print_int_element(void *data)
{
	int * tmp = (int*) data;
	printf("%d\t",*tmp);
}



void bqueue_init(bQueue *q,int max)
{
	struct _bqueue * tmp = malloc(sizeof (struct _bqueue) );		
	tmp->max = max;
	tmp->size = 0;
	tmp->l = NULL;
	pthread_mutex_init(&(tmp->m_size),NULL);
	
	pthread_cond_init(&(tmp->c_empty),NULL);
	pthread_cond_init(&(tmp->c_full),NULL);

	/*
	tmp->c_empty = PTHREAD_COND_INITIALIZER;
	tmp->c_full = PTHREAD_COND_INITIALIZER;
	*/

	list_init(&(tmp->l));

	*q = tmp;
}


void bqueue_destroy(bQueue *q)
{
	pthread_mutex_lock( & ((*q)->m_size) );
	list_destroy(&((*q)->l));
	pthread_mutex_unlock( & ((*q)->m_size) );
}

void bqueue_put(bQueue q,void * data,int len)
{
	pthread_mutex_lock(&(q->m_size));
	if (q->size >= q->max)
		pthread_cond_wait(&(q->c_full),&(q->m_size));
	list_insert_tail(&(q->l), data, len);	
	q->size++;
	if (q->size==1)
		pthread_cond_broadcast(&(q->c_empty));	
	pthread_mutex_unlock(&(q->m_size));
}

void * bqueue_get(bQueue q)
{
	void * point ;
	pthread_mutex_lock(&(q->m_size));
	if (q->size <= 0)
		pthread_cond_wait(&(q->c_empty),&(q->m_size));
	point = list_remove_head(&(q->l));
	q->size--;
	if (q->size == ((q->max)-1) )
		pthread_cond_broadcast(&(q->c_full));
	pthread_mutex_unlock(&(q->m_size));
	return point;
}



#endif
