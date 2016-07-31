#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <getopt.h>


typedef struct _maxComb {
	int sum;
	int start;
	int end;
} maxComb;


void print_arr(int * buffer,int len)
{
	int i = 0;
	for (i = 0;i < len;i++){
		fprintf(stdout,"%d\t",*(buffer+i));
	}
	fprintf(stdout,"\n");
}


maxComb find_maxSeqSum(int *buf,int len)
{
	int i = 0;
	int j ;
	int sum = 0;	
	maxComb max = {0,-1,-1};
	
	for(i=0;i<len;i++) {
	sum = 0;
	for (j=i;j<len;j++) {
		sum = sum + buf[j];		
		if (sum > max.sum) {
			max.sum = sum;
			max.start = i;
			max.end = j;
		}
	}

	}
	return max;
}

int find_maxSeqSum_2(int *buffer,int len)
{
	int maxSum = 0 ;
	int sumEnding = 0;
	int start = 0 ;
	int end = 0 ;
	int i = 0;
	for (i = 0;i<len;i++){
		if (sumEnding >0) 
			sumEnding += *(buffer+i);
		else 
			sumEnding = *(buffer+i);
			start = i;
		if (sumEnding > maxSum){
			maxSum = sumEnding;
			end = i;
		}
	}
	return maxSum;
}

void usage(int argc,char ** argv)
{
	fprintf(stderr,"%s usage:\n",argv[0]);
	fprintf(stderr,"	%s -n num\n",argv[0]);
	exit(1);
}

int main(int argc,char ** argv)
{	
	int c;
	int num;

	if (argc < 2) 
		usage(argc,argv);
	while ( (c=getopt(argc,argv,"n:")) != -1 ){
		switch (c){
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
	int buffer[num];
	int i = 0;
	int positive;
	for (i = 0;i < num;i++){
		positive = rand() % 2;
		buffer[i]  = rand() % 100;
		buffer[i] = positive ? buffer[i] : 0-buffer[i];
	}

//	print_arr(buffer,num);

	maxComb max = find_maxSeqSum(buffer,num);
	int maxInt = find_maxSeqSum_2(buffer,num);
	fprintf(stdout,"sum:%d start:%d end:%d\n",max.sum,max.start,max.end);
	fprintf(stdout,"sum:%d\n",maxInt);
}
