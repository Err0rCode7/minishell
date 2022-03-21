/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:39 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 00:02:41 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *limit, t_data *data)
{
	pid_t	parent;
	int		fd[2];

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
		prt_cmd_err_shellname(MSG_FILE_NOT_FOUND_ERR, file, NULL);
		g_exit_status = 1;
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
		prt_cmd_err_shellname(MSG_FILE_OPEN_ERR, file, NULL);
		g_exit_status = 1;
	}
	else if (0 > dup2(*fd, STDOUT_FILENO))
		pt_exit_status(MSG_DUP_TWO_ERR);
	if (*fd > 0)
		close(*fd);
}

void	action_parent(int *fd, pid_t *parent, int *exitcode)
{
	close(fd[1]);
	if (-1 == dup2(fd[0], STDIN_FILENO))
		pt_exit_status(MSG_DUP_TWO_ERR);
	waitpid(*parent, exitcode, 0);
	init_signal(handle_signal);
	g_exit_status = WEXITSTATUS(exitcode);
	if (WIFSIGNALED(exitcode))
		g_exit_status = 128 + WTERMSIG(exitcode);
	close(fd[0]);
}
