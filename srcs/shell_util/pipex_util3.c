/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:20:50 by taewan            #+#    #+#             */
/*   Updated: 2022/04/10 13:29:43 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_dir(char *name)
{
	struct stat	buf;

	stat(name, &buf);
	return (S_ISDIR(buf.st_mode));
}

int	ft_access2(char *name, int option)
{
	struct stat	buf;

	if (!name)
		return (FALSE);
	stat(name, &buf);
	return ((buf.st_mode & option) != 0
		|| (buf.st_mode & (option >> 3)) != 0
		|| (buf.st_mode & (option >> 6)) != 0);
}

int	find_char_start(char *cmd)
{
	int	i;

	i = 0;
	while (is_space(cmd[i]))
		i++;
	return (i);
}

int	only_dot(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == '.')
		i++;
	if (!cmd[i])
		return (1);
	return (0);
}
