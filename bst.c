#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <getopt.h>

typedef struct _bstNode {
	int val;
	struct _bstNode * left;
	struct _bstNode * right;
} BstNode, *BstTree;



void bst_insert(BstTree *tPtr,int val)
{
 	if (!*tPtr) {
		BstTree tree = *tPtr = malloc(sizeof(BstNode));
		tree->val = val;
		tree->left = tree->right = NULL;
	}
	else if((*tPtr)->val > val) {
		bst_insert( &((*tPtr)->left),val);
	}
	else if ((*tPtr)->val < val) {
		bst_insert( &((*tPtr)->right),val);
	}
	else 
		fprintf(stderr,"Duplicate key :%d\n",val);
}

void bst_destroy(BstTree *tPtr)
{
	if (*tPtr) {
		bst_destroy(&((*tPtr)->left));
		bst_destroy(&((*tPtr)->right));
		free(*tPtr);
		*tPtr = NULL;
	}
}

void inOrder_traversal(BstTree tree)
{
	if (tree) {
		inOrder_traversal(tree->left);	
		fprintf(stdout,"Address:%8lx Val:%4d Left:%8lx Right:%8lx\n",tree,tree->val,tree->left,tree->right);
		inOrder_traversal(tree->right);	
	}
}


void postOrder_traversal_i(BstTree tree,int max)
{
	int index = 0 ;
	BstTree cur = tree;
	BstTree tPtr_arr[max];
	bzero(tPtr_arr,sizeof(BstTree)*max);
	BstTree previsited = NULL;	

	while (cur || index >=1) {
		if (cur){
			tPtr_arr[index++] = cur;
			cur=cur->left;
		}
		else {
			cur = tPtr_arr[index-1];
			if (cur->right == NULL || cur->right == previsited){
			fprintf(stdout,"Address:%8lx Val:%4d Left:%8lx Right:%8lx\n",cur,cur->val,cur->left,cur->right);
			index--;
			previsited = cur;
			cur = NULL;
			}
			else 
				cur = cur->right;
		}
	}	
}

void preOrder_traversal_i(BstTree tree,int max)
{
	int index = 0;
	BstTree cur = tree;
	BstTree tPtr_arr[max];
	

	while (cur || index>=1) {
		
		if (!cur) 
			cur = tPtr_arr[--index];
		fprintf(stdout,"Address:%8lx Val:%4d Left:%8lx Right:%8lx\n",cur,cur->val,cur->left,cur->right);
		if (cur->right)
			tPtr_arr[index++] = cur->right;
		cur = cur->left;
	}
}

void inOrder_traversal_i(BstTree tree,int max)
{
	int index = 0;
	BstTree tPtr_arr[max];
	BstTree cur = tree;

	while (cur || index >=1 ){
		if (cur) {
			tPtr_arr[index++] = cur;
			cur = cur->left;
		} 
		else {
			cur = tPtr_arr[--index];	
			fprintf(stdout,"Address:%8lx Val:%4d Left:%8lx Right:%8lx\n",cur,cur->val,cur->left,cur->right);
			cur = cur->right;
		}
	}	
}

void bfs(BstTree tree,int max)
{
	int index = 0 ;
	int len = 0;
	BstTree tPtr_arr[max];
	BstTree tmp;
	bzero(tPtr_arr,sizeof(BstTree) * max);
	tPtr_arr[index++]=tree;
	len = 1;

	int cur_pos = 0;
	while (len >= 1) {
		tmp = tPtr_arr[cur_pos++];
		len--;
		fprintf(stdout,"Address:%8lx Val:%4d Left:%8lx Right:%8lx\n",tmp,tmp->val,tmp->left,tmp->right);
		if (tmp->left) {
			tPtr_arr[index++]=tmp->left;
			len++;
		}
		if (tmp->right) {
			tPtr_arr[index++]=tmp->right;
			len++;
		}
	}
}



void usage(int argc,char ** argv)
{
	fprintf(stderr,"%s usage\n",argv[0]);
	fprintf(stderr,"	%s -n num\n",argv[0]);
	exit(1);
}


int main(int argc,char ** argv)
{
	int num;
	BstTree tree = NULL;
	int c;
	int i;
	if (argc==1)
		usage(argc,argv);		
	while((c=getopt(argc,argv,"n:")) != -1){
		switch(c){
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
		bst_insert(&tree,rand() % 1000);
        inOrder_traversal(tree);		
	fprintf(stdout,"beautifull seperator \n");
        inOrder_traversal_i(tree,num);		
	fprintf(stdout,"beautifull seperator \n");
        preOrder_traversal_i(tree,num);		
	fprintf(stdout,"beautifull seperator \n");
	postOrder_traversal_i(tree,num);
	fprintf(stdout,"beautifull seperator \n");
	bfs(tree,num);
	bst_destroy(&tree);
	return 0 ;
}
