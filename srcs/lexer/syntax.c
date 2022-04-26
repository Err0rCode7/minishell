/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewakim <taewakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:02:02 by taewan            #+#    #+#             */
/*   Updated: 2022/04/26 18:44:34 by taewakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_here_doc(t_data *data, char *str)
{
	if (!ft_strncmp(, "<<", 2) && !data->wordcnt)
		data->wordcnt++;
}

void	syntax_redr(t_binode *node, t_data *data)
{
	int	sw[5];

	ft_bzero(sw, sizeof(int) * 5);
	while (node->data[sw[SW_INDX]])
	{
		if (node->data[sw[SW_INDX]] == '\'' && !(sw[SW_RDSW] & DQUOTE))
			sw[SW_RDSW] ^= SQUOTE;
		if (node->data[sw[SW_INDX]] == '\"' && !(sw[SW_RDSW] & SQUOTE))
			sw[SW_RDSW] ^= DQUOTE;
		if (node->data[sw[SW_INDX]] == '<' && !sw[SW_RDSW])
		{
			sw[SW_RDRL] = TRUE;
			check_here_doc(data, &node->data[sw[SW_INDX]]);
		}
		else if (node->data[sw[SW_INDX]] == '>' && !sw[SW_RDSW])
			sw[SW_RDRR] = TRUE;
		else if (isword(node->data[sw[SW_INDX]]))
			sw[SW_WORD] = TRUE;
		(sw[SW_INDX])++;
	}
	if ((sw[SW_RDRL] && sw[SW_RDRR]) || sw[SW_WORD] == FALSE)
		data->syntax = STX_ERR;
}
