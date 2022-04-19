/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_input2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 20:59:05 by taewan            #+#    #+#             */
/*   Updated: 2022/04/19 14:01:23 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	escape_logic(char **str, char *buf)
{
	int	i;
	int	buf_idx;
	int	squote;

	i = -1;
	buf_idx = 0;
	squote = 0;
	while (str[0][++i])
	{
		if (i > 0 && str[0][i - 1] == '\\')
		{
			if (str[0][i] == '\'' || str[0][i] == '\"' || str[0][i] == '\\')
			{
				buf[buf_idx++] = str[0][i];
				str[0][i] = 1;
			}
		}
		else if (str[0][i] != '\\' || squote)
			buf[buf_idx++] = str[0][i];
		if (str[0][i] == '\'')
			squote = 1 - squote;
	}
}

void	process_escape(char **str)
{
	char	*buf;

	if (!str)
		exit(1);
	buf = ft_calloc(sizeof(char), ft_strlen(*str) + 1);
	if (!buf)
		exit(1);
	escape_logic(str, buf);
	free(*str);
	*str = ft_strdup(buf);
	if (!*str)
		exit(1);
	free(buf);
}
