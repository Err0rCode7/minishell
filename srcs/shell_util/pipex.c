
#include "minishell.h"

int	pre_exec_cmd(t_data *data, char **new_argv, char **path)
{
	if (ft_strcmp(new_argv[0], "exit") == 0)
		return (pt_exit(new_argv));
	else if (ft_strcmp(new_argv[0], "export") == 0)
		return (pt_export(&(data->envp), new_argv));
	else if (ft_strcmp(new_argv[0], "unset") == 0)
		return (pt_unset(&(data->envp), new_argv));
	else if (ft_strcmp(new_argv[0], "env") == 0)
		return (pt_env(data->envp));
	else if (ft_strcmp(new_argv[0], "echo") == 0)
		return (pt_echo(new_argv));
	else
	{
		free(*path);
		*path = find_path(data->envp, new_argv[0]);
	}
	return (0);
}

int	handle_errno(int err)
{
	if (err == 14)
		return (127);
	return (0);
}

void	new_process(char *cmd, t_data *data)
{
	char	**new_argv;
	char	*path;

	new_argv = cmd_tokenizer(cmd);
	if (!*new_argv)
		exit(127);
	path = find_path(data->envp, new_argv[0]);
	if (execve(path, new_argv, data->envp) == -1)
	{
		ft_split_free(new_argv);
		error_exit("Command not found", 127);
	}
}

void	child_process(char *cmd, t_data *data)
{
	pid_t	parent;
	int		fd[2];
	int		exitcode;

	if (pipe(fd) < 0)
		pt_exit_status("Pipe Error");
	ignore_signal(ignore_sig);
	parent = fork();
	if (parent < 0)
		pt_exit_status("Fork Error");
	else if (!parent)
	{
		close(fd[0]);
		if (-1 == dup2(fd[1], STDOUT_FILENO))
			error_exit("dup2 Error", EXIT_FAILURE);
		new_process(cmd, data);
	}
	else
		action_parent(fd, &parent, &exitcode);
}

void	open_fd_with_type(char *redr, char *file, t_data *data)
{
	int	fd;

	if (!ft_strncmp(redr, "<", ft_strlen(redr)))
		left_redr(&fd, file);
	else if (!ft_strncmp(redr, ">", ft_strlen(redr)))
		right_redr(&fd, file);
	else if (!ft_strncmp(redr, ">>", ft_strlen(redr)))
	{
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd < 0)
			pt_exit_status("File open error");
		if (0 > dup2(fd, STDOUT_FILENO))
			pt_exit_status("dup2 Error");
	}
	else if (!ft_strncmp(redr, "<<", ft_strlen(redr)))
		here_doc(file, data);
	else
		pt_exit_status("Function : open_fd_with_type Error");
}
