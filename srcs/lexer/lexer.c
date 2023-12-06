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



/* todo:
 * 		- if the key doesn't exist should clean it out of the string
 * */
T_BOOL	expand_variables(char *input, t_container *book)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (check_state(input, i, FALSE, FALSE) && check_expand(input, i, book))
		{
			input = expand(input, i, book, -1);
			if (!input)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

char	*expand(char *input, int i, t_container *book, int j)
{
	char	*expanded;
	char	*exit_status;

	if (input[i + 1] == '?')
	{
		exit_status = ft_itoa(book->exit_status);
		expanded = ft_strcpy_lexer(input, i, exit_status);
		free(exit_status);
		free(input);
		return (expanded);
	}
	while (book->envp[++j])
	{
		if (!ft_strcmp_lexer(&input[i], (book->envp[j])))
		{
			expanded = ft_strcpy_lexer(input, i, book->envp[j] \
					+ ft_keysize(book->envp[j]));
			free(input);
			break ;
		}
	}
	if (!book->envp[j])
		return (input);
	return (expanded);
}

T_BOOL	check_expand(char *input, int i, t_container *book)
{
	int	j;

	j = 0;
	if (input[i] == '$')
	{
		if (input[i + 1] == '?')
			return (TRUE);
		while (book->envp[j])
		{
			if (!ft_strcmp_lexer(&input[i], (book->envp[j])))
				return (TRUE);
			j++;
		}
	}
	return (FALSE);
}
