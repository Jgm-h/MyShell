#ifndef PARSER_H
#define PARSER_H
# include "minishell.h"

char	*parenthese_trim(char *prompt);
char	*trim_space(char *prompt);
int		find_level(char *prompt, int level);

#endif //PARSER_H
