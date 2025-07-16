SRC				= main.c utils.c parser.c

OBJ	  			= $(SRC:.c=.o)

CC				= gcc
RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror 

NAME			= ft_ls

all:			$(NAME)

$(NAME): 		$(OBJ)
				$(MAKE) -C ./libft
				$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libftprintf.a

clean:
				$(MAKE) clean -C ./libft
				$(RM) $(OBJ)

fclean:			clean
				$(MAKE) fclean -C ./libft
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re 

