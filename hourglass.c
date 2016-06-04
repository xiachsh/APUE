#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <getopt.h>


int totalNum(int line) 
{
	int i = 1;
	int total = 0;
	for (i=0;i<=line;i++)
		total = 1 + (i-1)*2;	
	return 2*total - 1;
}

int determLineNum(int num)
{
	if (num<=0) return -1;
	int line = 1;
	while (1){
		if (totalNum(line)>=num) return line;
		line++;
	}
}

void print_line(int line,int maxStars)
{
	
	char buf[maxStars];
	bzero(buf,maxStars);
	int charStars = 1 + (line-1)*2;
	int charLeftWhiteSpace = (maxStars - charStars) / 2;
	int i = 0 ;
	int len = 0;
	for (i = 0;i<charLeftWhiteSpace;i++)
		buf[len++] = ' ';
	for (i = 0;i<charStars;i++)
		buf[len++] = '*';
	buf[len]='\0';
	fprintf(stdout,"%s\n",buf);

}

void print_hourglass(int num)
{
	int lines = determLineNum(num);
	int maxStars =  1 + (lines-1)*2;
	int line = lines;
	if (lines >= 1) {
		for (;line >= 1 ;line--)
			print_line(line,maxStars);
		for (line = 2 ;line <= lines ;line++)
			print_line(line,maxStars);
	}	
}

void usage(int argc,char **argv)
{
	fprintf(stderr,"%s usage\n",argv[0]);
	fprintf(stderr,"	%s -n num\n",argv[0]);
	exit(1);
}

int main(int argc,char ** argv)
{
	int num;
	int c;
	if (argc<2) usage(argc,argv);

	while ( (c=getopt(argc,argv,"n:")) != -1){
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
	print_hourglass(num);

	return 0;
}
