/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:18:00 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 00:18:02 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(int n)
{
	int	i;

	if (!n)
		return (1);
	i = 0;
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		minus;
	int		i;
	int		len;
	long	nbr;

	minus = 1;
	if (n < 0)
		minus = -1;
	len = ft_intlen(n);
	nbr = (long)n * (long)minus;
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	if (minus < 0)
		arr[0] = '-';
	i = (minus == -1);
	while (i < len)
	{
		arr[len - i - (minus == 1)] = (nbr % 10) + '0';
		nbr /= 10;
		i++;
	}
	arr[len] = 0;
	return (arr);
}
