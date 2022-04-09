/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:49 by taewan            #+#    #+#             */
/*   Updated: 2022/04/09 11:53:49 by taewan           ###   ########.fr       */
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
