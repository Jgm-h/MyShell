#include "minishell.h"
#include "lexer.h"

/* todo:
 * 		- handle wrong expand (if wrong, still execute the rest, sends what through the pipe?)
 * 		- check for \ and ;
 * */

/*a lexer in minishell has to do the following:
 * give back the command line if no input
 * print a \n and give back the command line if there are unclosed quotes, \ or ;
 * handle ' by not interpreting anything
 * handle " by interpreting only env variables preceded by a $
 * handle $ followed by env variables
 * handle $? by expanding it to the exit_status
 * */
T_BOOL	lexer(t_container *book, char *input)
{
	if (!check_closed_quotes(input, 0, 0))
		return (FALSE);
	if (!expand_variables(input, book))
		return (FALSE);
	clean_quotes(input);
	return (TRUE);
}

/*if FALSE & " on garde
 * TRUE & " on tej
 * if true & ' on garde
 * FALSE & ' on tej
 * */
void	clean_quotes(char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i])
	{
		if ((!check_state(input, i, FALSE, FALSE) && input[i] == '\"') \
			|| (check_state(input, i, FALSE, FALSE) && input[i] == '\''))
		{
			j = i;
			while (input[j])
			{
				input[j] = input[j + 1];
				j++;
			}
		}
		i++;
	}
}

T_BOOL	expand_variables(char *input, t_container *book)
{
	int	i;
	int	tmp;

	i = 0;
	while (input[i])
	{
		if (check_state(input, i, FALSE, FALSE) && check_expand(input, i, book))
		{
			tmp = ft_value_expand(&input[i], book->envp, book->exit_status);
			if (!expand(&input, book, 0))
				return (FALSE);
			i += tmp;
		}
		else
			i++;
	}
	return (TRUE);
}

unsigned int expand(char **input, t_container *book, int i)
{
	int		j;

	j = 0;
	if ((*input)[i + 1] == '?')
		return (ft_expand_exit(input, i, book));
	while (book->envp[++j])
	{
		if (!ft_strcmp_lexer(input[i], (book->envp[j])))
			return (ft_strcpy_lexer(input, i, book->envp[j] \
					+ ft_keysize(book->envp[j])));
	}
	return (ft_strcpy_lexer(input, i, NULL));
}

unsigned int	ft_expand_exit(char **input, int i, t_container *book)
{
	char	*exit_status;
	T_BOOL	status;

	exit_status = ft_itoa(book->exit_status);
	if (!exit_status)
		return (FALSE);
	status = ft_strcpy_lexer(input, i, exit_status);
	free(exit_status);
	return (status);
}

unsigned int ft_strcpy_lexer(char **input, int i, char *env)
{
	int		j;
	int		k;
	int		key_size;
	char	*exp;

	exp = ft_strdup(*input);
	(*input) = ft_calloc(ft_strlen(*input) + ft_strlen(env) \
			- ft_keysize_input(&(*input[i])) + 1, sizeof (char));
	if (!*input)
		return (FALSE);
	j = -1;
	k = -1;
	key_size = 0;
	while (++j < i)
		(*input[j]) = exp[j];
	while (env[++k])
		(*input)[j + k] = env[k];
	key_size = ft_keysize_input(&(exp[i]));
	while (input[j + key_size])
	{
		(*input)[j + k] = exp[j + key_size];
		j++;
	}
	(*input)[j + k] = 0;
	return (TRUE);
}
