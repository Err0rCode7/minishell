/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:06 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 00:04:38 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pt_env(char **envp, char *prefix)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		write(STDOUT, prefix, ft_strlen(prefix));
		write(STDOUT, envp[i], ft_strlen(envp[i]));
		write(STDOUT, "\n", 1);
	}
	g_exit_status = 0;
	return (0);
}
