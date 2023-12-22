#include "minishell.h"

char	**get_env_paths(char **envp)
{
	int		i;
	char	**paths;
	char	*to_free;

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

/*should test for existence
 * */
char	*find_path(t_token *leaf, t_container *book, int i, char *arg)
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
			free_split(env_paths);
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
	perror("minishell: execution failed");
}

int	execute(t_token *leaf, t_container *book, t_pipes pipes_exec)
{
	int		status;
	int		pipes[2];

	if (leaf->heredoc && !pipes_exec.in)
	{
		if (pipe(pipes) == -1)
			my_perror("pipe");
	}
	// if check builtin
	// execute_builtins;
	if (fork1() == 0)
		child(pipes, leaf, pipes_exec, book);
	status = 0;
	if (leaf->heredoc && !pipes_exec.in)
		manage_heredoc(leaf, pipes);
	if (wait(&status) == -1)
		my_perror("waitpid");
	return (WEXITSTATUS(status));
}

int	exec_one_cmd(t_token *leaf, t_container *book, t_pipes pipes)
{
	char	*path;

	leaf->args = ft_split(leaf->argv, ' ');
	if (!leaf->args)
		return (FALSE);
	path = find_path(leaf, book, -1, leaf->args[0]);
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
