
#include "minishell.h"

int	token_cnt(char const *s, char c)
{
	int	idx[3];

	ft_bzero(idx, sizeof(int) * 3);
	while (s[idx[2]])
	{
		if (s[idx[2]] != c)
		{
			idx[0]++;
			while (s[idx[2]])
			{
				if (s[idx[2]] == '\'' && !(idx[1] & DQUOTE))
					idx[1] ^= SQUOTE;
				if (s[idx[2]] == '\"' && !(idx[1] & SQUOTE))
					idx[1] ^= DQUOTE;
				if (s[idx[2]] == c && !idx[1])
					break ;
				idx[2]++;
			}
		}
		else
			idx[2]++;
	}
	return (idx[0]);
}

int	count_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i - 1);
}

void	init_tokenidx(t_tokenidx *idx)
{
	idx->i = -1;
	idx->j = 0;
	idx->sw = 0;
}

t_buffer	*init_arg(t_tokenidx *idx)
{
	t_buffer	*buff;

	buff = (t_buffer *)ft_calloc(sizeof(t_buffer), 1);
	init_buffer(buff, BUFFER_SIZE);
	init_tokenidx(idx);
	return (buff);
}

char	**cmd_tokenizer(char *str)
{
	char		**arr;
	t_buffer	*buff;
	t_tokenidx	idx;

	arr = (char **)ft_calloc(sizeof(char *), token_cnt(str, ' ') + 1);
	if (!arr)
		return (NULL);
	buff = init_arg(&idx);
	while (str[++idx.i])
	{
		if (buff->size == BUFFER_SIZE)
			flush_buffer(buff, arr + idx.j);
		idx.sw = switch_ctrl(idx.sw, str[idx.i]);
		if (str[idx.i] == ' ' && !idx.sw)
			idx.i += jump_space(str, arr + idx.j, buff, &idx);
		else
			put_buffer(buff, str[idx.i], idx.sw);
	}
	if (buff->size)
		flush_buffer(buff, arr + idx.j++);
	arr[idx.j] = 0;
	free(buff->arr);
	free(buff);
	return (arr);
}
