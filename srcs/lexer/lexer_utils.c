#include "minishell.h"

int	ft_strcmp_lexer(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != ' ' && \
		s1[i] != '\"' && s1[i] != '\'' && s1[i] == s2[i])
		i++;
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

/*need key lenght and value lenght*/
char	*ft_strcpy_lexer(char *input, int i, char *env)
{
	int		j;
	int		k;
	int		key_size;
	char	*exp;

	exp = ft_calloc(ft_strlen(input) + ft_strlen(env), sizeof (char));
	if (!exp)
		return (NULL);
	j = -1;
	k = -1;
	key_size = 0;
	while (j++ < i)
		exp[j] = input[j];
	while (env[++k])
		exp[j + k] = env[k];
	while (input[j + key_size] && input[j + key_size] != ' ' && \
		input[j + key_size] != '\"' && input[j + key_size] != '\'')
		key_size++;
	while (input[j + key_size])
	{
		exp[j + k] = input[j + key_size];
		j++;
	}
	return (exp);
}

int	ft_keysize(char *envp)
{
	int	i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	return (i + 1);
}
