# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esuits <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/05 17:37:19 by esuits            #+#    #+#              #
#    Updated: 2018/01/21 15:39:46 by esuits           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS = ft_args.c ft_form.c ft_last.c ft_mod.c ft_printf.c
LIB = libft.a
OBJ = $(SRCS:.c=.o)
CFLAGS = -Werror -Wextra -Wall

all : lib $(NAME)

lib :
	make -C libft;
$(NAME) : $(OBJ)
	cp libft/libft.a $(NAME)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME);

%.o : %.c
	gcc $(CFLAGS) -c $(SRCS) -I libft;

clean :
	make clean -C libft;
	rm -f $(OBJ);

fclean : clean
	make fclean -C libft;
	rm -rf $(NAME);

re : fclean all
	make re -C libft
