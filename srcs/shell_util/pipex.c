/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:43 by taewan            #+#    #+#             */
/*   Updated: 2022/04/07 10:45:25 by seujeon          ###   ########.fr       */
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

int		ft_dir_access(char *name)
{
	DIR *tmp;

	tmp = opendir(name);
	if (tmp != NULL)
	{
		closedir(tmp);
		return (1);
	}
	return (0);
}

void	new_process(char *cmd, t_data *data)
{
	char	**new_argv;
	char	*path;

	g_exit_status = 0;
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
	{
		if (!split_path(data->envp))
			prt_cmd_err_shellname(MSG_FILE_NOT_FOUND_ERR, new_argv[0], NULL);
		else if (ft_dir_access(path))
		{
			prt_cmd_err_shellname(MSG_DIR_ERR, new_argv[0], NULL);
			exit(126);
		}
		else
			prt_cmd_err_shellname(MSG_CMD_NOT_FOUND_ERR, new_argv[0], NULL);
		exit(127);
	}
}

void	child_process(char *cmd, t_data *data)
{
	pid_t	parent;
	int		fd[2];
	int		status;

	if (pipe(fd) < 0)
		pt_exit_status(MSG_PIPE_ERR);
	ignore_signal(ignore_sig);
	parent = fork();
	if (parent < 0)
		pt_exit_status(MSG_FORK_ERR);
	else if (!parent)
	{
		close(fd[0]);
		if (!data->tmp)
			if (-1 == dup2(fd[1], STDOUT_FILENO))
				error_exit(MSG_DUP_TWO_ERR, EXIT_FAILURE);
		new_process(cmd, data);
	}
	else
	{
		action_parent(fd);
		if (data->tmp)
		{
			waitpid(parent, &status, 0);
			g_exit_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				g_exit_status = 128 + WTERMSIG(status);
		}
	}
}

void	open_fd_with_type(char *redr, char *file, t_data *data)
{
	int	fd;

	if (!ft_strncmp(redr, "<", 2))
		left_redr(&fd, file, data);
	else if (!ft_strncmp(redr, ">", 2))
		right_redr(&fd, file, data);
	else if (!ft_strncmp(redr, ">>", 3))
	{
		if (data->roe_flag)
			return ;
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd < 0)
			pt_exit_status(MSG_FILE_OPEN_ERR);
		if (0 > dup2(fd, STDOUT_FILENO))
			pt_exit_status(MSG_DUP_TWO_ERR);
	}
	else if (!ft_strncmp(redr, "<<", ft_strlen(redr)))
	{
		here_doc(file, data);
		init_signal(handle_signal);
	}
	else
		pt_exit_status(MSG_OPEN_FD_WITH_TYPE_ERR);
}
