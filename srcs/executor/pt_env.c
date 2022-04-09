/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:06 by taewan            #+#    #+#             */
/*   Updated: 2022/04/09 12:58:34 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_env(char **new_argv)
{
	char	**tmp;
	int		i;

	tmp = ft_split("", 0);
	if (!tmp)
		exit(1);
	i = 0;
	while (new_argv[++i])
	{
		add_env(&tmp, new_argv[i]);
	}
	i = -1;
	while (tmp[++i])
		printf("%s\n", tmp[i]);
	ft_split_free(tmp);
}

static int	set_env_error(char *new_argv)
{
	if (ft_strchr(new_argv, '=') == NULL)
	{
		print_execute_err_3("env", new_argv, MSG_FILE_NOT_FOUND_ERR);
		g_exit_status = 127;
		return (1);
	}
	if (new_argv && new_argv[0] == '=')
	{
		print_execute_err_3("env", "setenv =", MSG_INVALID_ARG_ERR);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

int	pt_env(char **envp, char *prefix, char **new_argv)
{
	int	i;

	i = 0;
	while (new_argv[++i])
	{
		if (set_env_error(new_argv[i]))
			return (0);
	}
	i = -1;
	while (envp[++i])
	{
		write(STDOUT, prefix, ft_strlen(prefix));
		write(STDOUT, envp[i], ft_strlen(envp[i]));
		write(STDOUT, "\n", 1);
	}
	set_env(new_argv);
	g_exit_status = 0;
	return (0);
}
