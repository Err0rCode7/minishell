
#include "minishell.h"

int	pt_pwd(void)
{
	char	*tmp;

	tmp = getcwd(0, MAX_DIRLEN);
	g_exit_status = 0;
	printf("%s\n", tmp);
	free(tmp);
	return (0);
}
