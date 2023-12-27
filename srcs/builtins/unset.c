#include "minishell.h"

/* TODO: this function unset the envp copy variables as long as you have arguments
 * 		- [x] if no args return prompt and no errno
 * 		- [x] if the arg is not in envp, not an error
 * 		- [x] if an arg is invalid continue to unset for the others
 * */



T_BOOL	check_unvalid(char *key)
{
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		my_print_error("minishell-2.0: unset: `");
		my_print_error(key);
		my_print_error("': not a valid identifier");
		return (ERROR);
	}
	return (SUCCESS);
}

void	copy_env(t_container *book)
{
	int		i;
	char	**old_envp;
	char	**hook;

	i = 0;
	while (book->envp[i])
		i++;
	old_envp = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (book->envp[++i])
		old_envp[i] = ft_strdup(book->envp[i]);
	hook = book->envp;
	book->envp = ft_calloc(i + 2, sizeof (char *));
	i = -1;
	while (old_envp[++i])
		book->envp[i] = ft_strdup(old_envp[i]);
	i = -1;
	while (hook[++i])
	{
		free(hook[i]);
		free(old_envp[i]);
	}
	free(hook);
	free(old_envp);
}

void	unset_var(t_container *book, int index)
{
	copy_env(book);
	while (book->envp[index])
	{
		book->envp[index] = book->envp[index + 1];
		index++;
	}
}

T_BOOL	unset(t_token *leaf, t_container *book)
{
	int		index;
	int		i;
	T_BOOL	exit;

	i = 0;
	exit = SUCCESS;
	if (!leaf->args[1])
		return (SUCCESS);
	while (leaf->args[++i])
	{
		index = get_index_env(book->envp, leaf->args[i]);
		if (index == -1)
		{
			exit = check_unvalid(leaf->args[i]);
			if (exit)
				errno = 1;
			continue ;
		}
		else
			unset_var(book, index);
	}
	return (exit);
}
