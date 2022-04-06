/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:42 by taewan            #+#    #+#             */
/*   Updated: 2022/04/07 02:53:28 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	chk_quote(t_args *args, char chk)
{
	if (chk == '\'' && !(args->flag_bq))
	{
		if (args->flag_sq)
			args->flag_sq = 0;
		else
			args->flag_sq = 1;
	}
	if (chk == '"' && !(args->flag_sq))
	{
		if (args->flag_bq)
			args->flag_bq = 0;
		else
			args->flag_bq = 1;
	}
}

static int	is_invld_space(char c)
{
	if (c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (TRUE);
	return (FALSE);
}

static void	init_args(t_args *args)
{
	args->cnt_space = 0;
	args->flag_sq = 0;
	args->flag_bq = 0;
}

static int	chk_is_valid(char *str)
{
	int		i;
	t_args	args;

	i = -1;
	init_args(&args);
	while (str[++i])
	{
		if (is_invld_space(str[i]))
			return (FALSE);
		else if (str[i] == ' ')
			args.cnt_space++;
		chk_quote(&args, str[i]);
	}
	if (args.cnt_space == ft_strlen(str))
		return (FALSE);
	if (args.flag_sq || args.flag_bq)
	{
		ft_putendl_fd(MSG_QUOTE_ERR, STDERR);
		return (FALSE);
	}
	return (TRUE);
}

int	pre_process_input(char *str)
{
	add_history(str);
	if (!(chk_is_valid(str)))
	{
		free(str);
		g_exit_status = 1;
		return (FALSE);
	}
	return (TRUE);
}
