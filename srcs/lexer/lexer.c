/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewakim <taewakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:59 by taewan            #+#    #+#             */
/*   Updated: 2022/04/26 17:08:19 by taewakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	divide_str(int divide_kind, t_binode *parent, t_data *data)
{
	if (divide_kind == T_PIPE)
		divide_pipe(parent, data);
	if (divide_kind == T_COMD)
		divide_command(parent, data);
	if (divide_kind == T_REDS)
		divide_redirect(parent);
	if (divide_kind == T_REDR)
		syntax_redr(parent, data);
}

void	recur_parse(t_binode *parent, t_data *data)
{
	if (parent == NULL)
		return ;
	divide_str(parent->type, parent, data);
	recur_parse(parent->left, data);
	recur_parse(parent->right, data);
	return ;
}

t_binode	*parsetree(char *str, t_data *data)
{
	t_binode	*tree;

	tree = tree_make_binode(str, T_PIPE);
	if (!tree)
		return (NULL);
	recur_parse(tree, data);
	return (tree);
}
