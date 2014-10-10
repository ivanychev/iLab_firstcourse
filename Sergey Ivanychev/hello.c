#include <stdio.h>
#include <assert.h>


int main(int argc, char** argv)
{
	assert(argv);
	if (argc < 2)
	{
		printf("Hello, World!");
		getchar();
		return 0;
	}
	else
	{
		assert(argv[1]);
		printf("Hello, %s!", argv[1]);
		getchar();
		return 0;
	}
}