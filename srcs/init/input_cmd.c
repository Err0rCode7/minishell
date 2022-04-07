/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:49 by taewan            #+#    #+#             */
/*   Updated: 2022/04/07 10:29:11 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(char **buf)
{
	*buf = readline("minishell$ ");
	if (!*buf)
	{
		printf("\033[1A\033[10C exit\n");
		exit(0);
	}
	return (*buf);
}
