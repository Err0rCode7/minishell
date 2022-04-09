/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:39 by taewan            #+#    #+#             */
/*   Updated: 2022/04/09 11:07:44 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ignore_all_signal(int signo)
{
	(void)signo;
}

void	here_doc(char *limit, t_data *data)
{
	pid_t	parent;
	int		fd[2];

	signal(SIGINT, ignore_all_signal);
	signal(SIGQUIT, ignore_all_signal);
	if (pipe(fd) < 0)
		pt_exit_status(MSG_PIPE_ERR);
	parent = fork();
	if (parent < 0)
		pt_exit_status(MSG_FORK_ERR);
	else if (!parent)
		here_doc_child(fd, limit, data);
	else
	{
		close(fd[1]);
		if (-1 == dup2(fd[0], STDIN_FILENO))
			pt_exit_status(MSG_DUP_TWO_ERR);
		wait(0);
	}
}

void	left_redr(int *fd, char *file, t_data *data)
{
	*fd = open(file, O_RDONLY, 0644);
	if (*fd < 0)
	{
		prt_cmd_err_shellname(MSG_FILE_NOT_FOUND_ERR, file, NULL, 1);
		*fd = open("/dev/null", O_RDONLY, 0644);
		if (*fd < 0)
			exit(1);
		data->roe_flag = 1;
	}
	if (0 > dup2(*fd, STDIN_FILENO))
		pt_exit_status(MSG_DUP_TWO_ERR);
	close(*fd);
}

void	right_redr(int *fd, char *file, t_data *data)
{
	if (data->roe_flag)
		return ;
	*fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd < 0)
	{
		prt_cmd_err_shellname(MSG_FILE_OPEN_ERR, file, NULL, 1);
	}
	else if (0 > dup2(*fd, STDOUT_FILENO))
		pt_exit_status(MSG_DUP_TWO_ERR);
	if (*fd > 0)
		close(*fd);
}

void	action_parent(int *fd)
{
	close(fd[1]);
	if (-1 == dup2(fd[0], STDIN_FILENO))
		pt_exit_status(MSG_DUP_TWO_ERR);
	close(fd[0]);
}
