/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 00:38:52 by seujeon           #+#    #+#             */
/*   Updated: 2022/04/29 12:09:46 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_oneline(char *msg, char *cmd, char *arg, int errnum)
{
	char	*buf;

	g_exit_status = errnum;
	buf = NULL;
	add_str_to_buffer(&buf, "minishell: ", 0);
	add_str_to_buffer(&buf, cmd, 0);
	add_str_to_buffer(&buf, ": ", 0);
	if (arg != NULL && arg[0] != 0)
	{
		add_str_to_buffer(&buf, "`", 0);
		add_str_to_buffer(&buf, arg, 0);
		add_str_to_buffer(&buf, "\': ", 0);
	}
	add_str_to_buffer(&buf, msg, 0);
	add_str_to_buffer(&buf, "\n", 0);
	return (buf);
}

char	*get_oneline_exitpipe(char *token1, char *token2, char *err_msg,
	int pipeflag)
{
	char	*buf;

	buf = NULL;
	if (!pipeflag)
		add_str_to_buffer(&buf, "exit\n", 0);
	add_str_to_buffer(&buf, "minishell: ", 0);
	add_str_to_buffer(&buf, token1, 0);
	add_str_to_buffer(&buf, ": ", 0);
	add_str_to_buffer(&buf, token2, 0);
	add_str_to_buffer(&buf, ": ", 0);
	add_str_to_buffer(&buf, err_msg, 0);
	add_str_to_buffer(&buf, "\n", 0);
	return (buf);
}

void	print_oneline_err(t_data *data, char *str)
{
	int	fd;

	fd = 2;
	if (data)
		fd = data->errmsg_fd;
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
	free(str);
}
