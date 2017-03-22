#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>


int main(int argc,char ** argv)
{
	if (argc != 2) {
		printf("Usage: file\n");
		exit(1);
	}

	struct stat sb;
	int fd_input = open(argv[1],O_RDONLY);
	if (fd_input == -1){
		perror("open");
		exit(1);
	}
	if (fstat(fd_input,&sb) < 0) {
		perror("fstat");
		exit(1);
	}

	
	
	char * buf =  mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fd_input,0);
	if (buf == MAP_FAILED )
		perror("mmap");
	
	printf("%s",buf);
	close(fd_input);
	return 0;
}
