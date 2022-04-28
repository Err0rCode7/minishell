/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:39 by taewan            #+#    #+#             */
/*   Updated: 2022/04/29 00:21:05 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *limit, t_data *data)
{
	pid_t	parent;
	int		fd[2];
	int		status;

	ignore_all_sig(ignore_all_signal);
	if (pipe(fd) < 0)
		pt_exit_status(MSG_PIPE_ERR, data);
	parent = fork();
	if (parent < 0)
		pt_exit_status(MSG_FORK_ERR, data);
	else if (!parent)
		here_doc_child(fd, limit, data);
	else
	{
		waitpid(parent, &status, 0);
		g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		close(fd[1]);
		if (-1 == dup2(fd[0], STDIN_FILENO))
			pt_exit_status(MSG_DUP_TWO_ERR, data);
		close(fd[0]);
	}
}

void	left_redr(int *fd, char *file, t_data *data)
{
	*fd = open(file, O_RDONLY, 0644);
	if (*fd < 0)
	{
		prt_cmd_err_fd(MSG_FILE_NOT_FOUND_ERR, file, 1, data);
		*fd = open("/dev/null", O_RDONLY, 0644);
		if (*fd < 0)
			exit(1);
		data->roe_flag = 1;
	}
	if (0 > dup2(*fd, STDIN_FILENO))
		pt_exit_status(MSG_DUP_TWO_ERR, data);
	close(*fd);
}

void	right_redr(int *fd, char *file, t_data *data)
{
	if (data->roe_flag)
		return ;
	*fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd < 0)
	{
		prt_cmd_err_fd(MSG_FILE_OPEN_ERR, file, 1, data);
	}
	else if (0 > dup2(*fd, STDOUT_FILENO))
		pt_exit_status(MSG_DUP_TWO_ERR, data);
	if (*fd > 0)
		close(*fd);
	data->redrflag = 1;
}

void	action_parent(int *fd, t_data *data)
{
	close(fd[1]);
	if (-1 == dup2(fd[0], STDIN_FILENO))
		pt_exit_status(MSG_DUP_TWO_ERR, data);
	close(fd[0]);
}
