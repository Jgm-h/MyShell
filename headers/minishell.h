//
// Created by Joshua Morcom-Harneis on 12/5/23.
//

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "stdio.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# define T_BOOL unsigned int
# define TRUE 1
# define FALSE 0

typedef struct s_token{
	char			*cmd;
	char			**argv;
	int				fd_input;
	int				fd_output;
	struct s_token	*next;
}t_token;

typedef struct s_container{
	t_token	*head;
	char	**envp;
	char	**paths;
	int		exit_status;
}t_container;

void	init(t_container *book, char **envp);
unsigned int lexer(t_container *book, char *input);
void	parser(t_container *book, char **argv);
void	exec(t_container *book);

#endif //MINISHELL_H
