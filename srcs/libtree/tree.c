/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:07 by taewan            #+#    #+#             */
/*   Updated: 2022/04/09 16:59:45 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void	tree_del_bintree(t_binode *parent)
{
	if (!parent)
		return ;
	tree_del_bintree(parent->left);
	parent->left = NULL;
	tree_del_bintree(parent->right);
	parent->right = NULL;
	tree_del_binode(parent);
}

void	tree_del_binode(t_binode *node)
{
	if (node->left || node->right)
		return ;
	if (node->data)
		free(node->data);
	free(node);
}

void	tree_con_binode(t_binode *parent, t_binode *child, int dir)
{
	if (!parent)
		return ;
	if (dir == TREE_DIR_LEFT && !parent->left)
		parent->left = child;
	if (dir == TREE_DIR_RIGHT && !parent->right)
		parent->right = child;
}

t_binode	*tree_make_binode(char *str, int typecode)
{
	t_binode	*tmp;

	tmp = (t_binode *)malloc(sizeof(t_binode));
	tmp->data = ft_strdup(str);
	if (!tmp || !tmp->data)
		exit(1);
	tmp->type = typecode;
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}
