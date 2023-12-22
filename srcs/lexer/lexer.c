#include "minishell.h"
#include "lexer.h"
#define E_SYN "syntax error near unexpected token"

T_BOOL	check_empty_prompt(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (!input[i])
		return (FALSE);
	return (TRUE);
}

T_BOOL	redir_clean_heredoc(char **input, int i, int k)
{
	int		j;
	char	*hook;

	j = -1;
	hook = ft_strdup((*input));
	if (!hook)
		return (FALSE);
	(*input) = ft_calloc(ft_strlen(*input) + 1, sizeof (char));
	if (!(*input))
		return (FALSE);
	while (++j < i)
		(*input)[j] = hook[j];
	while (hook[j + k] != ' ')
		k++;
	while (hook[j + k] && hook[j + k] != ')' && \
		hook[j + k] != '|' && hook[j + k] != '&')
	{
		(*input)[j] = hook[j + k];
		j++;
	}
	(*input)[j++] = ' ';
	while (hook[i] != ' ')
		(*input)[j++] = hook[i++];
	while (hook[j])
	{
		(*input)[j] = hook[j];
		j++;
	}
	free(hook);
	return (TRUE);
}

T_BOOL	check_redir(char *input, int i)
{
	T_BOOL	redir;

	redir = FALSE;
	while (input[i] && input[i] != ')' && input[i] != '|' && input[i] != '&')
	{
		if (input[i] == '<' || input[i] == '>')
			redir = TRUE;
		if (input[i] == ' ')
			redir = FALSE;
		if (input[i] != '<' && input[i] != '>' && \
			input[i] != ' ' && redir == FALSE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

T_BOOL	redir_clean(char **input, int i, int k, int j)
{
	char	*hook;
	char	*redir;
	int		redir_len;

	redir_len = ft_redirlen((*input) + i);
	redir = ft_calloc(redir_len + 1, sizeof (char));
	ft_strlcpy(redir, (*input) + i, redir_len + 1);
	hook = ft_strdup(*input);
	(*input) = ft_calloc(ft_strlen(*input) + 1, sizeof (char));
	if (!(*input) || !hook || !redir)
		return (FALSE);
	while (++j < i)
		(*input)[j] = hook[j];
	while (check_char_redir(hook[j + redir_len]))
	{
		(*input)[j] = hook[j + redir_len];
		j++;
	}
	while (redir[++k])
		(*input)[j + k] = redir[k];
	while (hook[j + redir_len])
	{
		(*input)[j + redir_len] = hook[j + redir_len];
		j++;
	}
	free(hook);
	free(redir);
	return (TRUE);
}

/*a lexer in minishell has to do the following:
 * give back the command line if no input
 * print a \n and give back the command line if there are unclosed quotes, \ or ;
 * handle ' by not interpreting anything
 * handle " by interpreting only env variables preceded by a $
 * handle $ followed by env variables
 * handle $? by expanding it to the exit_status
 * */
T_BOOL	lexer(t_container *book, char **input)
{
	if (!check_empty_prompt(*input))
		return (FALSE);
	if (!check_closed_quotes(*input, 0, 0))
		return (FALSE);
	if (!check_pipe_position(*input))
	{
		perror("syntax error near unexpected token `|'\n");
		return (FALSE);
	}
	if (!check_heredoc_alone(*input, 0, FALSE))
		return (FALSE);
	space_redir_clean(input);
	lexer_redir_clean(input); //TODO: clean where the redir is moved to
	return (TRUE);
}
