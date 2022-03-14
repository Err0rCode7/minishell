/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:22:54 by seujeon           #+#    #+#             */
/*   Updated: 2022/03/14 15:22:55 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include <stdlib.h>

# include "libft.h"
# include "color.h"

void	error_exit(char *msg, int exitcode);
void	prterr_exit(void);
int		prt_error(char *msg);

#endif
