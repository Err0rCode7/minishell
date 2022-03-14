
#include "minishell.h"

int	pt_exit_status(char *str)
{
	prt_error(str);
	g_exit_status = 1;
	return (0);
}
