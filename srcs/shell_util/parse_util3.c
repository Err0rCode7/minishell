
#include "minishell.h"

char	*interprete_dollar_sign(char *str, int *size, char **envp)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && !ft_isspace(str[i]) && str[i] != '\'' && str[i] != '\"')
		i++;
	*size = i;
	if (i < 2)
		return (ft_strndup("$", 1));
	if (i < 3 && !ft_strncmp(str, "$?", 2))
		return (ft_itoa(g_exit_status));
	j = -1;
	while (envp[++j])
		if (correct_env(envp[j], str + 1, i - 1))
			return (ft_strndup(envp[j] + i, ft_strlen(envp[j] + i)));
	return (NULL);
}
