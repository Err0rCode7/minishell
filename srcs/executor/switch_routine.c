/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:34 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 00:01:37 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	switch_routine(char **new_argv, t_data *data)
{
	if (!*new_argv)
		return (0);
	if (ft_strcmp(new_argv[0], "exit") == 0)
		return (pt_exit(new_argv));
	if (ft_strcmp(new_argv[0], "cd") == 0)
		return (pt_cd(new_argv, data));
	if (ft_strcmp(new_argv[0], "export") == 0)
		return (pt_export(&data->envp, new_argv));
	if (ft_strcmp(new_argv[0], "unset") == 0)
		return (pt_unset(&data->envp, new_argv));
	if (ft_strcmp(new_argv[0], "env") == 0)
		return (pt_env(data->envp, ""));
	if (ft_strcmp(new_argv[0], "pwd") == 0)
		return (pt_pwd());
	if (ft_strcmp(new_argv[0], "echo") == 0)
		return (pt_echo(new_argv));
	return (1);
}
