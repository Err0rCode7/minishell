/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 00:01:42 by taewan            #+#    #+#             */
/*   Updated: 2022/04/09 12:07:28 by taewan           ###   ########.fr       */
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
		ft_putstr_fd(MSG_QUOTE_ERR, STDERR);
		write(2, "\n", 1);
		g_exit_status = 258;
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
		return (FALSE);
	}
	return (TRUE);
}
