# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltran <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/08 12:54:08 by ltran             #+#    #+#              #
#    Updated: 2017/12/03 17:00:08 by ltran            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

CC = gcc

SRCDIR = srcs

FLAGS = -Wall -Wextra -Werror

SRCS = main.c ls.c exec_key.c tools.c signal.c

SRC_N = $(addprefix $(SRCDIR)/, $(SRCS))

OBJDIR = objs

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFT= -L./libft/ -lft

all : $(NAME)

$(NAME): $(OBJS)
	make -C ./libft/
	$(CC) $(OBJS) $(LIBFT) $(FLAGS) -o $(NAME) -ltermcap -g

${OBJDIR}/%.o: srcs/%.c
	@mkdir -p ${OBJDIR}
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	make -C ./libft/ clean
	/bin/rm -rf $(OBJDIR)

fclean: clean
	make -C ./libft/ fclean
	/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
