# include "minishell.h"
#include "parser.h"

void	parser(t_container *book, char **argv)
{
	book->head = ft_calloc(1, sizeof (t_token));
	book->head->cmd = ft_strdup(argv[1]);
	book->head->argv = ft_calloc(2, sizeof (char *));
	book->head->argv[1] = NULL;
}