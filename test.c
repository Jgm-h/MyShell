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

void mod(char *test)
{
	*test = 1;
}

int main(int argc, char **argv, char **envp)
{
		int	i;
	char *input = malloc(4 * sizeof (char));

	input = "tes";
	mod(input);
	printf("%s", input);
	return(1);
}
