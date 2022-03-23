/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:36 by taewan            #+#    #+#             */
/*   Updated: 2022/03/23 15:09:20 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strcomb(char *s1, char *s2)
{
	char	*tmp;
	char	*tmp2;

	if (!s2)
		return (NULL);
	tmp = ft_strjoin(s1, "/");
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin(tmp, s2);
	free(tmp);
	if (!tmp2)
		return (NULL);
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

static int	ft_access(char *file, int option)
{
	int	fd;

	fd = open(file, option);
	if (fd < 0)
		return (fd);
	close(fd);
	return (0);
}

char	*find_path(char **envp, char *cmd)
{
	char	**arr;
	int		i;
	char	*path;

	if (ft_access(cmd, O_RDONLY) == 0)
		return (cmd);
	arr = split_path(envp);
	if (!arr)
		return (NULL);
	i = -1;
	while (arr[++i])
	{
		path = strcomb(arr[i], cmd);
		if (!path)
			exit(1);
		if (ft_access(path, O_RDONLY) == 0)
			break ;
		free(path);
		path = NULL;
	}
	ft_split_free(arr);
	if (path)
		return (path);
	return (NULL);
}

void	here_doc_child(int *fd, char *limit, t_data *data)
{
	char	*line;
	char	*str;
	char	*buffer;

	signal(SIGINT, heredoc_signal);
	signal(SIGQUIT, heredoc_signal);
	close(fd[0]);
	buffer = NULL;
	while (1)
	{
		line = readline("> ");
		if (handle_endline(line) || ft_strncmp(line, limit, ft_strlen(limit)) == 0)
		{
			if (buffer != NULL)
				write(fd[1], buffer, ft_strlen(buffer));
			exit(EXIT_SUCCESS);
		}
		str = replace_dollar_sign(line, data->envp);
		add_new_line_to_buffer(&buffer, str);
	}
}
