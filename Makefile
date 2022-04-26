# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taewakim <taewakim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/23 15:11:50 by seujeon           #+#    #+#              #
#    Updated: 2022/04/26 14:51:17 by taewakim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SUFFIXES: .c .o

NAME	=	minishell
NAME_FT	=	libft.a
NAME_RL	=	readline.a

CP		=	cp
RM		=	rm -f
MKDIR	=	mkdir -p
MV		=	mv
ECHO	=	echo
MAKE	=	make --no-print-directory


# ----------------------------------
# Echo Colors
# ----------------------------------

NOCOLOR		= \033[0m
RED			= \033[0;31m
GREEN		= \033[0;32m
ORANGE		= \033[0;33m
BLUE		= \033[0;34m
PURPLE		= \033[0;35m
CYAN		= \033[0;36m
LIGHTGRAY	= \033[0;37m
DARKGRAY	= \033[1;30m
LIGHTRED	= \033[1;31m
LIGHTGREEN	= \033[1;32m
YELLOW		= \033[1;33m
LIGHTBLUE	= \033[1;34m
LIGHTPURPLE	= \033[1;35m
LIGHTCYAN	= \033[1;36m
WHITE		= \033[1;37m

# ----------------------------------
# Mandatory source files
# ----------------------------------

MAIN_MANDA	=	main.c

# executor

SRCS	=	execute.c				\
			cmd_tokenizer.c			\
			cmd_tokenizer2.c		\
			pt_exit.c				\
			pt_env.c				\
			pt_export.c				\
			pt_cd.c					\
			pt_unset.c				\
			pt_pwd.c				\
			pt_echo.c				\
			pt_exit_status.c		\
			switch_routine.c		

# init

SRCS	+=	signal.c				\
			signal2.c				\
			input_cmd.c				\
			chk_input.c				\
			init_data.c

# lexer

SRCS	+=	lexer.c					\
			syntax.c

# libtree

SRCS	+=	tree.c

# shell_util

SRCS	+=	divide_parse.c			\
			parse_util.c			\
			parse_util2.c 			\
			split_str.c 			\
			pipex_util.c 			\
			replace_dollar_sign.c 	\
			pipex.c 				\
			error.c 				\
			buffer.c				\
			parse_util3.c			\
			pipex_util2.c			\
			pipex_util3.c

# print banner img

SRCS	+=	prt_image.c

# ----------------------------------
# Object files
# ----------------------------------

OBJS_MANDA	=	$(addprefix $(DIR_OBJ)/, $(SRCS:%.c=%.o))
OBJS_MANDA	+=	$(addprefix $(DIR_OBJ)/, $(MAIN_MANDA:%.c=%.o))

# ----------------------------------
# Directories and Paths
# ----------------------------------

DIR_INC	=	./includes
DIR_SRC	=	./srcs
DIR_OBJ	=	./obj
DIR_FT	=	./libft

# intel Mac Cluster o readline
DIR_RL	=	/Users/$(USER)/.brew/opt/readline/lib/
RL_INC	=	/Users/$(USER)/.brew/opt/readline/include/

# intel Mac Cluster x readline
# DIR_RL 	=	/usr/local/opt/readline/lib
# RL_INC	=	/usr/local/opt/readline/include

# linux readline
#DIR_RL	=	/usr/lib/x86_64-linux-gnu
#RL_INC	=	/usr/include/

# M1 readline
# DIR_RL = /opt/homebrew/opt/readline/lib
# RL_INC = /opt/homebrew/opt/readline/include

SUBDIRS	=	executor	\
			init		\
			lexer		\
			libtree		\
			shell_util

VPATH	=	$(DIR_SRC) $(addprefix $(DIR_SRC)/, $(SUBDIRS))

# ----------------------------------
# Compiler and flags
# ----------------------------------

CC		=	gcc
CFLAGS	=	-Werror -Wextra -Wall
CLIBFMW	=	-L$(DIR_FT) -lft -L$(DIR_RL) -lreadline

# ----------------------------------
# Rules
# ----------------------------------

all				: $(NAME)

$(DIR_OBJ)		:
			@$(MKDIR) $@

$(DIR_OBJ)/%.o	: %.c
			@$(CC) $(CFLAGS) -I$(DIR_INC) -I$(DIR_FT) -I$(RL_INC) -c $< -o $@
			@$(ECHO) "Compiled $(ORANGE)" $< " $(GREEN)Successfully$(NOCOLOR)"

$(NAME)			: $(DIR_FT)/$(NAME_FT) $(DIR_OBJ) $(OBJS_MANDA)
			@$(CC) $(CFLAGS) -I$(DIR_INC) $(OBJS_MANDA) $(CLIBFMW) -o $(NAME)
			@$(ECHO) "Maked $(BLUE)$(NAME)$(NOCOLOR) $(GREEN)Successfully$(NOCOLOR)"


$(DIR_FT)/$(NAME_FT):
			@$(ECHO) "Summoning $(ORANGE)$(NAME_FT)$(NOCOLOR) ..."
			@$(MAKE) -C $(DIR_FT) all
			@$(ECHO) "Summoned $(ORANGE)$(NAME_FT)$(ORANGE) $(GREEN)Successfully$(NOCOLOR)"


clean:
			@$(MAKE) -C $(DIR_FT) clean
			@$(ECHO) "Clean up $(RED)FT$(NOCOLOR)"

			@$(RM) -r $(DIR_OBJ)
			@$(ECHO) "Clean up $(RED)$(NAME)$(NOCOLOR)"

fclean:		clean
			@$(MAKE) -C $(DIR_FT) fclean
			@$(RM) -r $(NAME)
			@$(ECHO) "Removed $(RED)$(NAME)$(NOCOLOR)"

re:			fclean $(NAME)
