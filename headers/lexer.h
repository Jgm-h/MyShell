#ifndef LEXER_H
#define LEXER_H
# include "minishell.h"

T_BOOL	check_closed_quotes(const char *input, int in_single, int in_double);
T_BOOL	expand_variables(char *input, t_container *book);
T_BOOL	check_state(char *input, int pos, T_BOOL in_double, T_BOOL in_simple);
T_BOOL	check_expand(char *input, int i, t_container *book);
char	*expand(char *input, int i, t_container *book, int j);
int		ft_strcmp_lexer(const char *s1, const char *s2);
char	*ft_strcpy_lexer(char *input, int i, char *env);
int		ft_keysize(char *envp);

#endif //LEXER_H
