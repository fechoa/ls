# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gkelsie <gkelsie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/13 06:31:30 by marmand           #+#    #+#              #
#    Updated: 2022/04/07 19:49:06 by gkelsie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LIBFT = ./libft/libft.a

NAME = libftprintf.a

SRCS =  srcs/ft_printf.c \
			srcs/ft_parse_format.c \
			srcs/ft_print_char.c \
			srcs/ft_print_hex.c \
			srcs/ft_print_num.c \
			srcs/ft_print_percent.c \
			srcs/ft_print_one.c \
			srcs/ft_print_ptr.c \
			srcs/ft_print_str.c \
			srcs/ft_print_unsigned.c \

CC = gcc

FLAGS = -c -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@cp $(LIBFT) $(NAME)
	@ar -rcs $(NAME) $(OBJS)

all : $(NAME)

clean :
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJS)

%.o : %.c srcs/ft_printf.h
	@$(CC) $(FLAGS) $< -o $@

fclean : clean
	@$(MAKE) fclean -C ./libft
	@rm -rf $(NAME)

re : fclean all

bonus: all