# include "minishell.h"

T_BOOL	check_nmbr_args(t_token *leaf)
{
	int	i;

	i = 0;
	while (leaf->args[i])
		i++;
	if (i > 1)
		return (TRUE);
	return (FALSE);
}

int check_digit(t_token *leaf)
{
	int	i;

	i = 0;
	while (leaf->args[1][i])
	{
		if (!ft_isdigit(leaf->args[1][i]))
		{
			my_print_error("minishell-2.0: exit:");
			my_print_error(leaf->args[1]);
			my_print_error("numeric argument required");
		}
		i++;
	}
	if (i == 1)
		return (1);
	return (0);
}

/*	TODO:
 *  	- [x] if there is arg, get it in 256
 * 		- [x] if the arg is not numeric error
 * 		- [x] if more than one arg error and continue
 * 		- [x] free then write exit\n and then exit with arg given
 * 		- [x] if no arg exit with the old exit+statuts
 * 		- [x] if in pipe errno  = 1
 * */
void my_exit(t_token *leaf, t_container *book)
{
	int	tmp;

	if (book->in_pipe || check_nmbr_args(leaf))
	{
		errno = 1;
		if (check_nmbr_args(leaf))
			my_print_error("exit\nminishell-2.0: exit: too many arguments");
		return ;
	}
	my_print_error("exit");
	tmp = check_digit(leaf);
	if (tmp == 1)
		tmp = ft_atoi(leaf->args[1]);
	free_all(book);
	if (!tmp)
		exit(255);
	exit((unsigned char) tmp);
}