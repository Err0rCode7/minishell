/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:00:54 by taewan            #+#    #+#             */
/*   Updated: 2022/04/05 23:11:48 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home(char *str, char **envp)
{
	int		i;
	char	*tmp;
	char	*arr;

	i = 0;
	while (envp[i] && !correct_env(envp[i], "HOME", 4))
		i++;
	if (!envp[i])
		return (NULL);
	arr = ft_strndup(envp[i] + 5, ft_strlen(envp[i] + 5));
	if (arr == NULL)
		return (NULL);
	if (str && str[0] == '~')
		str += 1;
	if (str && str[0] == '/')
		tmp = ft_strndup(arr, ft_strlen(arr));
	else
		tmp = ft_strjoin(arr, "/");
	free(arr);
	arr = ft_strjoin(tmp, str);
	free(tmp);
	return (arr);
}

int	pt_cd(char **argv, t_data *data)
{
	char	*path;

	g_exit_status = 0;
	if (!chdir(argv[1]))
		return (0);
	path = find_home(argv[1], data->envp);
	if (!argv[1])
	{
		if (chdir(path))
		{
			prt_cmd_err_shellname(MSG_HOME_NOT_FOUND_ERR, argv[0], NULL);
			g_exit_status = 1;
		}
		free(path);
		return (0);
	}
	if ((!ft_strncmp(argv[1], "~", 1) || !ft_strncmp(argv[1], "~/", 2))
		&& !chdir(data->home))
	{
		free(path);
		return (0);
	}
	if (path)
		free(path);
	g_exit_status = 1;
	print_execute_err_2(argv[0], argv[1], MSG_FILE_NOT_FOUND_ERR);
	return (0);
}
