
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
