SRCS = ./CPCA/CPCA.a ./libft/libft.a ./dlist/*.c ./mask.c ./pipelines.c ./redirection_splitting/*.c ./command_table/*.c command_table_generator.c ./main.c
NAME	= miniSHELL 
CC	 = gcc
CFLAGS	 = -ltermcap

all:$(NAME)
$(NAME):
	@$(MAKE) -C CPCA
	@$(MAKE) -C libft 
	@echo "\033[0;32mcompiling miniSHELL"
	@gcc -g $(CFLAGS) CPCA/CPCA.a libft/libft.a $(SRCS) -o $(NAME) 

clean:
	@$(MAKE) -C CPCA clean
fclean:
	@rm -f $(NAME)
	@$(MAKE) -C CPCA fclean
	@$(MAKE) -C libft fclean
	@echo "\033[0;33meverything cleaned"

re : fclean all