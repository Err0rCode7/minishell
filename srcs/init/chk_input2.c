/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_input2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:42 by taewan            #+#    #+#             */
/*   Updated: 2022/04/07 03:20:12 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_escape(char **str)
{
	char	*buf;
	int		i;
	int		buf_idx;

	if (!str)
		exit(1);
	buf = ft_calloc(sizeof(char), ft_strlen(*str));
	if (!buf)
		exit(1);
	i = -1;
	buf_idx = 0;
	while (str[0][++i])
	{
		if (i > 0 && str[0][i - 1] == '\\')
		{
			if (str[0][i] == '\'' || str[0][i] == '\"' || str[0][i] == '\\')
			{
				buf[buf_idx++] = str[0][i] - 100;
				str[0][i] = 1;
			}
		}
		else if (str[0][i] != '\\')
			buf[buf_idx++] = str[0][i];
	}
	free(*str);
	*str = ft_strdup(buf);
	if (!*str)
		exit(1);
	free(buf);
}