/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:02 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 00:01:03 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option_n(char *argv)
{
	int	i;

	if (ft_strncmp(argv, "-n", 2) != 0)
		return (FALSE);
	i = 2;
	while (argv[i])
	{
		if (argv[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	pt_echo(char **new_argv)
{
	int	i;
	int	option;

	i = 1;
	option = FALSE;
	while (new_argv[i] && check_option_n(new_argv[i]))
	{
		option = TRUE;
		i++;
	}
	while (new_argv[i])
	{
		ft_putstr_fd(new_argv[i], STDOUT);
		if (new_argv[i + 1] != NULL)
			ft_putchar_fd(' ', STDOUT);
		i++;
	}
	if (option == FALSE)
		ft_putchar_fd('\n', STDOUT);
	g_exit_status = 0;
	return (0);
}
