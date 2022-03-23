/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:14:42 by taewan            #+#    #+#             */
/*   Updated: 2022/03/23 13:06:37 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_remain_line(char **files, char *ptr)
{
	char	*tmp;
	char	*line;

	if (ptr)
	{
		line = ft_strndup(*files, ptr + 1 - *files);
		tmp = ft_strndup(ptr + 1, ft_strlen(ptr + 1));
		free(*files);
		*files = tmp;
	}
	else if (*files)
	{
		line = *files;
		*files = NULL;
	}
	else
		line = ft_strndup("", 0);
	if (!*line)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

void	ft_combine(char **files, char *buff)
{
	char	*tmp;

	tmp = ft_strjoin(*files, buff);
	if (*files)
		free(*files);
	*files = tmp;
}

char	*get_next_line(int fd)
{
	static char	*files[MAX_FD + 1];
	char		buff[BUFFER_SIZE + 1];
	char		*tmp;
	ssize_t		byte;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE < 1)
		return (NULL);
	while (1)
	{
		tmp = ft_strchr(files[fd], '\n');
		if (tmp)
			break ;
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte < 0)
			return (NULL);
		if (byte < 1)
			break ;
		buff[byte] = '\0';
		if (!files[fd])
			files[fd] = ft_strndup(buff, byte);
		else
			ft_combine(&files[fd], buff);
	}
	return (get_remain_line(&files[fd], tmp));
}
