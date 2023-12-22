#include "minishell.h"

void	replace_path(t_token *leaf, char *pwd)
{
	int		i;
	int		j;
	char	*new_str;

	j = 0;
	i = ft_strlen(pwd);
	new_str = ft_calloc(ft_strlen(leaf->args[1]) - \
			ft_strlen(pwd) + 1, sizeof (char));
	while (leaf->args[1][i])
		new_str[j++] = leaf->args[1][i++];
	new_str[j] = 0;
	free(leaf->args[1]);
	leaf->args[1] = new_str;
}

/* need to remalloc the whole envp*/
void	add_var(t_container *book, char *key, char *value)
{
	int		i;
	char	**old_envp;
	char	**hook;

	i = 0;
	while (book->envp[i])
		i++;
	old_envp = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (book->envp[++i])
		old_envp[i] = ft_strdup(book->envp[i]);
	hook = book->envp;
	book->envp = ft_calloc(i + 2, sizeof (char *));
	i = -1;
	while (old_envp[++i])
		book->envp[i] = ft_strdup(old_envp[i]);
	book->envp[i] = ft_strjoin(key, value);
	i = -1;
	while (hook[++i])
	{
		free(hook[i]);
		free(old_envp[i]);
	}
	free(hook);
	free(old_envp);
}

void	export_value(char *env, char *key, char *value)
{
	char	*hook;

	hook = env;
	env = ft_calloc(ft_strlen(key) + ft_strlen(value) + 1, sizeof(char));
	if (!env)
		my_perror("malloc error");
	free(hook);
	ft_strlcpy(env, key, ft_strlen(key) + 1);
	ft_strlcpy(env + ft_strlen(key), value, ft_strlen(value) + 1);
	free(key);
	free(value);
}

int	get_index_env(char **envp, char *key)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], key, ft_strlen(key)))
		i++;
	if (!envp[i])
		return (-1);
	return (i);
}

T_BOOL	my_access(char *file, int flag)
{
	if (access(file, flag) == -1)
	{
		perror("minishell-2.0: permission denied: ");
		perror(file);
		return (FALSE);
	}
	else
		return (TRUE);
}

int	my_dup2(int fd_file, int to_dup)
{
	if (dup2(fd_file, to_dup) == -1)
	{
		perror("minishell-2.0: dup2 failed");
		return (-1);
	}
	else
		return (1);
}

void	my_perror(char *str)
{
	perror(str);
	exit(errno);
}

void	free_split(char **to_free)
{
	int		i;

	i = 0;
	while (to_free[i])
		free(to_free[i++]);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	manage_heredoc(t_token *token, int *pipes)
{
	int	i;

	if (!token->heredoc)
		return ;
	i = ft_strlen(token->heredoc);
	write(pipes[0], token->heredoc, i);
	close(pipes[1]);
	close(pipes[0]);
}
