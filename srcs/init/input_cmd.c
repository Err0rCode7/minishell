
#include "minishell.h"

char	*get_cmd(char **buf)
{
	char	*tmp;
	char	*prompt;

	tmp = getcwd(0, MAX_DIRLEN);
	if (tmp == NULL)
		exit(1);
	prompt = ft_strjoin(tmp, " \x1b[32m$\x1b[0m ");
	free(tmp);
	if (!prompt)
		exit(1);
	*buf = readline(prompt);
	if(!*buf)
		exit(1);
	free(prompt);
	return (*buf);
}
