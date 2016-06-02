#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <strings.h>



#define DEFAULT_ELEMS 16

typedef struct _bstNode {
	int data;
	struct _bstNode * left;
	struct _bstNode * right;
} BstNode, * BstTree;



void bst_insert(BstTree * tPtr,int val)
{
	if ((*tPtr) == NULL) {
		*tPtr = malloc(sizeof(BstNode));
		(*tPtr)->data = val;
		(*tPtr)->left = (*tPtr)->right = NULL;
	}
	else if ((*tPtr)->data > val) 
		bst_insert(&((*tPtr)->left),val);
	else if ((*tPtr)->data < val) 
		bst_insert(&((*tPtr)->right),val);
	else {
		fprintf(stderr,"duplicat key %d,Skipped\n",val);
	}
}

void delete_key(BstTree * tPtr,int key)
{


}

void bst_destroy(BstTree * tPtr)
{
	if (*tPtr){
		bst_destroy(&((*tPtr)->left));
		bst_destroy(&((*tPtr)->right));
		free(*tPtr);
		*tPtr = NULL;
	}
}


void postorder_iterative_traversal(BstTree tree,int max)
{
	int index = 0;
	BstTree t_arr[max];
	bzero(t_arr,sizeof(BstTree)*max);
	BstTree cur = tree;
	BstTree previsited = NULL;
	while ( cur != NULL || index >=1 )
	{
		while (cur != NULL){
			t_arr[index++] = cur;
			cur = cur->left;
		}
		cur = t_arr[index-1];
		if (cur->right == NULL | cur->right == previsited){
			fprintf(stdout,"Address:%8lx Val:%4d Left:%8lx Right:%8lx\n",cur,cur->data,cur->left,cur->right);	
			previsited = cur;
			index--;
			cur = NULL;	
		}
		else cur = cur->right;
	}
}

void preorder_iterative_traversal(BstTree tree,int max)
{
	int index = 0 ;
	BstTree t_arr[max];
	bzero(t_arr,sizeof(BstTree)*max);
	BstTree cur = tree;
	
	while ( cur ) {
		fprintf(stdout,"Address:%8lx Val:%4d Left:%8lx Right:%8lx\n",cur,cur->data,cur->left,cur->right);	
		if (cur->right) t_arr[index++] = cur->right;
		if (cur->left)  {
			cur = cur->left;
			continue;
		}
		else {
			if (index<1)  break;
 	                cur = t_arr[--index];
                }
	}
}

void inorder_iterative_traversal(BstTree tree,int max)
{
	int index = 0 ;
	BstTree t_arr[max];
	bzero(t_arr,sizeof(BstTree)*max);
	BstTree cur = tree;
	int topDown = 1;

	while (cur || index>=1) {
		while (cur && topDown) {
			t_arr[index++] = cur;
			cur = cur->left;
			 topDown = 1;	
		}
		if (index<1) break;
		cur = t_arr[--index];
		fprintf(stdout,"Address:%8lx Val:%4d Left:%8lx Right:%8lx\n",cur,cur->data,cur->left,cur->right);	
                if (cur->right) {
			cur=cur->right;
			topDown = 1;
			continue;
		}
		topDown = 0;
	}
}



void inorder_recursive_traversal(BstTree tree)
{
	if (tree) {
		inorder_recursive_traversal(tree->left);
		fprintf(stdout,"Address:%8lx Val:%4d Left:%8lx Right:%8lx\n",tree,tree->data,tree->left,tree->right);	
		inorder_recursive_traversal(tree->right);
	}
}

void usage(int argc,char ** argv)
{
	fprintf(stderr,"%s Usage:\n",argv[0]);
	fprintf(stderr,"	:%s -n num    num | num of elements\n",argv[0]);
	exit(1);
}

int main(int argc,char ** argv)
{
	int c = 0;
	int num ;
	int i ;
	BstTree tree = NULL;
	if (argc == 1) usage(argc,argv);
	while( (c=getopt(argc,argv,"n:")) != -1 ) {
		switch (c) {
			case 'n':
				if (!isdigit(optarg[0]))
					usage(argc,argv);
				num = atoi(optarg);
				break;
			default:
				usage(argc,argv);
				break;
		}
	}

	for (i=0;i<num;i++) 
		bst_insert(&tree,rand()%1000);
	inorder_recursive_traversal(tree);
	fprintf(stdout,"beatiful seperator LOL\n");
	inorder_iterative_traversal(tree,num);
	fprintf(stdout,"beatiful seperator LOL\n");
	preorder_iterative_traversal(tree,num);
	fprintf(stdout,"beatiful seperator LOL\n");
	postorder_iterative_traversal(tree,num);
	bst_destroy(&tree);	

} 
