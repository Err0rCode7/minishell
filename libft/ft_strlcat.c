/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:15:30 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 00:15:31 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && *dst)
	{
		dst++;
		i++;
	}
	while (*src && size > 0 && i < size - 1)
	{
		*dst++ = *src++;
		i++;
	}
	if (i < size)
		*dst = '\0';
	while (*src)
	{
		src++;
		i++;
	}
	return (i);
}
