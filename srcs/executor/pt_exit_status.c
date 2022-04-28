/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_exit_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:10 by taewan            #+#    #+#             */
/*   Updated: 2022/04/29 01:10:00 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pt_exit_status(char *str, t_data *data)
{
	prt_error(str, data);
	g_exit_status = 1;
	exit(1);
	return (0);
}

void	print_pipe_exit(int pipeflag, t_data *data)
{
	if (pipeflag)
		return ;
	write(data->errmsg_fd, "exit\n", 5);
}

int	print_execute_err_1(char *token, char *err_msg, int pipeflag, t_data *data)
{
	int		fd;
	char	*buf;

	fd = 2;
	buf = NULL;
	if (data)
		fd = data->errmsg_fd;
	if (!pipeflag)
		add_str_to_buffer(&buf, "exit\n", 0);
	add_str_to_buffer(&buf, "minishell: ", 0);
	add_str_to_buffer(&buf, token, 0);
	add_str_to_buffer(&buf, ": ", 0);
	add_str_to_buffer(&buf, err_msg, 0);
	add_str_to_buffer(&buf, "\n", 0);
	write(fd, buf, ft_strlen(buf));
	free(buf);
	return (-1);
}

int	print_execute_err_2(char *token1, char *token2, char *err_msg, t_data *data)
{
	int		fd;
	char	*buf;

	fd = 2;
	buf = NULL;
	if (data)
		fd = data->errmsg_fd;
	add_str_to_buffer(&buf, "minishell: ", 0);
	add_str_to_buffer(&buf, token1, 0);
	add_str_to_buffer(&buf, ": ", 0);
	add_str_to_buffer(&buf, token2, 0);
	add_str_to_buffer(&buf, ": ", 0);
	add_str_to_buffer(&buf, err_msg, 0);
	add_str_to_buffer(&buf, "\n", 0);
	write(fd, buf, ft_strlen(buf));
	free(buf);
	return (-1);
}

int	print_execute_err_3(char *head, char *token, char *err_msg, t_data *data)
{
	int		fd;
	char	*buf;

	fd = 2;
	buf = NULL;
	if (data)
		fd = data->errmsg_fd;
	add_str_to_buffer(&buf, head, 0);
	add_str_to_buffer(&buf, ": ", 0);
	add_str_to_buffer(&buf, token, 0);
	add_str_to_buffer(&buf, ": ", 0);
	add_str_to_buffer(&buf, err_msg, 0);
	add_str_to_buffer(&buf, "\n", 0);
	write(fd, buf, ft_strlen(buf));
	free(buf);
	return (-1);
}
