/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewakim <taewakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:45 by taewan            #+#    #+#             */
/*   Updated: 2022/04/30 12:00:27 by taewakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size_envp(char **str)
{
	int	i;

	i = 0;
	while (str[i])
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
	data->oldpwd = FALSE;
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
	data->last = 0;
	data->redrflag = 0;
	data->last_pid = 0;
	data->rd_out_flag = 0;
	data->errmsg_fd = 2;
	data->dev_flag = 0;
	data->heredoc_sigint = 0;
}

void	init_origin_fd(int *original_fd)
{
	if (dup2(original_fd[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(original_fd[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
}
