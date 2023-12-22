#include "minishell.h"

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
			if (check_redir((*input), i) && !redir_clean(input, i, -1, -1))
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	space_redir_clean(char **input)
{
	char	*hook;
	int		i;
	int		j;

	i = 0;
	j = 0;
	hook = ft_strdup(*input);
	(*input) = ft_calloc(ft_strlen(hook), sizeof (hook));
	while (hook[j])
	{
		if (hook[j] == '<' || hook[j] == '>')
		{
			while (hook[j] && (hook[j] == '<' || hook[j] == '>'))
				(*input)[i++] = hook[j++];
			while (hook[j] && hook[j] == ' ')
				j++;
		}
		else
			(*input)[i++] = hook[j++];
	}
	free(hook);
}

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

void	alloc(char *input, t_token *leaf, T_BOOL simp, T_BOOL doub)
{
	int	i;

	i = 0;
	while (*input)
	{
		while (*input && ((*input == ' ' && !simp && !doub) || \
			(*input == '\'' && !doub) || (*input == '\"' && !simp)))
		{
			if (*input == '\"' && !simp)
				doub = !doub;
			if (*input == '\'' && !doub)
				simp = !simp;
			input++;
		}
		if (!*input)
			continue ;
		i++;
		while (*input && !((*input == ' ' && !simp && !doub) || \
		(*input == '\'' && !doub) || (*input == '\"' && !simp)))
			input++;
	}
	leaf->args = ft_calloc(i, sizeof(char *));
}

int	word_len(char *str)
{
	T_BOOL	simp;
	T_BOOL	doub;
	int		size;
	int		ign;

	simp = FALSE;
	doub = FALSE;
	size = 0;
	ign = 0;
	while (str[ign] && !((str[ign] == ' ' && !simp && !doub) || \
		(str[ign] == '\'' && !doub) || (str[ign] == '\"' && !simp)))
	{
		if (*str == '\"' && !simp)
			doub = !doub;
		if (*str == '\'' && !doub)
			simp = !simp;
		ign++;
	}
	while (str[size + ign] && !((str[size + ign] == ' ' && !simp && !doub) || \
	(str[size + ign] == '\'' && !doub) || (str[size + ign] == '\"' && !simp)))
		size++;

}

void	split_var(char *input, t_token *leaf, T_BOOL simp, T_BOOL doub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	alloc(input, leaf, FALSE, FALSE);
	while (input[i])
	{
		i = ft_small_split(leaf->args[j++], &input[i]);
	}
}
/* check recursively for each token with type COMMAND
 * */
T_BOOL	lexer_token(t_token *leaf, t_container *book)
{
	int	i;

	i = 0;
	if (!leaf)
		return (TRUE);
	if (leaf->type != COMMAND)
		return (lexer_token(leaf->left, book) && \
				lexer_token(leaf->right, book));
	if (leaf->type == COMMAND)
	{
		split_var(leaf->argv, leaf, FALSE, FALSE);
		while (leaf->args[i])
		{
			if (!expand_variables(&(leaf->args[i]), book))
				return (FALSE);
			clean_quotes(&(leaf->args[i]), 0, 0, 0);
			i++;
		}
		return (TRUE);
	}
	return (FALSE);
}
