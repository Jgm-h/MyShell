#include "minishell.h"
#include "lexer.h"
#define E_SYN "syntax error near unexpected token"

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

static T_BOOL	check_heredoc_start(char *input)
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
			perror("syntax error near unexpected token `('");
			return (FALSE);
		}
		if (input[i] == ')')
		{
			perror("syntax error near unexpected token `)'");
			return (FALSE);
		}
		while (input[i] == ' ')
			i++;
		if (!input[i])
			return (FALSE);
	}
	return (TRUE);
}

static T_BOOL	check_heredoc_alone(char *input, int i, T_BOOL first)
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
				perror("syntax error near unexpected token '<<'");
				return (FALSE);
			}
			if (!input[i + 2])
			{
				perror(E_SYN"`newline'\n");
				return (FALSE);
			}
			first = TRUE;
		}
		i++;
	}
	return (TRUE);
}

T_BOOL	check_empty_prompt(char *input)
{
	int i;

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
	T_BOOL redir;

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

	hook = ft_strdup(*input);
	(*input) = ft_calloc(ft_strlen(*input) + 1, sizeof (char));
	if (!(*input) || !hook)
		return (FALSE);
	while (++j < i)
		(*input)[j] = hook[j];
	while (hook[j + k] == '<' || hook[j + k] == '>' || hook[j + k] == ' ')
		k++;
	while (hook[j + k] != ' ')
		k++;
	while (hook[j + k] && hook[j + k] != ')' && \
	hook[j + k] != '|' && hook[j + k] != '&')
	{
		(*input)[j] = hook[j + k];
		j++;
	}
	(*input)[j++] = ' '; // fuck up here
	while (hook[i] == '<' || hook[i] == '>' || hook[i] == ' ')
		(*input)[j++] = hook[i++];
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

T_BOOL	lexer_redir_clean(char **input)
{
	int	i;

	i = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '<' && (*input)[i + 1] == '<')
		{
			if (check_redir((*input), i) && \
			!redir_clean_heredoc(input, i, 0))
				return (FALSE);
		}
		if ((*input)[i] == '<' || (*input)[i] == '>')
		{
			if (check_redir((*input), i) && !redir_clean(input, i, 0, -1))
				return (FALSE);
		}
		i++;
	}
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
	if (!expand_variables(input, book))
		return (FALSE);
	if (!check_pipe_position(*input))
	{
		perror("syntax error near unexpected token `|'\n");
		return (FALSE);
	}
	if (!check_heredoc_alone(*input, 0, FALSE))
		return (FALSE);
	lexer_redir_clean(input);//TODO: clean this small shit
	//clean_quotes(*input, 0, 0, 0);
	return (TRUE);
}

/*if FALSE & " on garde
 * TRUE & " on tej
 * if true & ' on garde
 * FALSE & ' on tej
 * */
//void	clean_quotes(char *input, T_BOOL in_double, T_BOOL in_simple, int i)
//{
//	int		j;
//
//	while (input[i])
//	{
//		if ((input[i] == '\"' || input[i] == '\'') && !in_simple && !in_double)
//		{
//			if (input[i] == '\"')
//				in_double = !in_double;
//			if (input[i] == '\'')
//				in_simple = !in_simple;
//			j = i;
//			while (input[j])
//			{
//				input[j] = input[j + 1];
//				j++;
//			}
//		}
//		if (input[i] == '\"' && !in_simple)
//			in_double = !in_double;
//		else if (input[i] == '\'' && !in_double)
//			in_simple = !in_simple;
//		else
//			i++;
//	}
//}

T_BOOL	expand_variables(char **input, t_container *book)
{
	int	i;
	int	tmp;

	i = 0;
	while ((*input)[i])
	{
		if (check_state((*input), i, FALSE, \
				FALSE) && check_expand((*input), i, book))
		{
			tmp = ft_value_expand(&(*input)[i + 1], \
				book->envp, book->exit_status);
			if (!expand(input, book, i))
				return (FALSE);
			i += tmp;
		}
		else
			i++;
	}
	return (TRUE);
}

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
		return (FALSE);
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
