
#include "minishell.h"

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
			sw[SW_RDRL] = TRUE;
		else if (node->data[sw[SW_INDX]] == '>' && !sw[SW_RDSW])
			sw[SW_RDRR] = TRUE;
		else if (isword(node->data[sw[SW_INDX]]))
			sw[SW_WORD] = TRUE;
		(sw[SW_INDX])++;
	}
	if ((sw[SW_RDRL] && sw[SW_RDRR]) || sw[SW_WORD] == FALSE)
		data->syntax = STX_ERR;
}
