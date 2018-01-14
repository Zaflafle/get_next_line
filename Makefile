# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macuguen <macuguen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/21 00:45:39 by macuguen          #+#    #+#              #
#    Updated: 2017/12/03 01:59:50 by macuguen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compilation
CC =		gcc
CFLAGS =	-Wall -Wextra -Werror -I. 

#Binary
NAME =		get_next_line

# Directories
SRCDIR =	srcs
OBJDIR =	objs
INCDIR =	includes \
			libft/includes\

# Source
SRC = 		get_next_line.c \
		
OBJ = $(SRC:.c=.o)

# Prefixes
LIBFT = 	-L./libft/ -lft
LIBFT_PATH = ./libft

all: $(NAME)

$(NAME): lib $(OBJ)	
				@$(CC) $(CFLAGS) $(SRC) $(LIBFT) -o $(NAME)

lib:
	@make -C $(LIBFT_PATH)

%.o: $(SRC) %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all
