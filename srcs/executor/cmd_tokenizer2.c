/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tokenizer2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:00:42 by taewan            #+#    #+#             */
/*   Updated: 2022/04/09 21:04:59 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	jump_space(char *str, char **arr, t_buffer *buff, t_tokenidx *idx)
{
	if (buff->size)
	{
		flush_buffer(buff, arr);
		idx->j++;
	}
	return (count_space(str + idx->i));
}

int	switch_ctrl(int	sw, char c)
{
	if (c == '\'' && !(sw & DQUOTE))
		sw ^= SQUOTE;
	if (c == '\"' && !(sw & SQUOTE))
		sw ^= DQUOTE;
	return (sw);
}

void	put_buffer(t_buffer *buff, char c, int sw)
{
	if (((sw & SQUOTE) && (c == '\"'))
		|| ((sw & DQUOTE) && (c == '\'')))
		buff->arr[buff->size++] = c;
	else if (c != '\'' && c != '\"')
	{
		if (c < 0)
			c += 100;
		buff->arr[buff->size++] = c;
	}
}
