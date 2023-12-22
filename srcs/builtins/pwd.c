#include "minishell.h"

/* this builtin should print the working directory using getcwd
 * getcwd space needs to be freed
 * */

int	pwd(t_token *leaf, t_container *)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (errno);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
