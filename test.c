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

void tes(char **str)
{
	printf("%s", &(*str)[1]);
}

/*doesn't work in keeping the single quotes
 *
 * */
int main(int argc, char **argv, char **envp)
{
	int	i;
	char *test;

	test = ft_calloc(5, sizeof(char));
	test = "test";

	tes(&test);
	return(1);
}
