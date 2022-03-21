
#include "minishell.h"

void	execute(t_binode *tree, t_data *data)
{
	if (!tree)
		return ;
	if (tree->type == T_REDR) {
		tree->data = replace_dollar_sign(tree->data, data->envp);
		execute_redr(tree, data);
	}
	if (tree->type == T_WORD) {
		tree->data = replace_dollar_sign(tree->data, data->envp);
		execute_word(tree, data);
	}
	execute(tree->left, data);
	execute(tree->right, data);
}

void	execute_redr(t_binode *parent, t_data *data)
{
	char	*redr;
	char	**arr;
	int		i;

	i = -1;
	while (parent->data[++i])
		if (!isredirects(parent->data[i]))
			break ;
	redr = ft_strndup(parent->data, i);
	arr = cmd_tokenizer(parent->data + i);
	if (!arr || !redr)
        exit(1);
	open_fd_with_type(redr, arr[0], data);
	free(redr);
	ft_split_free(arr);
}

int	str_only_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ')
			return (0);
	return (1);
}

void	exec_fork(t_binode *parent, t_data *data)
{
	pid_t	pid;
	int		exitcode;

	ignore_signal(ignore_sig);
	pid = fork();
	if (pid < 0)
		pt_exit_status(MSG_FORK_ERR);
	if (!pid)
		new_process(parent->data, data);
	else
	{
		waitpid(pid, &exitcode, 0);
		init_signal(handle_signal);
		g_exit_status = WEXITSTATUS(exitcode);
		if (WIFSIGNALED(exitcode))
			g_exit_status = 128 + WTERMSIG(exitcode);
	}
}

void	execute_word(t_binode *parent, t_data *data)
{
	char	**new_argv;
	int		i;

	if (!parent->data || !(*parent->data) || str_only_space(parent->data))
		return ;
	new_argv = cmd_tokenizer(parent->data);
	if (!new_argv)
		exit(1);
	i = switch_routine(new_argv, data);
	if (i)
	{
		if (data->pipecnt--)
		{
			child_process(parent->data, data);
			data->roe_flag = 0;
			ft_split_free(new_argv);
			return ;
		}
		exec_fork(parent, data);
	}
	ft_split_free(new_argv);
}
