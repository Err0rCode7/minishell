/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewakim <taewakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:03:01 by seujeon           #+#    #+#             */
/*   Updated: 2022/04/30 12:03:54 by taewakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_signal(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \n");
		exit(-42);
	}
	else if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(STDOUT, "  \b\b", 4);
	}
}

int	handle_endline(char *line)
{
	if (line)
		return (FALSE);
	write(1, "\033[1A", ft_strlen("\033[1A"));
	write(1, "\033[2C", ft_strlen("\033[2C"));
	return (TRUE);
}

void	ignore_all_signal_a(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		g_exit_status = 130;
	}
	else if (signo == SIGQUIT)
		g_exit_status = 131;
}

void	ignore_all_signal(int signo)
{
	(void)signo;
}

void	ignore_all_sig(void (*handle)(int))
{
	signal(SIGINT, handle);
	signal(SIGQUIT, handle);
}
