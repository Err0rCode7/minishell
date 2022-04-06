/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:03:10 by taewan            #+#    #+#             */
/*   Updated: 2022/04/07 02:41:03 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_tree(t_binode *tree, t_data *data)
{
	if (data->syntax == STX_ERR || data->wordcnt - data->pipecnt != 1)
	{
		prt_error(MSG_GENERAL_SYNTAX_ERR);
		g_exit_status = 1;
	}
	else
		execute(tree, data);
	if (tree)
		tree_del_bintree(tree);
}

int	ft_dup(int *original_fd)
{
	original_fd[0] = dup(STDIN_FILENO);
	original_fd[1] = dup(STDOUT_FILENO);
	if (original_fd[0] == -1 || original_fd[1] == -1)
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*buf;
	t_binode	*tree;
	t_data		data;
	int			original_fd[2];
	int			status;

	(void)argc;
	(void)argv;
	if (!ft_dup(original_fd))
		return (1);
	init_set(&data, envp);
	while (get_cmd(&buf))
	{
		init_data(&data);
		if (!pre_process_input(buf))
			continue ;
		tree = parsetree(buf, &data);
		exec_tree(tree, &data);
		//수정 필요
		while (wait(&status) != -1);
		init_signal(handle_signal);
		free(buf);
		dup2(original_fd[0], STDIN_FILENO);
		dup2(original_fd[1], STDOUT_FILENO);
	}
	return (0);
}
