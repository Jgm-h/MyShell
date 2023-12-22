#include "minishell.h"

volatile extern int	g_status;

void	input_handling(t_container *book, char **input)
{
	book->prompt = ft_strjoin("minishell-2.0$", book->cwd);
	if (!book->prompt)
		my_perror("minishell-2.0: malloc error");
	*input = readline(book->prompt);
	if (!*input)
		my_perror("minishell-2.0: exit");
	add_history(*input);
}

int	minishell(t_container *book)
{
	char	*input;

	while (book)
	{
		g_status = NEW_LINE;
		book->in_pipe = FALSE;
		input_handling(book, &input);
		if (!input)
			continue ;
		if (!lexer(book, &input))
			continue ;
		book->head = parser(input);
		free(input);
		if (!exec(book))
			book->exit_status = errno;
	}
	//free_all(book, token);
	return (1);
}