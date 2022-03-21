
#include "error.h"

void	error_exit(char *msg, int exitcode)
{
	ft_putstr_fd(RED, 2);
	write(2, "Error : ", 8);
	ft_putstr_fd(RESET, 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(exitcode);
}

void	prterr_exit(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

int	prt_error(char *msg)
{
	ft_putstr_fd(RED, 2);
	write(2, "Error : ", 8);
	ft_putstr_fd(RESET, 2);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	return (0);
}

void	prt_cmd_err_shellname(char *msg, char *cmd, char *arg)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	if (arg != NULL && arg[0] != 0)
	{
		write(2, "`", 1);
		write(2, arg, ft_strlen(arg));
		write(2, "\': ", 3);
	}
	write(2, msg, ft_strlen(msg));
	write(1, "\n", 1);
}
