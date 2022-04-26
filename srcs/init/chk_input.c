/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewakim <taewakim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:42 by taewan            #+#    #+#             */
/*   Updated: 2022/04/26 14:52:01 by taewakim         ###   ########.fr       */
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
	{
		g_exit_status = 1;
		return (TRUE);
	}
	return (FALSE);
}

static void	init_args(t_args *args)
{
	args->cnt_space = 0;
	args->flag_sq = 0;
	args->flag_bq = 0;
	args->flag_escape = 0;
}

static int	chk_is_valid(char *str, int i)
{
	t_args	args;

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
	{
		g_exit_status = 1;
		return (FALSE);
	}
	if (args.flag_sq || args.flag_bq)
	{
		ft_putstr_fd(MSG_QUOTE_ERR, STDERR);
		write(2, "\n", 1);
		g_exit_status = 258;
		return (FALSE);
	}
	return (TRUE);
}

int	pre_process_input(char **str)
{
	add_history(*str);
	if (!(chk_is_valid(*str, -1)))
	{
		free(*str);
		return (FALSE);
	}
	return (TRUE);
}
