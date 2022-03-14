
#include "minishell.h"

void	exec_tree(t_binode *tree, t_data *data)
{
	if (data->syntax == STX_ERR)
	{
		prt_error("syntax error");
		g_exit_status = 1;
	}
	else
		execute(tree, data);
	if (tree)
		tree_del_bintree(tree);
}

int	main(int argc, char **argv, char **envp)
{
	char		*buf;
	t_binode	*tree;
	t_data		data;
	int			original_fd[2];

	(void)argc;
	(void)argv;
	init_set(&data, envp);
	original_fd[0] = dup(STDIN_FILENO);
	original_fd[1] = dup(STDOUT_FILENO);
	while (get_cmd(&buf))
	{
		init_data(&data);
		if (!pre_process_input(buf))
			continue ;
		buf = replace_dollar_sign(buf, envp);
		tree = parsetree(buf, &data);
		free(buf);
		exec_tree(tree, &data);
		dup2(original_fd[0], STDIN_FILENO);
		dup2(original_fd[1], STDOUT_FILENO);
	}
	return (0);
}
