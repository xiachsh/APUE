#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>



int main()
{

 char str[100] = "xxx:yyy:zzz::";

 char * token;

 token = strtok(str,":");
 while ( token != NULL ) {
 	
 	printf("%s\n",token);
	token = strtok(NULL,":");
}
	return 0;
}
