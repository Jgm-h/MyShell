# include "minishell.h"

/*TODO:
 * 		- [ ] fork if in pipe
 *		- [x] chck for getcwd error
 *		- [x] check for relative and absolute path (only checking relative atm)
 * 		- [x] handle normal behavior
 * 		- [x] handle '-':
 * 			- [x] set the new oldpwd
 * 			- [x] if no oldpwd handle error
 * 		- [x] handle no second argument to go back HOME
 * 		- [x] set the new PWD and OLDPWD
 * 		- [x] gerer l'erreur de si le home a ete unset
 * */

T_BOOL	update_old_new_pwd(t_container *book)
{
	int	index;

	index = get_index_env(book->envp, "OLPWD=");
	if (index == -1)
		add_var(book, ft_strdup("OLDPWD="), book->cwd);
	else
		export_value(book->envp[index], ft_strdup("OLDPWD="), book->cwd);
	book->cwd = getcwd(NULL, 0);
	if (!book->cwd)
	{
		my_print_error("minishell-2.0: cwd");
		return (FALSE);
	}
	index = get_index_env(book->envp, "PWD=");
	if (index == -1)
		add_var(book, ft_strdup("PWD="), ft_strdup(book->cwd));
	else
		export_value(book->envp[index], \
		ft_strdup("PWD="), ft_strdup(book->cwd));
	return (TRUE);
}

int	handle_oldpwd(t_container *book)
{
	int		index;

	index = get_index_env(book->envp, "OLDPWD=");
	if (index == -1)
	{
		my_print_error("minishell-2.0: cd: OLDPWD not set");
		errno = 1;
		return (ERROR);
	}
	if (chdir(book->envp[index] + 7) == -1)
	{
		my_print_error("minishell-2.0: cd: ");
		my_print_error(book->envp[index] + 7);
		my_print_error(": No such file or directory");
		errno = 1;
		return (ERROR);
	}
	if (!update_old_new_pwd(book))
		return (ERROR);
	printf("%s", book->cwd);
	return (SUCCESS);
}

int	go_home(t_container *book)
{
	int		index;

	index = get_index_env(book->envp, "HOME=");
	if (index == -1)
	{
		my_print_error("minishell-2.0: cd: HOME not set");
		return (ERROR);
	}
	if (chdir(book->envp[index] + 5) == -1)
		return (ERROR);
	if (!update_old_new_pwd(book))
		return (ERROR);
	return (SUCCESS);
}

int	normal_usage(t_token *leaf, t_container *book)
{
	if (chdir(leaf->args[1]) == -1)
	{
		my_print_error("minishell-2.0: cd: ");
		my_print_error(leaf->args[1]);
		my_print_error(": No such file or directory");
		return (ERROR);
	}
	if (!update_old_new_pwd(book))
		return (ERROR);
	return (SUCCESS);
}

void	check_absolute_path(t_token *leaf, t_container *book)
{
	int	index;

	index = get_index_env(book->envp, "PWD=");
	if (index == -1)
		return ;
	if (!ft_strncmp(book->envp[index] + 4, leaf->args[1], \
			ft_strlen(book->envp[index] + 4)))
		replace_path(leaf, book->envp[index] + 4);
}

T_BOOL	cd(t_token *leaf, t_container *book)
{
	if (book->in_pipe)
		return (SUCCESS);
	if (leaf->args[1][0] == '-' && !leaf->args[1][1])
		return (handle_oldpwd(book));
	if (leaf->args[1][0] == '-' && leaf->args[1][1])
	{
		my_print_error("minishell-2.0: cd:");
		my_print_error(leaf->args[1]);
		my_print_error(": invalid option\ncd: usage: cd [-L|-P] [dir]");
		errno = 1;
		return (ERROR);
	}
	if (!leaf->args[1])
		return (go_home(book));
	check_absolute_path(leaf, book);
	return (normal_usage(leaf, book));
}
