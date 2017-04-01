#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include <string.h>

#include <sys/mman.h>


#define SIZE 1024

int main()
{
	int ret = 0 ;
	void * buffer = malloc(sizeof(int)*SIZE);

	ret = mlock(buffer,SIZE*(sizeof(int)));
	if (ret) {
		perror("mlock");
	}
	munlock(buffer,SIZE*(sizeof(int)));

	return 0;
}
