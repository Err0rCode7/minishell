/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:53 by taewan            #+#    #+#             */
/*   Updated: 2022/04/07 10:23:06 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putendl_fd("  ", STDOUT);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  \b\b\a", STDOUT);
	}
}

void	ignore_sig(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		ft_putendl_fd("", STDOUT);
		// g_exit_status = 130;
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		ft_putstr_fd("Quit: 3\b\b\b\b\b\b\b", STDOUT);
	}
}

void	ignore_signal(void (*handle)(int))
{
	(void)handle;
	signal(SIGINT, ignore_sig);
	signal(SIGQUIT, ignore_sig);
}

void	init_signal(void (*handler)(int))
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
