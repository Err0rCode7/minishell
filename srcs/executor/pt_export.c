/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:18 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 00:04:56 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_env(int env_idx, char ***envp)
{
	char	**new;
	char	**cur;
	int		i;

	cur = *envp;
	new = malloc(sizeof(char *) * (env_idx + 1));
	if (!new)
		exit(1);
	i = -1;
	while (cur[++i] && i < env_idx)
	{
		new[i] = ft_strdup(cur[i]);
		free(cur[i]);
	}
	free(cur);
	new[env_idx] = NULL;
	*envp = new;
	return (new);
}

int	is_redipe(char *str)
{
	if (ft_strncmp(str, ">", 1) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (TRUE);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (TRUE);
	return (FALSE);
}

int	get_env_var(char *key, char **envp)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strjoin(key, "=");
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], tmp, ft_strlen(tmp)))
		{
			free(tmp);
			return (i);
		}
	}
	free(tmp);
	return (i);
}

static void	add_env(char ***envp, char *new_argv)
{
	char	*i;
	char	*key;
	int		env_idx;

	i = ft_strchr(new_argv, '=');
	if (i == NULL)
		return ;
	key = ft_substr(new_argv, 0, i - new_argv);
	env_idx = get_env_var(key, *envp);
	free(key);
	if ((*envp)[env_idx] == NULL)
		realloc_env(env_idx + 1, envp);
	else
		free((*envp)[env_idx]);
	(*envp)[env_idx] = ft_strdup(new_argv);
	if (!(*envp)[env_idx])
		exit(1);
}

int	pt_export(char ***envp, char **new_argv)
{
	int		i;

	g_exit_status = 0;
	i = 0;
	while (new_argv[i])
		i++;
	if (i == 1)
		pt_env(*envp, PREFIX_EXPORT);
	while (*++new_argv)
	{
		if (is_redipe(*new_argv))
		{
			g_exit_status = 1;
			prt_cmd_err_shellname(MSG_IDDENTIFIER_ERR, "export", *new_argv);
			continue ;
		}
		add_env(envp, *new_argv);
	}
	return (0);
}
