#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>


#define SIZE 1024 * 1024

int main()
{
	int i = 0;
	char * buf = NULL;
	for (i = 0;i < 4096;i++) {
	
		buf = mmap(NULL,SIZE * sizeof(char), PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);
		if (buf == MAP_FAILED) {
			perror("mmap");
			exit(1);
		}
		memset(buf,i%10,SIZE * sizeof(char));
		buf = NULL;
		sleep(1);
		

	}

	return 0;
}
