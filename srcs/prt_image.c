/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:03:14 by taewan            #+#    #+#             */
/*   Updated: 2022/04/28 23:23:35 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prt_image(void)
{
	int		fd;
	char	*gnl;

	fd = open("ascii_img/shell_image.txt", O_RDONLY, 0644);
	if (fd < 0)
		prt_error("Failed to open minishell banner.", NULL);
	gnl = ft_strndup("\n", 1);
	while (gnl)
	{
		printf("%s%s%s", YELLOW, gnl, RESET);
		free(gnl);
		gnl = get_next_line(fd);
	}
	close(fd);
	printf("%s%s%s\n", RED, "\t\tHi? My Kkanbu", RESET);
	printf("%s%s%s\n", GREEN, "\t\t\tMade by taewakim, seujeon", RESET);
}
