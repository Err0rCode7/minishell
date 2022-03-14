
#include "minishell.h"

int	pt_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		write(STDOUT, envp[i], ft_strlen(envp[i]));
		write(STDOUT, "\n", 1);
	}
	g_exit_status = 0;
	return (0);
}
