/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_exit_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:10 by taewan            #+#    #+#             */
/*   Updated: 2022/04/06 20:35:07 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pt_exit_status(char *str)
{
	prt_error(str);
	g_exit_status = 1;
	exit(1);
	return (0);
}

void	print_pipe_exit(int pipeflag)
{
	if (pipeflag)
		return ;
	write(STDOUT, "exit\n", 5);
}

int	print_execute_err_1(char *token, char *err_msg, int pipeflag)
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

int	print_execute_err_3(char *head, char *token, char *err_msg)
{
	ft_putstr_fd(head, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putstr_fd(token, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(err_msg, STDERR);
	return (-1);
}