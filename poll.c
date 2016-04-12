#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>

#include <getopt.h>
#define PAGE_SIZE getpagesize()

extern char *optarg;


static int pipefds_0[2];
static int pipefds_1[2];
static int pipefds_2[2];
static int itr = 10;
static int t = 2; 


void work()
{
	char buffer[PAGE_SIZE+1];
	int i = 0;
	pid_t pid = getpid();
	int fd;	
	if ( (pid % 3) == 0 )
	{
		close( pipefds_0[0]);
		
		close( pipefds_1[0]);
		close( pipefds_1[1]);
		close( pipefds_2[0]);
		close( pipefds_2[1]);
		fd = pipefds_0[1];
	}
	else if ( (pid % 3) == 1 )
	{
		
		close( pipefds_0[0]);
		close( pipefds_0[1]);
		
		close( pipefds_1[0]);

		close( pipefds_2[0]);
		close( pipefds_2[1]);
		fd = pipefds_1[1];

	}
	else
	{

		close( pipefds_0[0]);
		close( pipefds_0[1]);
		close( pipefds_1[0]);
		close( pipefds_1[1]);

		close( pipefds_2[0]);
		fd = pipefds_2[1];
	}
	
	while (i<itr)
	{
		sprintf(buffer,"hello world from child pid %d itr: %d pipe %d\n",pid,i,pid % 3);
		write(fd,buffer,strlen(buffer));
		sleep(pid % 3);
		i++;
	}
	close(fd);
	exit(0);
}

void usage(int argc,char ** argv)
{	
	printf("%s usage:\n",argv[0]);
	printf("	 -i itr iteration of message\n");
	printf("	 -t processes num of process\n");
	exit (EXIT_FAILURE);
}

int main(int argc,char ** argv)
{
	int c;
	char buffer[PAGE_SIZE+1];
	pid_t pid;
	int i = 0;
	struct pollfd fds[3];

	while ( (c = getopt(argc,argv,"i:t:")) != -1 )
	{
		switch (c)
		{
			case 'i':	
				if ( ! isdigit(optarg[0]) )
				{
					printf("the argument you input is no digit,exiting\n");
					usage(argc,argv);
				}
				itr = atoi(optarg);	
				break;
			case 't':
				if ( ! isdigit(optarg[0]) )
				{
					printf("the argument you input is no digit,exiting\n");
					usage(argc,argv);
				}
				t = atoi(optarg);
				break;
			default:
				usage(argc,argv);
				break;
		}
	} 	
	memset(buffer,'\0',PAGE_SIZE+1);
	if ( pipe(pipefds_0)<0 )
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if ( pipe(pipefds_1)<0 )
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if ( pipe(pipefds_2)<0 )
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	for (i=0;i<t;i++)
	{

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			work();
		}
	}	

	close(pipefds_0[1]);	
	close(pipefds_1[1]);	
	close(pipefds_2[1]);	


	fds[0].fd = pipefds_0[0];
	fds[0].events = POLLIN;
	fds[1].fd = pipefds_1[0];
	fds[1].events = POLLIN;
	fds[2].fd = pipefds_2[0];
	fds[2].events = POLLIN;
	
	while(1)
	{
		int i = 0;
		int ret = poll(fds,3,0);
		int b = 0;
		if (ret == -1)
			break;
		for (i=0;i<3;i++)
		{
			if (fds[i].revents ==  POLLIN)
			{
				if (	read(fds[i].fd,buffer,PAGE_SIZE) > 0)
				printf("%s",buffer);
			}
			if (fds[i].revents == POLLHUP)
				b++;
			if (b==2)goto exit;
				
		}

	}

exit:
	exit(0);
}
