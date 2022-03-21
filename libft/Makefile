# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: taewan <taewan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 15:46:03 by seujeon           #+#    #+#              #
#    Updated: 2022/03/22 00:14:55 by taewan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Werror -Wall -Wextra

INCLDS = includes

NAME = libft.a

FUNC = ft_memset \
	   ft_bzero \
	   ft_memcpy \
	   ft_memccpy \
	   ft_memmove \
	   ft_memchr \
	   ft_memcmp \
	   ft_strlen \
	   ft_strlcpy \
	   ft_strlcat \
	   ft_strchr \
	   ft_strrchr \
	   ft_strnstr \
	   ft_strncmp \
	   ft_strcmp \
	   ft_atoi \
	   ft_isalpha \
	   ft_isdigit \
	   ft_isalnum \
	   ft_isascii \
	   ft_isprint \
	   ft_toupper \
	   ft_tolower \
	   ft_calloc \
	   ft_strdup \
	   ft_substr \
	   ft_strjoin \
	   ft_strtrim \
	   ft_split \
	   ft_itoa \
	   ft_strmapi \
	   ft_putchar_fd \
	   ft_putstr_fd \
	   ft_putendl_fd \
	   ft_putnbr_fd \
	   ft_isspace	\
	   get_next_line_utils	\
	   get_next_line

FUNC_B = ft_lstnew \
		 ft_lstadd_front \
		 ft_lstsize \
		 ft_lstlast \
		 ft_lstadd_back \
		 ft_lstdelone \
		 ft_lstclear \
		 ft_lstiter \
		 ft_lstmap

SRCS = $(addsuffix .c, $(FUNC))
OBJS = $(addsuffix .o, $(FUNC))

SRCS_B = $(addsuffix .c, $(FUNC_B))
OBJS_B = $(addsuffix .o, $(FUNC_B))

all : $(NAME)

$(NAME) : $(OBJS)
		@ar rcs $@ $^

bonus : $(OBJS) $(OBJS_B)
		@ar rcs $(NAME) $(OBJS) $(OBJS_B)

.c.o :
		@$(CC) $(CFLAGS) -c $^ -o $@

so: $(OBJS)
	$(CC) -shared -o libft.so $(OBJS)

clean :
		@rm -f $(OBJS) $(OBJS_B) $(NAME)

fclean : clean
		@rm -f $(NAME)

re : fclean all

.PHONY : bonus all clean fclean re
