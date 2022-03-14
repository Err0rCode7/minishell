
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*sc;

	if (!dest && !src)
		return (NULL);
	dst = dest;
	sc = (unsigned char *)src;
	if (dst <= sc)
		while (n--)
			*dst++ = *sc++;
	else
	{
		dst += n;
		sc += n;
		while (n--)
			*--dst = *--sc;
	}
	return (dest);
}
