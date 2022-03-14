
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
