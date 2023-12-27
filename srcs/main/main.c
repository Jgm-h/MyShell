#include <stdio.h>
#include "minishell.h"
#include "libft.h"

volatile int	g_status = NEW_LINE;

int main(int argc, char **argv, char **envp)
{
	t_container *book;

	(void) argc;
	(void) argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	if (!init(&book, envp, argc))
		return (1);
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
//	if (tree->type == IN_REDIR)
//		printf("IN_REDIR ");
//	if (tree->type == HERDOC)
//		printf("HERDOC ");
//	if (tree->type == OUT_REDIR)
//		printf("OUT_REDIR ");
//	if (tree->type == APD_REDIR)
//		printf("APD_REDIR ");
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
//	if (tree->type == IN_REDIR)
//		printf("IN_REDIR ");
//	if (tree->type == HERDOC)
//		printf("HERDOC ");
//	if (tree->type == OUT_REDIR)
//		printf("OUT_REDIR ");
//	if (tree->type == APD_REDIR)
//		printf("APD_REDIR ");
//	printf("\n");
//}
