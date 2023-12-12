//#include "../headers/minishell.h"
//#include "../headers/init.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include "dirent.h"
#include "limits.h"
#include <sys/types.h>
#include "headers/lexer.h"

int	ft_keysize(char *envp);
void	ft_test(char **test);

int main(int argc, char **agrv, char **envp)
{
	/*DIR *tester;
	char *path;
	struct dirent *test;
	int i = 0;

	path = getcwd(NULL, PATH_MAX);
	tester = opendir(path);
	while ((test = readdir(tester)) != NULL)
	{
		printf("%s\n", test->d_name);
		i++;
	}*/
	char *test = "test";
	lexer(NULL, test);
	printf("%s", (test));
	return (1);
}

void	ft_test(char **test)
{
	*test = malloc(sizeof (char) * 5);
	int i = 0;
	while (i < 5)
	{
		(*test)[i] = 'a';
		i++;
	}
	(*test)[i] = 0;
}

int	ft_keysize(char *envp)
{
	int i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	return (i + 1);
}