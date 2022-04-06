/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:00:10 by taewan            #+#    #+#             */
/*   Updated: 2022/04/07 02:18:50 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_binode *tree, t_data *data)
{
	if (!tree)
		return ;
	if (tree->type == T_REDR)
	{
		tree->data = replace_dollar_sign(tree->data, data->envp);
		execute_redr(tree, data);
	}
	if (tree->type == T_WORD)
		execute_word(tree, data);
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

	ignore_signal(ignore_sig);
	pid = fork();
	if (pid < 0)
		pt_exit_status(MSG_FORK_ERR);
	if (!pid)
		new_process(parent->data, data);
	else
		init_signal(handle_signal);
}

void	execute_word(t_binode *parent, t_data *data)
{
	char	**new_argv;

	if (!parent->data || !(*parent->data) || str_only_space(parent->data))
		return ;
	if (data->pipeflag)
	{
		data->pipecnt--;
		data->tmp = 0;
		if (data->pipecnt == -1)
			data->tmp = 1;
		child_process(parent->data, data);
		data->roe_flag = 0;
	}
	else
	{
		parent->data = replace_dollar_sign(parent->data, data->envp);
		new_argv = cmd_tokenizer(parent->data);
		add_key_value(&data->envp, ft_strdup(get_last(new_argv)), ft_strdup("_"));
		if (!new_argv)
			exit(1);
		if (switch_routine(new_argv, data))
			exec_fork(parent, data);
		ft_split_free(new_argv);
	}
}
