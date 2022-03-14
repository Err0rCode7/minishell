
#include "minishell.h"

int	jump_space(char *str, char **arr, t_buffer *buff, t_tokenidx *idx)
{
	if (buff->size)
	{
		flush_buffer(buff, arr);
		idx->j++;
	}
	return (count_space(str + idx->i));
}

int	switch_ctrl(int	sw, char c)
{
	if (c == '\'' && !(sw & DQUOTE))
		sw ^= SQUOTE;
	if (c == '\"' && !(sw & SQUOTE))
		sw ^= DQUOTE;
	return (sw);
}

void	put_buffer(t_buffer *buff, char c, int sw)
{
	if (((sw & SQUOTE) && (c == '\"'))
		|| ((sw & DQUOTE) && (c == '\'')))
		buff->arr[buff->size++] = c;
	else if (c != '\'' && c != '\"')
		buff->arr[buff->size++] = c;
}
