
#include "minishell.h"

static void	rm_env_var(int arg_idx, char ***envp)
{
	int			i;
	int			var_count;
	const char	**envs = (const char **)*envp;

	free((void *)envs[arg_idx]);
	envs[arg_idx] = NULL;
	i = arg_idx;
	var_count = arg_idx + 1;
	while (envs[i + 1])
	{
		envs[i] = envs[i + 1];
		i++;
		var_count++;
	}
	envs[i] = envs[i + 1];
	*envp = realloc_env(var_count - 1, envp);
}

int	pt_unset(char ***envp, char **new_argv)
{
	int		i;
	int		var_idx;

	g_exit_status = 0;
	i = 0;
	while (new_argv[i])
		i++;
	if (i == 1)
	{
		ft_putendl_fd("unset: not enough arguments", STDERR);
		g_exit_status = 1;
		return (0);
	}
	while (*++new_argv)
	{
		if (is_redipe(*new_argv)) {
			prt_cmd_err_shellname(MSG_IDDENTIFIER_ERR, "unset", *new_argv);
			continue ;
		}
		var_idx = get_env_var(*new_argv, *envp);
		if ((*envp)[var_idx])
			rm_env_var(var_idx, envp);
	}
	return (0);
}
