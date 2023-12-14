#ifndef INIT_H
# define INIT_H
# include "minishell.h"

unsigned int init_envp(t_container *book, char **envp);
unsigned int init_paths(t_container *book);
void	init_termios(void);

#endif //INIT_H
