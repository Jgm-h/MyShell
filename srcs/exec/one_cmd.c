#include "minishell.h"

char	**get_env_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
		paths[i] = ft_strjoin(paths[i], "/");
	return (paths);
}

char	*find_path(t_container *book, int i, char *arg)
{
	char	**env_paths;
	char	*pathed;

	if (!access(arg, F_OK))
		return (arg);
	env_paths = get_env_paths(book->envp);
	if (!env_paths)
		return (NULL);
	while (env_paths[++i])
	{
		pathed = ft_strjoin(ft_strdup(env_paths[i]), arg);
		if (!pathed)
			return (NULL);
		if (!access(pathed, F_OK))
		{
			free_split(env_paths); //check que j'ai pas deja tout free
			return (pathed);
		}
	}
	return (NULL);
}

void	child(int *pipes, t_token *leaf, t_pipes pipes_exec, t_container *book)
{
	if (dup2(pipes_exec.in, STDIN_FILENO) == -1 \
	|| dup2(pipes_exec.out, STDOUT_FILENO) == -1)
		return ;
	close(pipes_exec.in);
	close(pipes_exec.out);
	if (leaf->heredoc && !pipes_exec.in)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[0]);
		close(pipes[1]);
	}
	execve(leaf->args[0], leaf->args, book->envp);
	my_print_error("minishell: execution failed");
}

/*TODO:
 * 	- [ ] check how heredoc and STDIN interact
 * */
int	execute(t_token *leaf, t_container *book, t_pipes pipes_exec)
{
	int		pipes[2];

	if (leaf->heredoc)
	{
		if (pipe(pipes) == -1)
			my_perror("pipe", book);
	}
	if (fork1() == 0)
	{
		if (leaf->heredoc)
			dup2(pipes[1], STDIN_FILENO);
		if (check_builtin(leaf->args[0]))
			execute_builtins(leaf, book, pipes_exec);
		child(pipes, leaf, pipes_exec, book);
	}
	dup2(pipe[1], STDOUT_FILENO);
	if (leaf->heredoc)
		manage_heredoc(leaf, pipes);
}

int	exec_one_cmd(t_token *leaf, t_container *book, t_pipes pipes)
{
	char	*path;

	leaf->args = ft_split(leaf->argv, ' ');
	if (!leaf->args)
		return (FALSE);
	path = find_path(book, -1, leaf->args[0]);
	if (!path)
	{
		ft_putstr_fd((char *)"minishell: ", STDERR_FILENO);
		ft_putstr_fd(leaf->args[0], STDERR_FILENO);
		ft_putstr_fd((char *)": command not found\n", STDERR_FILENO);
		book->exit_status = 127;
		return (FALSE);
	}
	free(leaf->args[0]);
	leaf->args[0] = path;
	return (execute(leaf, book, pipes));
}
