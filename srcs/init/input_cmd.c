
#include "minishell.h"

char	*get_cmd(char **buf)
{
	char	*tmp;
	char	*prompt;

	tmp = getcwd(0, MAX_DIRLEN);
	prompt = ft_strjoin(tmp, " \x1b[32m$\x1b[0m ");
	free(tmp);
	*buf = readline(prompt);
	free(prompt);
	return (*buf);
}
