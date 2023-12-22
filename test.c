#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include "dirent.h"
#include "limits.h"
#include <sys/types.h>
# include <fcntl.h>
# define T_BOOL unsigned int
# define TRUE 1
# define FALSE 0
typedef struct s_token
{
	union
	{
		char	*argv;
		int		fd;
		int		pipe[2];
	};
	char				**args;
	char				*heredoc;
	struct s_token		*left;
	struct s_token		*right;
}	t_token;

void	ft_bzero(void *s, int n)
{
	unsigned char	*d;

	d = (unsigned char *) s;
	if (n == 0)
		return ;
	while (n > 0)
	{
		*d++ = '\0';
		n--;
	}
}

void	*ft_calloc(int count, int size)
{
	void	*tab;

	tab = malloc(size * count);
	if (!tab)
	{
		perror("minishell-2.0: malloc error");
		exit(1);
	}
	ft_bzero(tab, size * count);
	return (tab);
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
	leaf->args = ft_calloc(i + 1, sizeof(char *));
}

int	ft_small_split(char *str, char **to_copy, int size, int ign)
{
	T_BOOL	simp;
	T_BOOL	doub;

	simp = FALSE;
	doub = FALSE;
	while (str[ign] && ((str[ign] == ' ' && !simp && !doub) || \
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
	(*to_copy) = ft_calloc(size + 1, sizeof(char));
	size = 0;
	while (str[size + ign] && !((str[size + ign] == ' ' && !simp && !doub) || \
	(str[size + ign] == '\'' && !doub) || (str[size + ign] == '\"' && !simp)))
	{
		(*to_copy)[size] = str[ign + size];
		size++;
	}
	return (size + ign);
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
		i += ft_small_split(&input[i], &(leaf->args[j]), 0, 0);
		j++;
	}
}

/*doesn't work in keeping the single quotes
 *
 * */
int main(int argc, char **argv, char **envp)
{
	int	i;
	t_token *leaf;

	leaf = malloc(sizeof (t_token));
	split_var(argv[1], leaf, FALSE, FALSE);
	i = 0;
	while (leaf->args[i])
	{
		printf("%s\n", leaf->args[i]);
		printf("%d\n", i);
		i++;
	}
	return(1);
}
