
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		ans;
	int		i;
	int		minus;

	ans = 0;
	i = 0;
	minus = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			minus = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		ans *= 10;
		ans += minus * (nptr[i] - '0');
		i++;
	}
	return (ans);
}
