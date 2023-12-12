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

enum e_token_type{
	AND,
	OR,
	PIPE,
	INPUT_REDIRECTION,
	HERDOC_REDIRECTION,
	OUTPUT_REDIRECTION,
	OUTPUT_ADD_REDIRECTION,
	COMMAND,
	FILE_,
};

typedef struct s_token
{
	enum e_token_type	type;
	union
	{
		char	*argv;
		int		fd;
		int		pipe[2];
	};
	struct s_token		*left;
	struct s_token		*right;
}	t_token;

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
