# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marmand <marmand@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 17:08:51 by marmand           #+#    #+#              #
#    Updated: 2022/04/13 15:31:12 by marmand          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRCS =  flags.c \
		ft_ls.c \
		str_vector.c \
		utils.c

CC = gcc

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@$(MAKE) -C ./ft_printf
	@$(CC) $(FLAGS) $(OBJS) ./ft_printf/libftprintf.a -o $@
	@echo "Ft_ls is ready ✅"

ft_ls.o: ft_ls.c ft_ls.h flags.h str_vector.h
	@$(CC) $(FLAGS) -c $<

flags.o: flags.c flags.h
	@$(CC) $(FLAGS) -c $<

str_vector.o: str_vector.c str_vector.h
	@$(CC) $(FLAGS) -c $<

utils.o: utils.c ft_ls.h flags.h str_vector.h
	@$(CC) $(FLAGS) -c $<

all : $(NAME)

clean :
	@$(MAKE) clean -C ./ft_printf
	@rm -rf $(OBJS)
	@echo "Ft_ls was stopped ❌"

fclean : clean
	@$(MAKE) fclean -C ./ft_printf
	@rm -rf $(NAME)
	

re : fclean all
