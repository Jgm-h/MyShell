#ifndef EXEC_H
# define EXEC_H
# include "minishell.h"

int		exec_one_cmd(t_token *leaf, t_container *book, t_pipes pipes);
char	*find_path(t_token *leaf, t_container *book, int i, char *arg);
T_BOOL	execute_redir(t_token *leaf, t_container *book, t_pipes pipes);
T_BOOL	r_executor(t_token *leaf, t_container *book, t_pipes pipes);
T_BOOL	execute_pipe(t_token *leaf, t_container *book, t_pipes pipes);

#endif //EXEC_H
