/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewakim <taewakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:23 by taewan            #+#    #+#             */
/*   Updated: 2022/04/26 17:48:55 by taewakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pt_pwd(void)
{
	char	*tmp;

	tmp = getcwd(0, MAX_DIRLEN);
	g_exit_status = 0;
	printf("%s\n", tmp);
	free(tmp);
	return (0);
}
