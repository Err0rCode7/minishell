/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:12 by taewan            #+#    #+#             */
/*   Updated: 2022/03/23 15:14:51 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_buffer(t_buffer *buffer, size_t size)
{
	buffer->size = 0;
	buffer->arr = (char *)ft_calloc(sizeof(char), (size + 1));
	if (!buffer->arr)
		return (0);
	return (1);
}

void	flush_buffer(t_buffer *buffer, char **arr)
{
	buffer->arr[buffer->size] = 0;
	ft_combine(arr, buffer->arr);
	if (*arr == NULL)
		exit(1);
	buffer->size = 0;
}

void	add_new_line_to_buffer(char **buffer, char *str)
{
	char	*tmp;
	char	*tmp2;

	if (!*str)
		return ;
	tmp = ft_strjoin(*buffer, str);
	if (tmp == NULL)
		exit(1);
	if (*buffer)
		free(*buffer);
	if (str)
		free(str);
	tmp2 = ft_strjoin(tmp, "\n");
	if (tmp2 == NULL)
		exit(1);
	free(tmp);
	*buffer = tmp2;
}
