//
// Created by Joshua Morcom-Harneis on 12/19/23.
//

#ifndef MINISHELL_BUILTINS_H
#define MINISHELL_BUILTINS_H
# include "minishell.h"

int		pwd(void);
T_BOOL	echo(t_token *leaf, t_pipes pipes);
T_BOOL	cd(t_token *leaf, t_container *book);
int		env(t_token *leaf, t_container *book);
void	my_exit(t_token *leaf, t_container *book);
T_BOOL	export(t_token *leaf, t_container *book);
T_BOOL	unset(t_token *leaf, t_container *book);

#endif //MINISHELL_BUILTINS_H
