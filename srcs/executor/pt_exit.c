/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:14 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 22:46:57 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isdigit_eachstr(char *str)
{
	int	idx;
	int sign;

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

static void print_pipe_exit(int pipeflag)
{
	if (pipeflag)
		return ;
	write(STDOUT, "exit\n", 5);
}

static int	print_execute_err_1(char *token, char *err_msg, int pipeflag)
{
	print_pipe_exit(pipeflag);
	ft_putstr_fd("minishell", STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(token, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(err_msg, STDERR);
	return (-1);
}

int	print_execute_err_2(char *token1, char *token2, char *err_msg)
{
	ft_putstr_fd("minishell", STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(token1, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(token2, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(err_msg, STDERR);
	return (-1);
}

static void	process_exit(char **cmd, int cnt, int pipeflag)
{
	if (cnt == 1)
		print_pipe_exit(pipeflag);
	else if (cnt == 2 && ft_isdigit_eachstr(cmd[1]))
	{
		print_pipe_exit(pipeflag);
		g_exit_status = ft_atoi(cmd[1]) % 256;
	}
	else if (cnt > 2 && ft_isdigit_eachstr(cmd[1]))
	{
		print_execute_err_1("exit", "too many arguments", pipeflag);
		return ;
	}
	else
	{
		print_pipe_exit(pipeflag);
		print_execute_err_2("exit", cmd[1], "numeric argument required");
		exit(255);
	}
	exit(g_exit_status);
}

int	pt_exit(char **cmd, int pipeflag)
{
	int	cnt;

	g_exit_status = 0;
	cnt = 0;
	while (cmd[cnt] != NULL)
		cnt++;
	process_exit(cmd, cnt, pipeflag);
	return (0);
}
