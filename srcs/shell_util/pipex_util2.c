
#include "minishell.h"

void	here_doc(char *limit, t_data *data)
{
	pid_t	parent;
	int		fd[2];

	if (pipe(fd) < 0)
		pt_exit_status("Pipe Error");
	parent = fork();
	if (parent < 0)
		pt_exit_status("Fork Error");
	else if (!parent)
		here_doc_child(fd, limit, data);
	else
	{
		close(fd[1]);
		if (-1 == dup2(fd[0], STDIN_FILENO))
			pt_exit_status("dup2 Error");
		wait(0);
	}
}

void	left_redr(int *fd, char *file)
{
	*fd = open(file, O_RDONLY, 0644);
	if (*fd < 0)
		pt_exit_status("No such file or directory");
	if (0 > dup2(*fd, STDIN_FILENO))
		pt_exit_status("dup2 Error");
}

void	right_redr(int *fd, char *file)
{
	*fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (*fd < 0)
		pt_exit_status("File open error");
	if (0 > dup2(*fd, STDOUT_FILENO))
		pt_exit_status("dup2 Error");
}

void	action_parent(int *fd, pid_t *parent, int *exitcode)
{
	close(fd[1]);
	if (-1 == dup2(fd[0], STDIN_FILENO))
		pt_exit_status("dup2 Error");
	waitpid(*parent, exitcode, 0);
	init_signal(handle_signal);
	g_exit_status = WEXITSTATUS(exitcode);
	if (WIFSIGNALED(exitcode))
		g_exit_status = 128 + WTERMSIG(exitcode);
	close(fd[0]);
}
