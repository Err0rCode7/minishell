/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 15:03:01 by seujeon           #+#    #+#             */
/*   Updated: 2022/03/23 15:13:56 by seujeon          ###   ########.fr       */
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
		exit(1);
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
