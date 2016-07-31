#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

void permute(char *buffer,int len,char *curBuffer,int selectedElems)
{
	if (selectedElems == len) {
		printf("%s\n",curBuffer);
	}
	else {
		int i = 0;
		for(i=0;i<len&&selectedElems<len;i++) {
			int j = 0 ;
			for (j=0;j<selectedElems;j++) {
				if (curBuffer[j] == buffer[i] )
				 break;
			}
			if (j!=selectedElems) continue;
			curBuffer[selectedElems++] = buffer[i];
			permute(buffer,len,curBuffer,selectedElems);
			selectedElems--;
		}
	}
}


int main()
{
	char buffer[128] = "ABCD";
	char newBuffer[128];
	bzero(newBuffer,128);

	permute(buffer,4,newBuffer,0);


}
