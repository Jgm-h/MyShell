#include <stdio.h>
#include "minishell.h"
#include "libft.h"

volatile int	g_status = PROMPT;

int main(int argc, char **argv, char **envp)
{
	t_container *book;

	(void) argc;
	(void) argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	init(&book, envp, argc);
	return (minishell(book));
}

//void	print_intree(t_token *tree)
//{
//	if (!tree)
//		return ;
//	if (tree->type == COMMAND)
//		printf("%s ", tree->argv);
//	if (tree->type == AND)
//		printf("AND ");
//	if (tree->type == OR)
//		printf("OR ");
//	if (tree->type == PIPE)
//		printf("PIPE ");
//	if (tree->type == INPUT_REDIRECTION)
//		printf("INPUT_REDIRECTION ");
//	if (tree->type == HERDOC_REDIRECTION)
//		printf("HERDOC_REDIRECTION ");
//	if (tree->type == OUTPUT_REDIRECTION)
//		printf("OUTPUT_REDIRECTION ");
//	if (tree->type == OUTPUT_ADD_REDIRECTION)
//		printf("OUTPUT_ADD_REDIRECTION ");
//	printf("\n");
//	print_tree(tree->left);
//	print_tree(tree->right);
//}
//
//void	print_posttree(t_token *tree)
//{
//	if (!tree)
//		return ;
//	print_tree(tree->left);
//	print_tree(tree->right);
//	if (tree->type == COMMAND)
//		printf("%s ", tree->argv);
//	if (tree->type == AND)
//		printf("AND ");
//	if (tree->type == OR)
//		printf("OR ");
//	if (tree->type == PIPE)
//		printf("PIPE ");
//	if (tree->type == INPUT_REDIRECTION)
//		printf("INPUT_REDIRECTION ");
//	if (tree->type == HERDOC_REDIRECTION)
//		printf("HERDOC_REDIRECTION ");
//	if (tree->type == OUTPUT_REDIRECTION)
//		printf("OUTPUT_REDIRECTION ");
//	if (tree->type == OUTPUT_ADD_REDIRECTION)
//		printf("OUTPUT_ADD_REDIRECTION ");
//	printf("\n");
//}
