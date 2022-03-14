
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != (unsigned char)c)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}
