/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:14 by taewan            #+#    #+#             */
/*   Updated: 2022/04/29 01:04:33 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isdigit_eachstr(char *str)
{
	int	idx;
	int	sign;

	idx = 0;
	sign = 0;
	if (str[idx] == '-' || str[idx] == '+')
	{
		sign = 1;
		idx++;
	}
	while (str[idx])
	{
		if (!ft_isdigit(str[idx]) || idx > 19 + sign)
			return (FALSE);
		idx++;
	}
	if ((str[0] == '+' && (ft_strcmp(str, "+9223372036854775807") > 0))
		|| (str[0] == '-' && (ft_strcmp(str, "-9223372036854775808") > 0))
		|| (!sign && ft_strcmp(str, "9223372036854775807") > 0))
		return (FALSE);
	return (TRUE);
}

static void	process_exit(char **cmd, int cnt, int pipeflag, t_data *data)
{
	if (cnt == 1)
		print_pipe_exit(pipeflag, data);
	else if (cnt == 2 && ft_isdigit_eachstr(cmd[1]))
	{
		print_pipe_exit(pipeflag, data);
		g_exit_status = ft_atoi(cmd[1]) % 256;
	}
	else if (cnt > 2 && ft_isdigit_eachstr(cmd[1]))
	{
		print_execute_err_1("exit", "too many arguments", pipeflag, data);
		return ;
	}
	else
	{
		print_oneline_err(data,
			get_oneline_exitpipe(
				"exit", cmd[1], "numeric argument required", pipeflag));
		exit(255);
	}
	exit(g_exit_status);
}

int	pt_exit(char **cmd, int pipeflag, t_data *data)
{
	int	cnt;

	cnt = 0;
	while (cmd[cnt] != NULL)
		cnt++;
	process_exit(cmd, cnt, pipeflag, data);
	return (0);
}
