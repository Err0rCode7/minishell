/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:22:44 by seujeon           #+#    #+#             */
/*   Updated: 2022/03/14 15:22:46 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include "libft.h"

# define TREE_DIR_LEFT	0
# define TREE_DIR_RIGHT	1

typedef struct s_binode
{
	char			*data;
	int				type;
	struct s_binode	*left;
	struct s_binode	*right;
}				t_binode;

t_binode	*tree_make_binode(char *str, int typecode);
void		tree_con_binode(t_binode *parent, t_binode *child, int dir);
void		tree_del_bintree(t_binode *parent);
void		tree_del_binode(t_binode *node);

#endif
