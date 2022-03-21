/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:29 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 00:02:30 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_single_quotmark(char c)
{
	if (c == '\'')
		return (TRUE);
	return (FALSE);
}

int	is_double_quotmark(char c)
{
	if (c == '\"')
		return (TRUE);
	return (FALSE);
}

int	is_dollar_sign(char c)
{
	if (c == '$')
		return (TRUE);
	return (FALSE);
}

int	is_space(char c)
{
	if (c == ' ')
		return (TRUE);
	return (FALSE);
}

int	correct_env(char *env, char *str, int size)
{
	if (ft_strncmp(env, str, size))
		return (0);
	if (env[size] != '=')
		return (0);
	return (1);
}
