/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:00:54 by taewan            #+#    #+#             */
/*   Updated: 2022/04/09 21:45:33 by taewan           ###   ########.fr       */
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

int	check_oldpwd(char **argv, t_data *data, int *is_oldpwd)
{
	char	**envp;

	*is_oldpwd = FALSE;
	if (argv[1] && ft_strcmp(argv[1], "-") == 0)
	{
		if (!data->oldpwd)
		{
			print_execute_err_3("minishell", argv[0], "OLDPWD not set");
			g_exit_status = 1;
			return (1);
		}
		envp = data->envp + get_env_var("OLDPWD", data->envp);
		if (!*envp)
		{
			print_execute_err_3("minishell", argv[0], MSG_OLDPWD_NOT_FOUND_ERR);
			g_exit_status = 1;
			return (1);
		}
		free(argv[1]);
		*is_oldpwd = TRUE;
		data->oldpwd = TRUE;
		argv[1] = ft_strdup(*envp + 7);
	}
	return (0);
}

int	set_pwd(t_data *data, char *oldpwd, int is_oldpwd)
{
	char	*tmp;

	tmp = ft_strjoin("OLDPWD=", oldpwd);
	if (!tmp)
		exit(1);
	add_env(&data->envp, tmp);
	free(oldpwd);
	free(tmp);
	oldpwd = getcwd(0, MAX_DIRLEN);
	if (!oldpwd)
		exit(1);
	if (is_oldpwd)
		printf("%s\n", oldpwd);
	tmp = ft_strjoin("PWD=", oldpwd);
	add_env(&data->envp, tmp);
	free(oldpwd);
	free(tmp);
	return (0);
}

int	check_to_home(char **argv, t_data *data, char *oldpwd, int is_oldpwd)
{
	char	*path;

	g_exit_status = 0;
	if (!chdir(argv[1]))
		return (0);
	path = find_home(argv[1], data->envp);
	if (!argv[1])
	{
		if (chdir(path))
			prt_cmd_err_s_name(MSG_HOME_NOT_FOUND_ERR, argv[0], NULL, 1);
		free(path);
		return (set_pwd(data, oldpwd, is_oldpwd));
	}
	if ((!ft_strncmp(argv[1], "~", 1) || !ft_strncmp(argv[1], "~/", 2))
		&& !chdir(data->home))
	{
		free(path);
		return (set_pwd(data, oldpwd, is_oldpwd));
	}
	if (path)
		free(path);
	return (1);
}

int	pt_cd(char **argv, t_data *data)
{
	char	*oldpwd;
	int		is_oldpwd;

	g_exit_status = 0;
	if (check_oldpwd(argv, data, &is_oldpwd))
		return (0);
	oldpwd = getcwd(0, MAX_DIRLEN);
	if (!oldpwd)
		exit(1);
	if (!chdir(argv[1]))
		return (set_pwd(data, oldpwd, is_oldpwd));
	if (!check_to_home(argv, data, oldpwd, is_oldpwd))
		return (0);
	free(oldpwd);
	g_exit_status = 1;
	print_execute_err_2(argv[0], argv[1], MSG_FILE_NOT_FOUND_ERR);
	return (0);
}
