/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:06 by taewan            #+#    #+#             */
/*   Updated: 2022/04/06 21:09:44 by seujeon          ###   ########.fr       */
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

void	add_key_value(char ***envp, char *value, char *key)
{
	char	*buf;
	char	*tmp;

	if (!ft_strncmp("echo", value, 4))
		return ;
	if (check_invalid_arg_null(key, value))
		return ;
	tmp = ft_strjoin(key, "=");
	free(key);
	buf = ft_strjoin(tmp, value);
	free(tmp);
	add_env(envp, buf);
	free(buf);
}