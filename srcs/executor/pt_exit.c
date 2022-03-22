/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewakim <taewakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:14 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 15:09:33 by taewakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isdigit_eachstr(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (!ft_isdigit(str[idx]))
			return (0);
		idx++;
	}
	return (1);
}

static int	print_execute_err_1(char *token, char *err_msg)
{
	ft_putstr_fd("exit\n", STDERR);
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

static void	process_exit(char **cmd, int cnt)
{
	if (cnt == 1)
		write(STDOUT, "exit\n", 5);
	else if (cnt == 2 && ft_isdigit_eachstr(cmd[1]))
	{
		write(STDOUT, "exit\n", 5);
		g_exit_status = ft_atoi(cmd[1]) % 256;
	}
	else if (cnt > 2 && ft_isdigit_eachstr(cmd[1]))
	{
		print_execute_err_1("exit", "too many arguments");
		return ;
	}
	else
	{
		write(STDOUT, "exit\n", 5);
		print_execute_err_2("exit", cmd[1], "numeric argument required");
		exit(255);
	}
	exit(g_exit_status);
}

int	pt_exit(char **cmd)
{
	int	cnt;

	g_exit_status = 0;
	cnt = 0;
	while (cmd[cnt] != NULL)
		cnt++;
	process_exit(cmd, cnt);
	return (0);
}
