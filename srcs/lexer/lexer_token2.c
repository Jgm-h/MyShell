#include "minishell.h"

unsigned int	expand(char **input, t_container *book, int i)
{
	int		j;

	j = 0;
	if ((*input)[i + 1] == '?')
		return (ft_expand_exit(input, i, book));
	while (book->envp[++j])
	{
		if (!ft_strcmp_lexer(&(*input)[i + 1], (book->envp[j])))
			return (ft_strcpy_lexer(input, i, book->envp[j] \
					+ ft_keysize(book->envp[j]), -1));
	}
	return (ft_strcpy_lexer(input, i, NULL, -1));
}

unsigned int	ft_expand_exit(char **input, int i, t_container *book)
{
	char	*exit_status;
	T_BOOL	status;

	exit_status = ft_itoa(book->exit_status);
	if (!exit_status)
		return (FALSE);
	status = ft_strcpy_lexer(input, i, exit_status, -1);
	free(exit_status);
	return (status);
}

unsigned int	ft_strcpy_lexer(char **input, int i, char *env, int j)
{
	int		k;
	int		key_size;
	char	*exp;

	exp = ft_strdup(*input);
	(*input) = ft_calloc(ft_strlen(*input) + ft_strlen(env) \
			- ft_keysize_input((*input) + i) + 1, sizeof (char));
	if (!*input || !exp)
		my_perror("malloc");
	while (++j < i)
		(*input)[j] = exp[j];
	k = -1;
	if (env)
	{
		while (env[++k])
			(*input)[j + k] = env[k];
	}
	key_size = ft_keysize_input(&(exp[i]));
	while (exp[j + key_size])
		(*input)[j + k++] = exp[j + key_size++];
	(*input)[j + k] = 0;
	return (TRUE);
}

T_BOOL	check_char_redir(char c)
{
	if (c == '|' \
	|| c == '&' || c == ')' || c == '(')
		return (FALSE);
	return (TRUE);
}


void	clean_quotes(char **input, T_BOOL in_double, T_BOOL in_simple, int i)
{
	int		j;

	while ((*input[i]))
	{
		if (((*input)[i] == '\"' && !in_simple) || \
			((*input[i]) == '\'' && !in_double))
		{
			if ((*input)[i] == '\"')
				in_double = !in_double;
			if ((*input)[i] == '\'')
				in_simple = !in_simple;
			j = i - 1;
			while (input[++j])
				(*input)[j] = (*input)[j + 1];
		}
		else
			i++;
	}
}
