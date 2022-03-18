
#include "minishell.h"

int	combine_variable(char **arr, char *str, char **envp)
{
	char	*tmp;
	int		size;

	size = 0;
	tmp = interprete_dollar_sign(str, &size, envp);
	if (tmp == 0)
		exit(1);
	ft_combine(arr, tmp);
	if (!*arr)
		exit(1);
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
	arr = ft_strdup("");
	if (!arr)
		exit(1);
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

	if (init_buffer(&buff, BUFFER_SIZE) == 0) // 흠...
		exit(1); 
	arr = find_dollar(str, envp, &buff); // 모든 $변수를 파싱한 문자열 반환
	flush_buffer(&buff, &arr); // 버퍼를 비움
	free(buff.arr); // 버퍼 free
	free(str);
	return (arr);
}
