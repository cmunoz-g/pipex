NAME = pipex
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCLUDE = inc/
OBJFOLDER = obj/
FOLDER = srcs/
SRCS = main.c pipex.c utils.c awk.c ft_error.c
OBJS = $(SRCS:%.c=$(OBJFOLDER)%.o)
LIBFT = libft

OBJS = $(SRCS:%.c=$(OBJFOLDER)%.o)

$(OBJFOLDER)%.o: $(FOLDER)%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT)/libft.a

all: $(NAME)

clean:
	@rm -rf $(OBJFOLDER)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re

