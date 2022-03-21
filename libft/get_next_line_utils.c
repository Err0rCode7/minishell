/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:14:45 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 00:14:47 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*ans;

	if (!s1)
		return (NULL);
	ans = (char *)malloc(sizeof(char) * (n + 1));
	if (!ans)
		return (NULL);
	ft_strncpy(ans, s1, n);
	return (ans);
}
