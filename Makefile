NAME = pipex
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INCLUDE = inc/
FOLDER = srcs/
OBJFOLDER = obj/
LIBFT = libft/
LIBFT_LIB = $(LIBFT)libft.a
SRCS = ft_error.c ft_split.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
       ft_strlen.c ft_strnstr.c main.c pipex.c
OBJS = $(addprefix $(OBJFOLDER), $(SRCS:.c=.o))

$(OBJFOLDER)%.o: $(FOLDER)%.c
	@mkdir -p $(OBJFOLDER)
	$(CC) $(CFLAGS) -I$(INCLUDE) -I$(LIBFT) -c $< -o $@

$(NAME): $(LIBFT_LIB) $(OBJS)
	$(CC) -o $(NAME) $(OBJS) -L$(LIBFT) -lft

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT)

all: $(NAME)

clean:
	rm -rf $(OBJFOLDER)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
