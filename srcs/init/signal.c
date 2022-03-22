/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:53 by taewan            #+#    #+#             */
/*   Updated: 2022/03/23 00:24:57 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int signo)
{
	if (signo == SIGINT)
	{
		printf("minishell$ \n");
		// rl_on_new_line();
		// rl_redisplay();
		// ft_putendl_fd("  ", STDOUT);
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
		// g_exit_status = 130;
	}
	// else if (signo == SIGQUIT)
	// {
	// 	rl_on_new_line();
	// 	rl_redisplay();
	// 	ft_putstr_fd("  \b\b\a", STDOUT);
	// }
	// else
	// {
	// 	printf("exit");
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
	// }
	
    if (rl_on_new_line() == -1)
        exit(1);
    rl_replace_line("", 1);
    rl_redisplay();
}

void	ignore_sig(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		ft_putendl_fd("", STDOUT);
		g_exit_status = 130;
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		ft_putstr_fd("Quit: 3\n", STDOUT);
	}
}

void	ignore_signal(void (*handle)(int))
{
	(void)handle;
	signal(SIGINT, ignore_sig);
	signal(SIGQUIT, ignore_sig);
}

// void	heredoc_signal(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		exit(0);
// 	}
// }

void	init_signal(void (*handler)(int))
{
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
