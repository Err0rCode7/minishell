
#include "libft.h"

size_t	ft_word_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

char	**ft_split_free(char **arr)
{
	size_t	i;

	i = 0;
	if (arr)
		while (arr[i])
			free(arr[i++]);
	if (!arr)
		free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	char	*start;

	arr = (char **)malloc(sizeof(char *) * (ft_word_count(s, c) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = (char *)s;
			while (*s && *s != c)
				s++;
			arr[i] = (char *)malloc(sizeof(char) * (s - start + 1));
			if (!(arr[i]))
				return (ft_split_free(arr));
			ft_strlcpy(arr[i++], start, s - start + 1);
		}
		else
			s++;
	}
	arr[i] = 0;
	return (arr);
}
