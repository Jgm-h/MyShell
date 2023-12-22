# include "minishell.h"

/* TODO:
 *  	- [x] check that first char is possible return error do until faulty
 * 		- [x] while arg export the arg (allowed char are alpha, digit, '_'):
 * 		   	- [x] check for the = sign if not skip
 * 		- [x] the first char should not be a digit
 * */

T_BOOL	check_allowed_char_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

void	export_pair(char *str, t_container *book)
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
	book->envp[i] = ft_strdup(str);
	i = -1;
	while (hook[++i])
	{
		free(hook[i]);
		free(old_envp[i]);
	}
	free(hook);
	free(old_envp);
}

T_BOOL	export(t_token *leaf, t_container *book)
{
	int	i;

	i = 1;
	if (book->in_pipe)
		return (SUCCESS);
	while (leaf->args[i])
	{
		if (!ft_isalpha(leaf->args[i][0]) && leaf->args[i][0] != '_')
		{
			errno = 1;
			return (ERROR);
		}
		if (!check_allowed_char_key(leaf->args[i]))
		{
			errno = 1;
			return (ERROR);
		}
		export_pair(leaf->args[i], book);
		i++;
	}
	return (SUCCESS);
}
