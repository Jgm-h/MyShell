# include "minishell.h"

/* TODO: print envp
 * 		- [x] if more than 1 arg print "bash: envp: command not found"
 * */

int	env(t_token *leaf, t_container *book)
{
	int	i;

	i = 0;
	if (leaf->args[1])
	{
		my_print_error("env:");
		my_print_error(leaf->args[1]);
		my_print_error(": No such file or directory");
		errno = 127;
		return (ERROR);
	}
	while (book->envp[i])
	{
		printf("%s\n", book->envp[i]);
		i++;
	}
	return (SUCCESS);
}
