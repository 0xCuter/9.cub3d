# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvandenb <vvandenb@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/11 14:08:44 by vvandenb          #+#    #+#              #
#    Updated: 2022/05/16 10:58:49 by vvandenb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror	\
		-D BUFFER_SIZE=256		\
		-I $(HEADERS_DIR) -I $(LIBFT_DIR) -I $(LIBX_DIR)
ifdef DEBUG
	CFLAGS += -g 
endif
ifdef FSAN
	CFLAGS += -fsanitize=address
endif

SRCS_DIR = srcs/
HEADERS_DIR = includes/
HEADERS = $(HEADERS_DIR)main.h $(HEADERS_DIR)keymap.h
NAME = cub3D
SRCS = $(SRCS_DIR)main.c $(SRCS_DIR)init.c $(SRCS_DIR)utils.c	\
		$(SRCS_DIR)mlx/mlx_utils.c $(SRCS_DIR)mlx/hooks.c	\
		$(SRCS_DIR)gnl/get_next_line.c $(SRCS_DIR)gnl/get_next_line_utils.c	\
		$(SRCS_DIR)debug/map.c
OBJS = $(SRCS:c=o)

#LIBFT
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_FLAGS = -lft -L$(LIBFT_DIR)

#MACOS minilibx
LIBX_DIR = minilibx_macos/
LIBX = $(LIBX_DIR)libmlx.a
LIBX_FLAGS = -l mlx -L $(LIBX_DIR) -framework OpenGL -framework AppKit

#LINUX minilibx and math lib
ifdef LINUX
	LIBX_DIR = minilibx-linux/
	LIBX = $(LIBX_DIR)libmlx.a
	LIBX_FLAGS = -l mlx -L $(LIBX_DIR) -lXext -lX11
	CFLAGS := $(CFLAGS) -lm
endif

all: $(NAME)

%.o: %.c $(HEADERS) Makefile
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT): FORCE
	@make bonus -C $(LIBFT_DIR)

$(LIBX): FORCE
	@make -C $(LIBX_DIR)

$(NAME): $(LIBFT) $(LIBX) $(OBJS)
	@echo Compiling...
	@$(CC) $(OBJS) -o $@ $(CFLAGS) $(LIBFT_FLAGS) $(LIBX_FLAGS)
	@echo Compiled!

clean:
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(LIBX_DIR)
	@rm -f $(OBJS)
	@echo Cleaned!

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo Fcleaned!

re: fclean all

FORCE:

.PHONY: FORCE clean fclean re
