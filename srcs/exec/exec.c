#include "minishell.h"
#include "exec.h"

volatile extern int	g_status;

/*TODO: create a new pipe structure so it can talk in a new pipe;
 * */
T_BOOL	execute_pipe(t_token *leaf, t_container *book, t_pipes pipes)
{
	int		new_pipes[2];
	t_pipes	new_pipe;
	int		pid;

	book->in_pipe = TRUE;
	if (pipe(new_pipes) == -1)
		return (FALSE);
	new_pipe.in = new_pipes[0];
	new_pipe.out = new_pipes[1];
	pid = fork1();
	if (!pid)
	{

	}
	if (!r_executor(leaf->left, book, new_pipe) \
	|| !r_executor(leaf->right, book, new_pipe))
	{
		close(new_pipes[0]);
		close(new_pipes[1]);
		return (FALSE);
	}
	close(new_pipes[0]);
	close(new_pipes[1]);
	book->in_pipe = FALSE;
	return (TRUE);
}

T_BOOL	r_executor(t_token *leaf, t_container *book, t_pipes pipes)
{
	if (g_status == EXECUTION)
	{
		if (!leaf)
			return (SUCCESS);
		else if (leaf->type == AND)
			return (r_executor(leaf->left, book, pipes) \
		&& r_executor(leaf->right, book, pipes));
		else if (leaf->type == OR)
		{
			if (r_executor(leaf->left, book, pipes))
				return (SUCCESS);
			if (g_status != EXECUTION)
				return (ERROR);
			return (r_executor(leaf->right, book, pipes));
		}
		else if (leaf->type == APD_REDIR || leaf->type == IN_REDIR \
		|| leaf->type == OUT_REDIR || leaf->type == HERDOC)
			return (execute_redir(leaf, book, pipes));
		else if (leaf->type == PIPE)
			return (execute_pipe(leaf, book, pipes));
		else if (leaf->type == COMMAND)
			return (exec_one_cmd(leaf, book, pipes));
	}
	return (ERROR);
}

T_BOOL exec(t_container *book)
{
	struct s_pipes	pipes;
	
	pipes.in = 0;
	pipes.out = 1;
	g_status = EXECUTION;
	return (r_executor(book->head, book, pipes));
}
