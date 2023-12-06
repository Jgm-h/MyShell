#include "minishell.h"
#include "init.h"

void	init(t_container *book, char **envp)
{
	book = ft_calloc(1, sizeof (t_container));
	book->exit_status = 0;
	init_envp(book, envp);
	init_paths(book);
}

void	init_paths(t_container *book)
{
	int		i;
	char	*hook;

	i = 0;
	while (ft_strncmp(book->envp[i], "PATH", 4))
		i++;
	book->paths = ft_split(book->envp[i] + 5);
	i = 0;
	while (book->paths[i])
	{
		hook = book->paths[i];
		book->paths[i] = ft_strjoin(book->paths[i], "/");
		free(hook);
		i++;
	}
}

void	init_envp(t_container *book, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	book->envp = ft_calloc(i, sizeof (char *));
	i = 0;
	while (envp[i])
	{
		book->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	book->envp[i] = NULL;
}
