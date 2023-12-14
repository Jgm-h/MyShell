#include "minishell.h"
#include "init.h"

void	init(t_container **book, char **envp, int argc)
{
	if (argc != 1)
	{
		perror("Usage: ./minishell {don't use any arguments}\n");
		exit(1);
	}
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		perror("./minishell error with stream\n");
		exit(1);
	}
	(*book) = ft_calloc(1, sizeof (t_container));
	if (!(*book))
		exit(1);
	(*book)->exit_status = 0;
	(*book)->prompt = "minishell-2.0$";
	if (!getcwd((*book)->cwd, MAX_PATH_LEN + 1))
	{
		perror("minishell: getcwd: ");
		exit(1);
	}
	if (!init_envp(*book, envp) || !init_paths(*book))
		exit(1);
	init_termios();
}

void	init_termios(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
		return ;
	}
}

unsigned int	init_paths(t_container *book)
{
	int		i;
	char	*hook;

	i = 0;
	while (ft_strncmp(book->envp[i], "PATH", 4))
		i++;
	book->paths = ft_split(book->envp[i] + 5);
	if (!book->paths)
		return (FALSE);
	i = 0;
	while (book->paths[i])
	{
		hook = book->paths[i];
		book->paths[i] = ft_strjoin(book->paths[i], "/");
		free(hook);
		i++;
	}
	return (TRUE);
}

unsigned int	init_envp(t_container *book, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	book->envp = ft_calloc(i, sizeof (char *));
	if (!book->envp)
		return (FALSE);
	i = 0;
	while (envp[i])
	{
		book->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	book->envp[i] = NULL;
	return (TRUE);
}
