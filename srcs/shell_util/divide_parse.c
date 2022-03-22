/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewakim <taewakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:17 by taewan            #+#    #+#             */
/*   Updated: 2022/03/22 14:51:57 by taewakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	divide_pipe(t_binode *parent, t_data *data)
{
	char	**splited_str;

	splited_str = split_pipe(parent->data);
	if (!splited_str || !splited_str[0] || !splited_str[1])
		exit(1);
	if (**splited_str)
	{
		tree_con_binode(parent, \
		tree_make_binode(*splited_str, T_COMD), TREE_DIR_LEFT);
	}
	splited_str++;
	if (**splited_str)
	{
		data->pipecnt++;
		tree_con_binode(parent, \
		tree_make_binode(*splited_str, T_PIPE), TREE_DIR_RIGHT);
	}
	ft_split_free(--splited_str);
}

void	divide_command(t_binode *parent)
{
	char	**splited_str;

	splited_str = split_command(parent->data);
	if (!splited_str || !splited_str[0] || !splited_str[1])
		exit(1);
	if (**splited_str)
	{
		tree_con_binode(parent, \
		tree_make_binode(*splited_str, T_REDS), TREE_DIR_LEFT);
	}
	splited_str++;
	if (**splited_str)
	{
		tree_con_binode(parent, \
		tree_make_binode(*splited_str, T_WORD), TREE_DIR_RIGHT);
	}
	ft_split_free(--splited_str);
}

void	divide_redirect(t_binode *parent)
{
	char	**splited_str;

	splited_str = split_redirect(parent->data);
	if (!splited_str || !splited_str[0] || !splited_str[1])
		exit(1);
	if (**splited_str)
	{
		tree_con_binode(parent, \
		tree_make_binode(*splited_str, T_REDR), TREE_DIR_LEFT);
	}
	splited_str++;
	if (**splited_str)
	{
		tree_con_binode(parent, \
		tree_make_binode(*splited_str, T_REDS), TREE_DIR_RIGHT);
	}
	ft_split_free(--splited_str);
}
