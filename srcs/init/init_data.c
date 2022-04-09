/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:45 by taewan            #+#    #+#             */
/*   Updated: 2022/04/09 13:03:21 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size_envp(char **str)
{
	int	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

char	**dup_envp(char **envp)
{
	char	**result;
	int		i;

	result = malloc(sizeof(char *) * (get_size_envp(envp) + 1));
	if (result == NULL)
		exit(1);
	i = -1;
	while (envp[++i])
	{
		result[i] = ft_strdup(envp[i]);
		if (!result[i])
			exit(1);
	}
	result[i] = NULL;
	return (result);
}

void	init_set(t_data *data, char **envp)
{
	init_signal(handle_signal);
	prt_image();
	data->envp = dup_envp(envp);
	data->home = find_home("", envp);
}

void	init_data(t_data *data, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	data->syntax = STX_OK;
	data->pipecnt = 0;
	data->roe_flag = 0;
	data->wordcnt = 0;
	data->pipeflag = FALSE;
	data->tmp = 0;
}
