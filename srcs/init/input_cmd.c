/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewakim <taewakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:49 by taewan            #+#    #+#             */
/*   Updated: 2022/04/26 17:42:17 by taewakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(char **buf)
{
	*buf = readline("minishell$ ");
	if (!*buf)
	{
		printf("\033[1A\033[10C exit\n");
		exit(g_exit_status);
	}
	return (*buf);
}
