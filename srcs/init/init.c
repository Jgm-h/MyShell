#include "minishell.h"
#include "init.h"

unsigned int init(t_container **book, char **envp, int argc)
{
	if (argc != 1)
		return (my_print_error("Usage: ./minishell {don't use any arguments}\n"));
	if (!isatty(0) || !isatty(1) || !isatty(2))
		return (my_print_error("./minishell error with stream\n"));
	(*book) = ft_calloc(1, sizeof (t_container));
	if (!(*book))
		return (my_print_error("minishell-2.0: malloc error"));
	(*book)->exit_status = 0;
	(*book)->prompt = "minishell-2.0$";
	(*book)->cwd = getcwd(NULL, 0);
	if (!(*book)->cwd)
		return (my_print_error("minishell: getcwd: "));
	if (!init_envp(*book, envp) || !init_paths(*book))
		return (1);
	(*book)->prompt = ft_strdup("minishell-2.0$");
	if (!(*book)->prompt)
		return (my_print_error("minishell-2.0: malloc error"));
	init_termios();
	return (1);
}

void	init_termios(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		my_print_error("tcgetattr");
		return ;
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		my_print_error("tcsetattr");
		return ;
	}
}

unsigned int	init_paths(t_container *book)
{
	int		i;

	i = 0;
	while (ft_strncmp(book->envp[i], "PATH", 4))
		i++;
	book->paths = ft_split(book->envp[i] + 5, ':');
	if (!book->paths)
		return (FALSE);
	i = 0;
	while (book->paths[i])
	{
		book->paths[i] = ft_strjoin(ft_strdup(book->paths[i]), ft_strdup("/"));
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
