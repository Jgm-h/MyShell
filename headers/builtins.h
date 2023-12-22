//
// Created by Joshua Morcom-Harneis on 12/19/23.
//

#ifndef MINISHELL_BUILTINS_H
#define MINISHELL_BUILTINS_H
# include "minishell.h"

int		pwd(t_token *leaf, t_container *);
T_BOOL	echo(t_token *leaf, t_container *book, t_pipes pipes);


#endif //MINISHELL_BUILTINS_H
