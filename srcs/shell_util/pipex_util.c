
#include "minishell.h"

char	*strcomb(char *s1, char *s2)
{
	char	*tmp;
	char	*tmp2;

	if (!s2)
		return (NULL);
	tmp = ft_strjoin(s1, "/");
	tmp2 = ft_strjoin(tmp, s2);
	free(tmp);
	return (tmp2);
}

char	**split_path(char **envp)
{
	int		i;
	char	**arr;

	i = 0;
	while (envp[i] && !(correct_env(envp[i], "PATH", 4)))
		i++;
	if (!envp[i])
		return (NULL);
	arr = ft_split(envp[i] + 5, ':');
	return (arr);
}

char	*find_path(char **envp, char *cmd)
{
	char	**arr;
	int		i;
	char	*path;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	arr = split_path(envp);
	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		path = strcomb(arr[i], cmd);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	ft_split_free(arr);
	return (path);
}

void	here_doc_child(int *fd, char *limit, t_data *data)
{
	char	*line;
	char	*str;

	close(fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, limit, ft_strlen(limit)) == 0)
			exit(EXIT_SUCCESS);
		str = replace_dollar_sign(line, data->envp);
		write(fd[1], str, ft_strlen(str));
		free(str);
	}
}
