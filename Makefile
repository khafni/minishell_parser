# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aabounak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/14 18:00:02 by aabounak          #+#    #+#              #
#    Updated: 2021/02/14 19:16:10 by aabounak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror

LIBNAME = libft.a

NAME = minishell

EXEC = minishell

SRC = aksh.c \
get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBNAME): $(SRC)
	make -C libft/
	cp libft/$(LIBNAME) ./

$(NAME): $(LIBNAME)
	@echo "Compilation in progress! DO NOT INTERRUPT!"
	gcc $(FLAGS) $(SRC) libft.a -D BUFFER_SIZE=666 -o $(EXEC)
	@echo "Compilation done! :)"

clean:
	make clean -C libft/
	rm -f *.o

fclean: clean
	make fclean -C libft/
	rm -f *.a
	rm -f $(EXEC)

re: fclean all
