
#include "minishell.h"

int	combine_variable(char **arr, char *str, char **envp)
{
	char	*tmp;
	int		size;

	size = 0;
	tmp = interprete_dollar_sign(str, &size, envp);
	ft_combine(arr, tmp);
	free(tmp);
	return (size - 1);
}

void	ignore_single_quote(char *str, int *idx, t_buffer *buff)
{
	if (str[*idx] == '\'' && buff->size < BUFFER_SIZE)
	{
		buff->arr[buff->size++] = str[*idx];
		while (str[++(*idx)] != '\'' && buff->size < BUFFER_SIZE)
			buff->arr[buff->size++] = str[*idx];
	}
}

char	*find_dollar(char *str, char **envp, t_buffer *buff)
{
	int		i;
	int		sw;
	char	*arr;

	i = -1;
	sw = 0;
	arr = ft_strndup("", 0);
	while (str[++i])
	{
		if (buff->size == BUFFER_SIZE)
			flush_buffer(buff, &arr);
		if (str[i] == '\'' && !(sw & DQUOTE))
			sw ^= SQUOTE;
		if (str[i] == '\"' && !(sw & SQUOTE))
			sw ^= DQUOTE;
		if (is_dollar_sign(str[i]) && !(sw & SQUOTE))
		{
			flush_buffer(buff, &arr);
			i += combine_variable(&arr, str + i, envp);
		}
		else
			buff->arr[buff->size++] = str[i];
	}
	return (arr);
}

char	*replace_dollar_sign(char *str, char **envp)
{
	char		*arr;
	t_buffer	buff;

	init_buffer(&buff, BUFFER_SIZE);
	arr = find_dollar(str, envp, &buff);
	flush_buffer(&buff, &arr);
	free(buff.arr);
	free(str);
	return (arr);
}
