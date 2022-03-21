/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:12 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 00:02:14 by taewan           ###   ########.fr       */
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
