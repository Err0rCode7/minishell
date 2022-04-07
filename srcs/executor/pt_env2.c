/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:06 by taewan            #+#    #+#             */
/*   Updated: 2022/04/07 02:19:48 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_invalid_arg_null(char *key, char *value)
{
	if (!key || !value)
	{
		if (key)
			free(key);
		if (value)
			free(value);
		return (1);
	}
	return (0);
}

char	*get_last(char **arr)
{
	if (!*arr)
		return NULL;
	while (*arr)
		arr++;
	return *(arr - 1);
}

void	add_key_value(char ***envp, char *value, char *key)
{
	char	*buf;
	char	*tmp;

	if (check_invalid_arg_null(key, value))
		return ;
	if (!ft_strncmp("echo", value, 4))
	{
		free(value);
		free(key);
		return ;
	}
	tmp = ft_strjoin(key, "=");
	free(key);
	buf = ft_strjoin(tmp, value);
	free(value);
	free(tmp);
	add_env(envp, buf);
	free(buf);
}