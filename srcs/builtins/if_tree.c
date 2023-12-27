#include "minishell.h"
#include "builtins.h"

T_BOOL execute_builtins(t_token *leaf, t_container *book, t_pipes pipes)
{
	if (!ft_strncmp(leaf->args[0], "cd", 3))
		return (cd(leaf, book));
	if (!ft_strncmp(leaf->args[0], "echo", 5))
		return (echo(leaf, pipes));
	if (!ft_strncmp(leaf->args[0], "env", 4))
		return (env(leaf, book));
	if (!ft_strncmp(leaf->args[0], "exit", 5))
		my_exit(leaf, book);
	if (!ft_strncmp(leaf->args[0], "export", 7))
		return (export(leaf, book));
	if (!ft_strncmp(leaf->args[0], "pwd", 4))
		return (pwd());
	if (!ft_strncmp(leaf->args[0], "unset", 6))
		return (unset(leaf, book));
	return (ERROR);
}