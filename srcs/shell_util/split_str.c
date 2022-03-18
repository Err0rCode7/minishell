
#include "minishell.h"

char	*find_pipe(char *str)
{
	int	sw;
	int	i;

	if (!*str)
		return (NULL);
	sw = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && !(sw & DQUOTE))
			sw ^= SQUOTE;
		if (str[i] == '\"' && !(sw & SQUOTE))
			sw ^= DQUOTE;
		if (str[i] == '|' && !sw)
			return (str + i);
	}
	return (NULL);
}

char	**split_pipe(char *str)
{
	char	*c;
	char	**tmp;
	char	*buf;

	c = find_pipe(str);
	tmp = (char **)ft_calloc(sizeof(char *), 3);
	if (!tmp)
		return (NULL);
	if (!c)
	{
		tmp[0] = ft_strdup(str);
		tmp[1] = ft_strdup("");
		return (tmp);
	}
	buf = ft_strndup(str, c - str);
	tmp[0] = buf;
	if (*(c + 1))
		buf = ft_strdup(c + 1);
	else
		buf = ft_strdup("");
	tmp[1] = buf;
	return (tmp);
}

int	*find_redirect(char *str)
{
	int	*idx;

	idx = (int *)malloc(sizeof(int) * 2);
	if (idx == 0)
		exit(1);
	idx[0] = -1;
	idx[1] = 0;
	while (str[++idx[0]])
	{
		if (str[idx[0]] == '\'' && !(idx[1] & DQUOTE))
			idx[1] ^= SQUOTE;
		if (str[idx[0]] == '\"' && !(idx[1] & SQUOTE))
			idx[1] ^= DQUOTE;
		if (idx[0] > 1 && isredirects(str[idx[0]]) && !idx[1])
			break ;
	}
	return (idx);
}

char	**split_redirect(char *str)
{
	char	**arr;
	int		*idx;

	idx = find_redirect(str);
	arr = (char **)malloc(sizeof(char *) * 3);
	if (!arr)
		return (NULL);
	arr[0] = ft_strndup(str, idx[0]);
	if (str[idx[1]])
		arr[1] = ft_strdup(str + idx[0]);
	else
		arr[1] = ft_strdup("");
	arr[2] = 0;
	free(idx);
	return (arr);
}

char	**split_command(char *str)
{
	int		idx[6];
	char	**tmp_strs;

	ft_bzero(idx, 6 * sizeof(int));
	tmp_strs = calloc_redirects(ft_strlen(str) + 1);
	idx[indx] = -1;
	while (str[++idx[indx]])
	{
		if (str[idx[indx]] == '\'' && !idx[dquote])
			idx[squote] = ~idx[squote];
		if (str[idx[indx]] == '\"' && !idx[squote])
			idx[dquote] = ~idx[dquote];
		if (isredirects(str[idx[indx]]) && !idx[squote] && !idx[dquote])
			idx[sw] = TRUE;
		if (idx[indx] > 0 && str[idx[indx]] == ' ' && \
			isword(str[idx[indx] - 1]) && !idx[squote] && !idx[dquote])
			idx[sw] = FALSE;
		if (idx[sw])
			(*tmp_strs)[idx[idx_str0]++] = str[idx[indx]]; 
		else
			(*(tmp_strs + 1))[idx[idx_str1]++] = str[idx[indx]];
	}
	return (tmp_strs);
}
