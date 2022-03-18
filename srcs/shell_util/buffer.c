
#include "minishell.h"

int	init_buffer(t_buffer *buffer, size_t size)
{
	buffer->size = 0;
	buffer->arr = (char *)ft_calloc(sizeof(char), (size + 1));
	if (!buffer->arr)
		return (0);
	return (1);
}

void	flush_buffer(t_buffer *buffer, char **arr)
{
	buffer->arr[buffer->size] = 0;
	ft_combine(arr, buffer->arr);
	if (*arr == NULL)
		exit(1);
	buffer->size = 0;
}
