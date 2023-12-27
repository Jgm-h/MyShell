#include "minishell.h"

volatile extern int	g_status;

void	input_handling(t_container *book, char **input)
{
	*input = readline(book->prompt);
	if (!*input)
		my_print_error("minishell-2.0: exit");
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
		if (!lexer(&input))
			continue ;
		printf("%s", input);
		book->head = parser(input);
		lexer_token(book->head, book);
		free(input);
//		if (!exec(book))
//			book->exit_status = errno;
	}
	free_all(book);
	return (1);
}