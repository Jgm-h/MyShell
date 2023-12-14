#include "minishell.h"

volatile extern int	g_status;

static void	handle_sigquit(void)
{
	return ;
}

static void	handle_sigint(void)
{
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = NEW_LINE;
}

void	signal_handler(int signal)
{
	if (signal == SIGQUIT)
		handle_sigquit();
	if (signal == SIGINT)
		handle_sigint();
}