#include "minishell.h"
#include "exec.h"

volatile extern int	g_status;

t_pipes	init_pipe(T_BOOL first, T_BOOL last)
{
	t_pipes ret;
	int		fd[2];

	pipe(fd);
	if (first)
	{
		ret.in = STDIN_FILENO;
		close(fd[0]);
	}
	else
	{
		dup2(STDIN_FILENO, fd[0]);
		close(fd[0]);
	}
	if (last)
	{
		ret.out = STDOUT_FILENO;
		close(fd[1]);
	}
	else
	{
		dup2(STDOUT_FILENO, fd [1]);
		close(fd[1]);
	}
	return (ret);
}

t_token *find_left(t_token *to_find)
{
	while (to_find->left)
		to_find = to_find->left;
	return (to_find);
}

/* TODO;
 * 	- [ ] code find left and find right
 * 	- [ ] I need to close the pipes at the end, but not close STDIN & STDOUT and only the one i used
 * 	- [ ] I need to know if i'm in a pipe for the execution
 * 	- [ ] if i have a out redir i should fill the redir and give the pipe the std_out (test: cat>1 |grep test)
 * */
T_BOOL	execute_pipe(t_token *leaf, t_container *book, t_pipes pipes)
{
	t_pipes	left;
	t_pipes	right;

	left = init_pipe(find_left(leaf)->first, find_left(leaf)->last);
	right = init_pipe(leaf->right->first, leaf->right->last);
	r_executor(leaf->left, book, left);
	//close_fd(find_left(leaf->left)->first, find_left(leaf->left)->last);
	r_executor(leaf->left, book, right);
	//close_fd(find_right(leaf->right)->first, find_right(leaf->right)->last);
	return (SUCCESS);
}

/* TODO:
 * 	- [ ] waitpid 0 for each sub group
 * 	- [ ] to waitpid 0 i need to know how many cmd processes i have running
 * 	- [ ] check les macros pour chacun des process:
 * 		- [ ] un process qui est arrete par signal c'est une erreur
 * 		- [ ] un process qui est arrete par un code != 0 c'est pas une erreur
 * 	- [ ] check status between subgroups
 *  - [ ] remettre a zero le nombre de process
 * */
T_BOOL exec_and(t_token *leaf, t_container *book)
{

	waitpid();
	r_executor(leaf->left, book, )
		return (r_executor(leaf->right, book, pipes));
	else
		return (ERROR);
}

/* TODO:
 * 	- [ ] waitpid 0 for each sub group
 * 	- [ ] check status between subgroups
* - [ ] remettre a zero le nombre de process
 * */
T_BOOL exec_or(t_token *leaf, t_container *book)
{
	if (r_executor(leaf->left, book, pipes))
		return (SUCCESS);
	if (g_status != EXECUTION)
		return (ERROR);
	return (r_executor(leaf->right, book, pipes));
}

T_BOOL	r_executor(t_token *leaf, t_container *book, t_pipes pipes)
{
	if (g_status == EXECUTION) {
		if (!leaf)
			return (SUCCESS);
		else if (leaf->type == AND)
			return (exec_and(leaf, book));
		else if (leaf->type == OR)
			return (exec_or(leaf, book));
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

/*TODO:
 * - [ ] i should wait pid -1 here also
 * - [ ] handle status for subgroup here
 * so somehow i have a master group that monitors all the subgroups
 * maybe i should check if the head is a && or an || (and then maybe i should have a master group)
 * - [ ] remettre a zero le nombre de process
 * */
T_BOOL exec(t_container *book)
{
	struct s_pipes	pipes;

	pipes.in = STDIN_FILENO;
	pipes.out = STDOUT_FILENO;
	g_status = EXECUTION;
	if (!r_executor(book->head, book, pipes))
		// handle g_status
		//waitpid all groups
	return (r_executor(book->head, book, pipes));
}
