
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
