#include "builtins.h"

T_BOOL	echo(t_token *leaf, t_pipes pipes)
{
	T_BOOL	option;
	int		i;

	i = 1;
	option = FALSE;
	while (!ft_strncmp(leaf->args[1], "-n", 3))
	{
		option = TRUE;
		i++;
	}
	while (leaf->args[i])
	{
		if (write(pipes.out, leaf->args[i], ft_strlen(leaf->args[i])) == -1)
			return (ERROR);
		if (leaf->args[i + 1])
			if (write(pipes.out, " ", 1) == -1)
				return (ERROR);
		i++;
	}
	if (option)
		return (SUCCESS);
	if (write(pipes.out, "\n", 1) == -1)
		return (ERROR);
	return (SUCCESS);
}
