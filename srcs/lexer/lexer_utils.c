#include "minishell.h"

int	ft_strcmp_lexer(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != ' ' && \
		s1[i] != '\"' && s1[i] != '\'' && s1[i] == s2[i])
		i++;
	if ((!s1[i] || s1[i] == ' ' || s1[i] == '\"' || \
		s1[i] != '\'') && s2[i] == '=')
		return (FALSE);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_intlen(int number)
{
	int size;

	size = 0;
	if (number == 0)
		return (1);
	while (number % 10)
	{
		number /= 10;
		size++;
	}
	return (size);
}

int	ft_keysize_input(char *s1)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != ' ' && s1[i] != '\"' && s1[i] != '\'')
		i++;
	return (i);
}

int	ft_keysize(char *envp)
{
	int	i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	return (i + 1);
}

int	ft_value_expand(char *input, char **envp, int exit_status)
{
	int	j;

	j = 0;
	if (input[1] == '?')
		return (ft_intlen(exit_status));
	while (envp[++j])
	{
		if (!ft_strcmp_lexer(input, envp[j]))
			return (ft_strlen(envp[j] + 4));
	}
	return (0);
}
