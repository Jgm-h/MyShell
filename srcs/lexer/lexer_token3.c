#include "minishell.h"

int	ft_redirlen(char *redir)
{
	int	i;

	i = 0;
	while (*redir && (*redir == '<' || *redir == '>'))
	{
		redir++;
		i++;
	}
	while (*redir && *redir != ' ' && *redir != '<' && *redir != '>' \
		&& *redir != ')' && *redir != '|' && *redir != '&')
	{
		redir++;
		i++;
	}
	return (i);
}

T_BOOL	check_pipe_position(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (!input[i] || input[i] == '|')
		return (FALSE);
	while (input[i++])
	{
		if (!check_double(input, i, 0, 0) && input[i] == '|')
		{
			while (input[i] && input[i] == ' ')
				i++;
			if (input[i] == '|' && !input[i + 1])
				return (FALSE);
		}
		else if (input[i] == '|' && !input[i + 1])
			return (FALSE);
	}
	return (TRUE);
}

T_BOOL	check_heredoc_start(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
		i++;
	if (!ft_strncmp(&input[i], (char *)"<<", 2))
	{
		while (input[i] != ' ' && input[i] != '(' && input[i] != ')')
			i++;
		if (input[i] == '(')
		{
			my_print_error("syntax error near unexpected token `('");
			return (FALSE);
		}
		if (input[i] == ')')
		{
			my_print_error("syntax error near unexpected token `)'");
			return (FALSE);
		}
		while (input[i] == ' ')
			i++;
		if (!input[i])
			return (FALSE);
	}
	return (TRUE);
}

T_BOOL	check_heredoc_alone(char *input, int i, T_BOOL first)
{
	while (input[i] && input[i] == ' ')
		i++;
	if (!check_heredoc_start(input))
		return (FALSE);
	while (input[i])
	{
		if (!ft_strncmp(&input[i], "<<", 2))
		{
			if (first)
			{
				my_print_error("syntax error near unexpected token '<<'");
				return (FALSE);
			}
			if (!input[i + 2])
			{
				my_print_error("syntax error near unexpected token `newline'\n");
				return (FALSE);
			}
			first = TRUE;
		}
		i++;
	}
	return (TRUE);
}
