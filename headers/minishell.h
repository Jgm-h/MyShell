//
// Created by Joshua Morcom-Harneis on 12/5/23.
//

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "stdio.h"
# include <errno.h>
# include "signal.h"
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# define T_BOOL unsigned int
# define TRUE 1
# define FALSE 0
# define MAX_PATH_LEN 4096

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

enum e_status{
	PROMPT,
	NEW_LINE,
	HEREDOC,
	ABORT_HEREDOC
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
	char	*prompt;
	char	*cwd;
	int		exit_status;
}t_container;

void			init(t_container **book, char **envp, int argc);
unsigned int	lexer(t_container *book, char **input);
t_token			*parser(char *prompt);
void			signal_handler(int signal);
int				minishell(t_container *book);

#endif //MINISHELL_H
