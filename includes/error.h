/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:22:54 by seujeon           #+#    #+#             */
/*   Updated: 2022/04/28 22:47:22 by seujeon          ###   ########.fr       */
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
# define MSG_HOME_NOT_FOUND_ERR	"HOME not set"
# define MSG_INVALID_ARG_ERR	"Invalid argument"
# define MSG_DIR_ERR	"is a directory"
# define MSG_PERMISSION_ERR	"Permission denied"
# define MSG_OLDPWD_NOT_FOUND_ERR	"OLDPWD not set"
# define MSG_ARG_ERR "filename argument required"

# define STX_ERR		0
# define STX_OK			1

#endif
