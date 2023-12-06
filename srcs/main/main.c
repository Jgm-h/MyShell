#include <stdio.h>
#include "minishell.h"
#include "libft.h"

int main(int argc, char **argv, char **envp)
{
	t_container *book;
	char *input;

	(void) argc;
	(void) argv;
	book = NULL;
	init(book, envp);
	input = readline("minishell-1.0$");
	lexer(book, input);
	parser(book, argv);
	exec(book);
	return (1);
}
/*
int main(int argc, char **argv, char **envp) {
	t_container	*book;

	init(book, envp);
	mini_parse(argc, argv, book);
	execution;
	return 0;
}*/
