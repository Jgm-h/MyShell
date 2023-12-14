#include "minishell.h"

volatile extern int	g_status;

void	print_tree(t_token *tree)
{
	if (!tree)
		return ;
	print_tree(tree->left);
	if (tree->type == COMMAND)
		printf("%s ", tree->argv);
	if (tree->type == AND)
		printf("AND ");
	if (tree->type == OR)
		printf("OR ");
	if (tree->type == PIPE)
		printf("PIPE ");
	if (tree->type == INPUT_REDIRECTION)
		printf("INPUT_REDIRECTION ");
	if (tree->type == HERDOC_REDIRECTION)
		printf("HERDOC_REDIRECTION ");
	if (tree->type == OUTPUT_REDIRECTION)
		printf("OUTPUT_REDIRECTION ");
	if (tree->type == OUTPUT_ADD_REDIRECTION)
		printf("OUTPUT_ADD_REDIRECTION ");
	printf("\n");
	print_tree(tree->right);
}

void	input_handling(t_container *book, char **input)
{
	book->prompt = ft_strjoin("minishell-2.0$", book->cwd);
	if (!book->prompt)
		exit(1);//exit_minishell(book, input);
	*input = readline(book->prompt);
	if (!*input)
		exit(1);//exit_minishell(book, input);
	add_history(*input);
}
/*
T_BOOL	exec(t_token *token)
{
	if (token->type == AND)
	{
		if (exec(token->left))
			exec(token->right);
	}
	if (token->type == OR)
	{
		if (!exec(token->left))
			exec(token->right);
	}
	if (token->type == PIPE)
		return (exec_pipe(token->left, token->right));
	if (token->type)
}*/

int	minishell(t_container *book)
{
	char	*input;

	while (book)
	{
		input_handling(book, &input);
		if (!input)
			continue ;
		if (!lexer(book, &input))
			continue ;
		book->head = parser(input);
		free(input);
		print_tree(book->head);
		if (g_status == NEW_LINE)
			book->exit_status = 130;
//	exec(book);
	}
	//free_all(book, token);
	return (1);
}