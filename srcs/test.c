//#include "../headers/minishell.h"
//#include "../headers/init.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"

int	ft_keysize(char *envp);

int main(int argc, char **agrv, char **envp)
{
	char *tester;
	char *test;
	int	i;

	tester = "PATH=test moi ca";

	printf("%s", tester + ft_keysize(tester));
	return (1);
}


int	ft_keysize(char *envp)
{
	int i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	return (i + 1);
}