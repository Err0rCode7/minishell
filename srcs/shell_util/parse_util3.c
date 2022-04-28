/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:32 by taewan            #+#    #+#             */
/*   Updated: 2022/04/28 23:44:51 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*interprete_dollar_sign(char *str, int *size, char **envp)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && !ft_isspace(str[i]) && !(str[i] == '=')
		&& str[i] != '\'' && str[i] != '\"' && str[i] != ':')
		i++;
	*size = i;
	if (i < 2)
		return (ft_strdup("$"));
	if (i < 3 && !ft_strncmp(str, "$?", 2))
		return (ft_itoa(g_exit_status));
	j = -1;
	while (envp[++j])
		if (correct_env(envp[j], str + 1, i - 1))
			return (ft_strdup(envp[j] + i));
	return (ft_strdup(""));
}
