/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:43 by taewan            #+#    #+#             */
/*   Updated: 2022/03/23 11:16:45 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_process(char *cmd, t_data *data)
{
	char	**new_argv;
	char	*path;
	char	*tmp;
	int		i;

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
	i = 0;
	while (new_argv[++i])
	{
		if (ft_strncmp(new_argv[i], "~", 1) != 0)
			continue ;
		tmp = find_home(new_argv[i], data->envp);
		free(new_argv[i]);
		new_argv[i] = tmp;
	}
	if (execve(path, new_argv, data->envp) == -1)
	{
		prt_cmd_err_shellname(MSG_CMD_NOT_FOUND_ERR, new_argv[0], NULL);
		exit(127);
	}
}

void	child_process(char *cmd, t_data *data)
{
	pid_t	parent;
	int		fd[2];
	int		exitcode;

	if (pipe(fd) < 0)
		pt_exit_status(MSG_PIPE_ERR);
	ignore_signal(ignore_sig);
	parent = fork();
	if (parent < 0)
		pt_exit_status(MSG_FORK_ERR);
	else if (!parent)
	{
		close(fd[0]);
		if (-1 == dup2(fd[1], STDOUT_FILENO))
			error_exit(MSG_DUP_TWO_ERR, EXIT_FAILURE);
		new_process(cmd, data);
	}
	else
		action_parent(fd, &parent, &exitcode);
}

static void	heredoc_signal(int signo)
{
	(void)signo;
	// if (signo == SIGINT)
	// {
	// 	printf("\n");
	// }
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
		signal(SIGINT, heredoc_signal);
		signal(SIGQUIT, heredoc_signal);
		here_doc(file, data);
		init_signal(handle_signal);
	}
	else
		pt_exit_status(MSG_OPEN_FD_WITH_TYPE_ERR);
}
