#include "minishell.h"
#include "exec.h"

void exec(t_container *book)
{
	if (!book->head->next)
		exec_one_cmd(book, book->head);
}

void exec_one_cmd(t_container *book, t_token *node)
{
	char	*path;

	path = find_path(book, node);
	node->argv[0] = "ls";
	if (!path) //should do something
		;
	book->exit_status = execve(path, node->argv, book->envp);
	printf("%d\n", errno);
	perror(strerror(errno));
}

/* tries all the paths in env PATH
 * todo:
 * 	- have this fonction also check without adding any path to the command
 * */
char *find_path(t_container *book,t_token *node)
{
	int		i;
	char	*path;

	i = 0;
	while (book->paths[i])
	{
		path = ft_strjoin(book->paths[i], node->cmd);
		if (!access(path, F_OK))
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
