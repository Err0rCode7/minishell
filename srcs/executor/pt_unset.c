/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:27 by taewan            #+#    #+#             */
/*   Updated: 2022/04/29 01:07:40 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	is_valid_key(char *key)
{
	int	i;

	i = -1;
	if (key && ft_isdigit(*key))
		return (FALSE);
	while (key[++i])
		if (!ft_isdigit(key[i]) && !ft_isalpha(key[i]))
			return (FALSE);
	return (TRUE);
}

int	pt_unset(char ***envp, char **new_argv, int j, t_data *data)
{
	int		i;

	g_exit_status = 0;
	i = 0;
	while (new_argv[i])
		i++;
	if (i == 1)
	{
		print_oneline_err(data, ft_strdup("unset: not enough arguments\n"));
		g_exit_status = 1;
		return (0);
	}
	while (new_argv[j])
	{
		if (!is_valid_key(new_argv[j]))
		{
			print_oneline_err(
				data,
				get_oneline(MSG_IDDENTIFIER_ERR, "unset", new_argv[j], 1));
			continue ;
		}
		i = get_env_var(new_argv[j], *envp);
		if ((*envp)[i])
			rm_env_var(i, envp);
		j++;
	}
	return (0);
}
