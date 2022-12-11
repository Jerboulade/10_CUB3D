# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/16 15:45:34 by jcarere           #+#    #+#              #
#    Updated: 2022/08/04 16:48:50 by jcarere          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
SRCDIR = ./src/
OBJDIR = ./obj/
INCL = ./includes/
MLX_DIR = ./minilibx_macos/
LIBMLX = $(MLX_DIR)libmlx.a
LIBDIR = ./libft/
LIB = $(LIBDIR)libft.a
SRC =	main.c init.c parse_file.c parse_info.c parse_map.c check_map_config.c \
		launch.c raycast.c action.c event.c init_images.c render_params.c \
		colors.c tool.c is_check.c free.c
OBJ = $(addprefix $(OBJDIR), $(SRC:%.c=%.o))
FRAMEWORK = -framework OpenGl -framework Appkit
REMOVE = /bin/rm -rf
C_CYAN = \033[1;96m
C_GREEN = \033[1;32m
C_MAG = \033[1;35m
C_RED = \033[0;31m
C_ORANGE = \033[0;33m
C_RESET = \033[0m
L_CLEAR = \033[K

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCL) -I$(MLX_DIR)
	@printf "$(C_MAG)Compiling 'cub3D':               \
	$(C_CYAN)[$(C_ORANGE)$<$(C_CYAN)] $(C_RESET) $(L_CLEAR)\r"

$(OBJDIR)%.o: $(BSRCDIR)%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCL) -I$(MLX_DIR)
	@printf "$(C_MAG)Compiling 'cub3D':               \
	$(C_CYAN)[$(C_ORANGE)$<$(C_CYAN)] $(C_RESET) $(L_CLEAR)\r"

$(NAME): $(OBJ)
	@printf "$(L_CLEAR)\r"
	@printf "$(C_CYAN)"
	@make -s -C $(MLX_DIR)
	@printf "$(C_RESET)"
	@make -s -C $(LIBDIR)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIB) $(LIBMLX) -lmlx $(FRAMEWORK)
	@printf "$(C_CYAN)'cub3D'    : $(C_GREEN)ready             \
	$(C_CYAN)[$(C_GREEN)✔$(C_CYAN)]$(C_RESET)"
	@printf "$(L_CLEAR)\n"

all: $(NAME)

bonus: re
	@printf "$(L_CLEAR)"
	@printf "$(C_CYAN)bonus      : $(C_GREEN)ready             \
	$(C_CYAN)[$(C_GREEN)✔$(C_CYAN)]$(C_RESET)\n"


clean:
	@make -C $(LIBDIR) clean
	@$(REMOVE) $(OBJDIR)
	@printf "$(C_CYAN)'cub3D'    : $(C_RED)objects deleted   \
	$(C_CYAN)[$(C_GREEN)✔$(C_CYAN)]$(C_RESET)\n"

fclean: clean
	@make -s -C $(MLX_DIR) clean
	@$(REMOVE) $(LIB)
	@printf "$(C_CYAN)'libft.a'  : $(C_RED)deleted           \
	$(C_CYAN)[$(C_GREEN)✔$(C_CYAN)]$(C_RESET)\n"
	@$(REMOVE) $(NAME)
	@printf "$(C_CYAN)'cub3D'    : $(C_RED)deleted           \
	$(C_CYAN)[$(C_GREEN)✔$(C_CYAN)]$(C_RESET)\n"

re: fclean all

.PHONY: all clean fclean re bonus norm
