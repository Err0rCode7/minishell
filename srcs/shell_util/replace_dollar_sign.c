/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar_sign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:46 by taewan            #+#    #+#             */
/*   Updated: 2022/04/29 00:19:27 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	combine_variable(char **arr, char *str, char **envp)
{
	char	*tmp;
	int		size;

	size = 0;
	tmp = interprete_dollar_sign(str, &size, envp);
	if (tmp == 0)
		exit(1);
	ft_combine(arr, tmp);
	if (!*arr)
		exit(1);
	free(tmp);
	return (size - 1);
}

char	*find_dollar(char *str, char **envp, t_buffer *buff, int i)
{
	int		sw;
	char	*arr;

	sw = 0;
	arr = ft_strdup("");
	if (!arr)
		exit(1);
	while (str[++i])
	{
		if (buff->size == BUFFER_SIZE)
			flush_buffer(buff, &arr);
		if (str[i] == '\'' && !(sw & DQUOTE))
			sw ^= SQUOTE;
		if (str[i] == '\"' && !(sw & SQUOTE))
			sw ^= DQUOTE;
		if (is_dollar_sign(str[i]) && !(sw & SQUOTE))
		{
			flush_buffer(buff, &arr);
			i += combine_variable(&arr, str + i, envp);
		}
		else
			buff->arr[buff->size++] = str[i];
	}
	return (arr);
}

char	*replace_dollar_sign(char *str, char **envp)
{
	char		*arr;
	t_buffer	buff;

	if (init_buffer(&buff, BUFFER_SIZE) == 0)
		exit(1);
	arr = find_dollar(str, envp, &buff, -1);
	flush_buffer(&buff, &arr);
	free(buff.arr);
	free(str);
	return (arr);
}
