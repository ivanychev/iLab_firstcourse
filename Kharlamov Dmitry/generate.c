#include "stdio.h"
#include "stdlib.h"


#define BUFSIZE 4

int main()
{
	printf("sizeof(unsigned) = %u\n\n", sizeof(unsigned));
	int buf[BUFSIZE] = {};
	
	for (int i = 0; i < BUFSIZE; i++)
	{
		scanf("%u", buf + i);
	}	

	FILE* output = fopen("output.txt", "w");


	fclose(output);
	return 0;
}