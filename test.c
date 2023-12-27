#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include "dirent.h"
#include "limits.h"
#include <sys/types.h>
# include <fcntl.h>
# define T_BOOL unsigned int
# define TRUE 1
# define FALSE 0

int test(void)
{
	int main;

	main = 2;
	return (main);
}

void print_test(int main)
{
	printf("%d", main);
}

int main(int argc, char **argv, char **envp)
{
	int main;

	main = test();
	print_test(main);
	return(1);
}
