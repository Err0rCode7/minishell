/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:15:08 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 00:15:10 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*res;

	res = 0;
	while (*s)
	{
		if (*s == (unsigned char)c)
			res = s;
		s++;
	}
	if (*s == (unsigned char)c)
		res = s;
	if (!res)
		return (NULL);
	return ((char *)res);
}
