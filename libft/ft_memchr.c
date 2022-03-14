
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*mem;

	mem = (unsigned char *)s;
	while (n--)
	{
		if (*mem == (unsigned char)c)
			return ((void *)mem);
		mem++;
	}
	return (0);
}
