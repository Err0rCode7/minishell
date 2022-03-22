/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taewan <taewan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:22:54 by seujeon           #+#    #+#             */
/*   Updated: 2022/03/22 00:03:37 by taewan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include <stdlib.h>

# include "libft.h"
# include "color.h"

# define MSG_QUOTE_ERR	"Invalid quote syntax"
# define MSG_IDDENTIFIER_ERR	"not a valid identifier"
# define MSG_GENERAL_SYNTAX_ERR	"syntax error"
# define MSG_FILE_NOT_FOUND_ERR	"No such file or directory"
# define MSG_FORK_ERR	"Fork Error"
# define MSG_FILE_OPEN_ERR	"File open error"
# define MSG_DUP_TWO_ERR	"dup2 Error"
# define MSG_PIPE_ERR	"Pipe Error"
# define MSG_OPEN_FD_WITH_TYPE_ERR	"Function : open_fd_with_type Error"
# define MSG_CMD_NOT_FOUND_ERR	"command not found"

# define STX_ERR		0
# define STX_OK			1

void	error_exit(char *msg, int exitcode);
void	prterr_exit(void);
int		prt_error(char *msg);
void	prt_cmd_err_shellname(char *msg, char *cmd, char *arg);

#endif
