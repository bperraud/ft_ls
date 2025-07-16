# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/22 20:29:49 by bperraud          #+#    #+#              #
#    Updated: 2022/01/22 20:29:49 by bperraud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRC				= ft_printf.c

OBJ	  			= $(SRC:.c=.o)

CC				= gcc
RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror 

NAME			= libftprintf.a

all:			$(NAME)

$(NAME): 		$(OBJ)
				$(MAKE) bonus -C ./libft
				cp libft/libft.a $(NAME)
				ar rs $(NAME) $(OBJ) 

clean:
				$(MAKE) clean -C ./libft
				$(RM) $(OBJ)

fclean:			clean
				$(MAKE) fclean -C ./libft
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re 