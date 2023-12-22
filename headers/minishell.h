//
// Created by Joshua Morcom-Harneis on 12/5/23.
//

#ifndef MINISHELL_H
# define MINISHELL_H
# define T_BOOL unsigned int
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1
# define MAX_PATH_LEN 4096
# include "libft.h"
# include "utils.h"
# include "lexer.h"
# include "stdio.h"
# include <errno.h>
# include "signal.h"
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

void			init(t_container **book, char **envp, int argc);
unsigned int	lexer(t_container *book, char **input);
t_token			*parser(char *prompt);
void			signal_handler(int signal);
int				minishell(t_container *book);
T_BOOL			exec(t_container *book);

#endif //MINISHELL_H
