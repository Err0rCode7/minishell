/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:25 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 00:02:27 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ispipe(char c)
{
	if (c == '|')
		return (TRUE);
	return (FALSE);
}

int	isword(char c)
{
	if (c == ' ' || isredirects(c))
		return (FALSE);
	return (TRUE);
}

int	isredirects(char c)
{
	if (c == '>' || c == '<')
		return (TRUE);
	return (FALSE);
}

char	**calloc_redirects(size_t cnt)
{
	char	**tmp;

	tmp = (char **)malloc(sizeof(char *) * 3);
	if (!tmp)
		exit(1);
	*tmp = (char *)ft_calloc(sizeof(char), cnt);
	*(tmp + 1) = (char *)ft_calloc(sizeof(char), cnt);
	if (!tmp[0] || !tmp[1])
		exit(1);
	*(tmp + 2) = 0;
	return (tmp);
}
