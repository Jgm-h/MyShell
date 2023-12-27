

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"


enum e_token_type{
	AND,
	OR,
	PIPE,
	HERDOC,
	IN_REDIR,
	APD_REDIR,
	OUT_REDIR,
	COMMAND,
};

enum e_status{
	NEW_LINE,
	EXECUTION,
	HEREDOC,
	ABORT_HEREDOC
};

typedef struct s_pipes
{
	int	in;
	int	out;
}	t_pipes;

typedef struct s_token
{
	enum e_token_type	type;
	char				*argv;
	char				**args;
	char				*heredoc;
	T_BOOL				first;
	T_BOOL				last;
	struct s_token		*left;
	struct s_token		*right;
}	t_token;

typedef struct s_container{
	t_token	*head;
	char	**envp;
	char	**paths;
	char	*prompt;
	char	*cwd;
	int		exit_status;
	T_BOOL	in_pipe;
}t_container;

int		get_index_env(char **envp, char *key);
void	add_var(t_container *book, char *key, char *value);
void	free_split(char **to_free);
int		fork1(void);
void	my_perror(char *str, t_container *book);
void	manage_heredoc(t_token *leaf, int *pipes);
int		my_dup2(int fd_file, int to_dup);
T_BOOL	my_access(char *file, int flag);
void	export_value(char *env, char *key, char *value);
void	replace_path(t_token *leaf, char *pwd);
T_BOOL	check_builtin(char *str);
int my_print_error(char *str);
void	free_array(char **array);

#endif //MINISHELL_UTILS_H
