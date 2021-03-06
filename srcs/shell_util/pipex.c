/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:43 by taewan            #+#    #+#             */
/*   Updated: 2022/04/29 12:47:57 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_home(char **new_argv, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (new_argv[++i])
	{
		if (ft_strncmp(new_argv[i], "~", 1) != 0)
			continue ;
		tmp = find_home(new_argv[i], data->envp);
		if (!tmp)
			exit(1);
		free(new_argv[i]);
		new_argv[i] = tmp;
	}
}

static int	fail_execve(char *path, char **new_argv, int exist_flag,
	t_data *data)
{
	if (path && !ft_strncmp(*new_argv, ".", 2))
	{
		prt_cmd_err_fd(MSG_ARG_ERR, new_argv[0], 2, data);
		write(data->errmsg_fd, ".: usage: . filename [arguments]\n", 33);
	}
	else if (only_dot(new_argv[0]) || (exist_flag && new_argv[0][0] != '.'
		&& new_argv[0][0] != '/'))
		prt_cmd_err_fd(MSG_CMD_NOT_FOUND_ERR, new_argv[0], 127, data);
	else if (!path && !exist_flag)
		prt_cmd_err_fd(MSG_FILE_NOT_FOUND_ERR, new_argv[0], 127, data);
	else if (ft_is_dir(path))
		prt_cmd_err_fd(MSG_DIR_ERR, new_argv[0], 126, data);
	else if (ft_access2(path, S_IREAD) && !ft_access2(path, S_IEXEC))
		prt_cmd_err_fd(MSG_PERMISSION_ERR, new_argv[0], 126, data);
	else if (ft_access2(path, S_IEXEC))
		g_exit_status = 0;
	else
	{
		if (ft_strchr(new_argv[0], '/'))
			prt_cmd_err_fd(MSG_FILE_NOT_FOUND_ERR, new_argv[0], 127, data);
		else
			prt_cmd_err_fd(MSG_CMD_NOT_FOUND_ERR, new_argv[0], 127, data);
	}
	return (g_exit_status);
}

void	new_process(char *cmd, t_data *data)
{
	char	**new_argv;
	char	*path;

	data->redrflag = 0;
	cmd = replace_dollar_sign(cmd, data->envp);
	new_argv = cmd_tokenizer(cmd);
	if (!new_argv)
		exit(1);
	if (!*new_argv)
		exit(127);
	if (switch_routine(new_argv, data) == 0)
		exit(g_exit_status);
	path = find_path(data->envp, new_argv[0]);
	set_home(new_argv, data);
	if (execve(path, new_argv, data->envp) == -1)
		exit(fail_execve(path, new_argv, exist_path(data->envp), data));
}

void	child_process(char *cmd, t_data *data)
{
	pid_t	parent;
	int		fd[2];

	if (pipe(fd) < 0)
		pt_exit_status(MSG_PIPE_ERR, data);
	ignore_all_sig(ignore_all_signal_a);
	if (!ft_strncmp(cmd + find_char_start(cmd), "more", 5))
		ignore_all_sig(ignore_all_signal);
	parent = fork();
	data->last_pid = parent;
	if (parent < 0)
		pt_exit_status(MSG_FORK_ERR, data);
	else if (!parent)
	{
		close(fd[0]);
		if (data->redrflag)
			new_process(cmd, data);
		if (!data->last)
			if (-1 == dup2(fd[1], STDOUT_FILENO))
				error_exit(MSG_DUP_TWO_ERR, EXIT_FAILURE, data);
		new_process(cmd, data);
	}
	else
		action_parent(fd, data);
}

void	open_fd_with_type(char *redr, char *file, t_data *data)
{
	int	fd;

	if (!ft_strncmp(redr, "<", 2))
		left_redr(&fd, file, data);
	else if (!ft_strncmp(redr, ">", 2))
	{
		data->rd_out_flag = 1;
		right_redr(&fd, file, data);
	}
	else if (!ft_strncmp(redr, ">>", 3))
	{
		data->rd_out_flag = 1;
		if (data->roe_flag)
			return ;
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd < 0)
			pt_exit_status(MSG_FILE_OPEN_ERR, data);
		if (0 > dup2(fd, STDOUT_FILENO))
			pt_exit_status(MSG_DUP_TWO_ERR, data);
		close(fd);
	}
	else if (!ft_strncmp(redr, "<<", ft_strlen(redr)))
		here_doc(file, data);
	else
		pt_exit_status(MSG_OPEN_FD_WITH_TYPE_ERR, data);
}
