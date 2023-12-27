#include "minishell.h"

/* this builtin should print the working directory using getcwd
 * getcwd space needs to be freed
 * */

int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (errno);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
