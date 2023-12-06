#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"

void exec_one_cmd(t_container *book, t_token *node);
char *find_path(t_container *book,t_token *node);

#endif //EXEC_H
