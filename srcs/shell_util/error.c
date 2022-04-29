/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:21 by taewan            #+#    #+#             */
/*   Updated: 2022/04/29 12:25:01 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *msg, int exitcode, t_data *data)
{
	int		fd;
	char	*buf;

	fd = 2;
	buf = NULL;
	if (data)
		fd = data->errmsg_fd;
	add_str_to_buffer(&buf, RED, 0);
	add_str_to_buffer(&buf, "Error : ", 0);
	add_str_to_buffer(&buf, RESET, 0);
	add_str_to_buffer(&buf, msg, 0);
	add_str_to_buffer(&buf, "\n", 0);
	write(fd, buf, ft_strlen(buf));
	free(buf);
	exit(exitcode);
}

void	prterr_exit(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}

int	prt_error(char *msg, t_data *data)
{
	int		fd;
	char	*buf;

	fd = 2;
	buf = NULL;
	if (data)
		fd = data->errmsg_fd;
	add_str_to_buffer(&buf, RED, 0);
	add_str_to_buffer(&buf, "Error : ", 0);
	add_str_to_buffer(&buf, RESET, 0);
	add_str_to_buffer(&buf, msg, 0);
	add_str_to_buffer(&buf, "\n", 0);
	write(fd, buf, ft_strlen(buf));
	free(buf);
	return (0);
}

void	prt_cmd_err_s_name(char *msg, char *cmd, char *arg, int errnum)
{
	g_exit_status = errnum;
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	if (arg != NULL && arg[0] != 0)
	{
		write(2, "`", 1);
		write(2, arg, ft_strlen(arg));
		write(2, "\': ", 3);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	prt_cmd_err_fd(char *msg, char *cmd, int errnum, t_data *data)
{
	int		fd;
	char	*buf;

	fd = 2;
	if (data)
		fd = data->errmsg_fd;
	g_exit_status = errnum;
	buf = NULL;
	add_str_to_buffer(&buf, "minishell: ", 0);
	add_str_to_buffer(&buf, cmd, 0);
	add_str_to_buffer(&buf, ": ", 0);
	add_str_to_buffer(&buf, msg, 0);
	add_str_to_buffer(&buf, "\n", 0);
	write(fd, buf, ft_strlen(buf));
	free(buf);
}
