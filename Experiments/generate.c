#include "stdio.h"
#include "stdlib.h"
#include "assert.h"


#define BUFSIZE  4

int main()
{
	printf("sizeof(unsigned) = %u\n\n", sizeof(unsigned));
	int buf[BUFSIZE] = {};
	
	for (int i = 0; i < BUFSIZE; i++)
	{
		scanf("%u", buf + i);
	}	

	FILE* output = fopen("output.bin", "wb");

	int cond = fwrite(buf, sizeof(int), BUFSIZE, output);

	assert(cond == BUFSIZE);
	fclose(output);
	return 0;
}