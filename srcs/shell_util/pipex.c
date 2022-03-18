
#include "minishell.h"

void	new_process(char *cmd, t_data *data)
{
	char	**new_argv;
	char	*path;

	new_argv = cmd_tokenizer(cmd);
	if (!new_argv)
		exit(1);
	if (!*new_argv)
		exit(127);
	path = find_path(data->envp, new_argv[0]);
	if (execve(path, new_argv, data->envp) == -1)
	{
		prt_cmd_err_shellname(MSG_CMD_NOT_FOUND_ERR, new_argv[0], NULL);
		ft_split_free(new_argv);
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

void	open_fd_with_type(char *redr, char *file, t_data *data)
{
	int	fd;

	if (!ft_strncmp(redr, "<", 2))
		left_redr(&fd, file);
	else if (!ft_strncmp(redr, ">", 2))
		right_redr(&fd, file);
	else if (!ft_strncmp(redr, ">>", 3))
	{
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd < 0) // 수정이 필요
			pt_exit_status(MSG_FILE_OPEN_ERR);
		if (0 > dup2(fd, STDOUT_FILENO))
			pt_exit_status(MSG_DUP_TWO_ERR);
	}
	else if (!ft_strncmp(redr, "<<", ft_strlen(redr)))
		here_doc(file, data);
	else
		pt_exit_status(MSG_OPEN_FD_WITH_TYPE_ERR);
}
