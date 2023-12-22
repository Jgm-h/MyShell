#include "exec.h"

volatile extern int	g_status;

int	get_redir_fd_side(char *file, enum e_token_type type)
{
	int	fd;

	if (type == IN_REDIR)
	{
		if (!my_access(file, R_OK))
			return (-1);
		fd = open(file, O_RDONLY);
	}
	if (type == OUT_REDIR || type == APD_REDIR)
	{
		if (!my_access(file, W_OK))
			return (-1);
		fd = open(file, O_WRONLY);
	}
	if (fd == -1)
		perror("minishell-2.0: open failed");
	return (fd);
}

T_BOOL	inside_heredoc(t_token *leaf, char *input, char *eof)
{
	if (!ft_strncmp(eof, input, ft_strlen(eof)))
	{
		free(input);
		return (FALSE);
	}
	leaf->heredoc = ft_strjoin(leaf->heredoc, input);
	if (!leaf->heredoc)
		my_perror("minishell-2.0: malloc failed");
	return (TRUE);
}

char	*get_eof(t_token *leaf)
{
	if (leaf->right->type == COMMAND)
		return (leaf->right->argv);
	return (leaf->right->left->argv);
}

T_BOOL	get_heredoc(t_token *leaf)
{
	char	*input;
	char	*eof;

	eof = get_eof(leaf);
	while (g_status == HEREDOC)
	{
		input = readline("> ");
		if (!input)
		{
			g_status = ABORT_HEREDOC;
			return (FALSE);
		}
		if (!inside_heredoc(leaf, input, eof))
			continue ;
	}
	g_status = EXECUTION;
	return (TRUE);
}

unsigned int	one_redir(t_token *leaf, char *file, t_pipes pipes)
{
	int		fd_file;

	if (leaf->type != HERDOC)
	{
		fd_file = get_redir_fd_side(file, leaf->type);
		if (fd_file == -1)
			return (FALSE);
	}
	else
	{
		g_status = HEREDOC;
		return (get_heredoc(leaf));
	}
	if (leaf->type == OUT_REDIR || leaf->type == APD_REDIR)
	{
		if (my_dup2(fd_file, pipes.out) == -1)
			return (FALSE);
	}
	if (leaf->type == IN_REDIR)
	{
		if (my_dup2(fd_file, pipes.in) == -1)
			return (FALSE);
	}
	close(fd_file);
	return (TRUE);
}

T_BOOL	redir_management(t_token *leaf, t_pipes pipes)
{
	if (leaf->right->type == COMMAND)
	{
		if (!one_redir(leaf, leaf->right->argv, pipes))
			return (FALSE);
		leaf = leaf->right;
	}
	while (leaf && leaf->type != COMMAND)
	{
		if (leaf->right->type == COMMAND)
		{
			if (!one_redir(leaf, leaf->right->argv, pipes))
				return (FALSE);
		}
		else
		{
			if (!one_redir(leaf, leaf->right->left->argv, pipes))
				return (FALSE);
		}
		leaf = leaf->right;
	}
	return (TRUE);
}

T_BOOL	execute_redir(t_token *leaf, t_container *book, t_pipes pipes)
{
	if (!redir_management(leaf, pipes))
	{
		book->exit_status = errno;
		return (FALSE);
	}
	book->exit_status = exec_one_cmd(leaf->left, book, pipes);
	if (!book->exit_status)
		return (TRUE);
	return (FALSE);
}
