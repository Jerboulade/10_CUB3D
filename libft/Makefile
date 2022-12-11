# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/21 17:16:36 by jcarere           #+#    #+#              #
#    Updated: 2022/01/15 17:20:47 by jcarere          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re bonus

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = ./lib_src/
PF_SRCDIR = $(SRCDIR)ft_printf_src/
OBJDIR = ./lib_obj/
INCL = ./lib_includes/
SRC = ft_strnstr.c ft_isdigit.c ft_putstr_fd.c ft_strlcpy.c ft_strlen.c\
ft_memcmp.c ft_putnbr_fd.c ft_strchr.c ft_bzero.c ft_strjoin.c ft_isascii.c\
ft_memcpy.c ft_memccpy.c ft_isprint.c ft_putendl_fd.c ft_toupper.c ft_split.c\
ft_strrchr.c ft_isalpha.c ft_memchr.c ft_putchar_fd.c ft_memset.c ft_substr.c\
ft_strncmp.c ft_strmapi.c ft_strtrim.c ft_memmove.c ft_strlcat.c ft_calloc.c\
ft_strdup.c ft_atoi.c ft_isalnum.c ft_itoa.c ft_tolower.c get_next_line.c\
ft_atoi_base.c ft_atol.c ft_strequ.c ft_abs.c ft_lstadd_back.c ft_lstnew.c\
ft_lstlast.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstsize.c\
ft_lstadd_front.c ft_lstdelone.c ft_unitoa_base.c ft_count_digit_base.c
PF_SRC = ft_printf.c ft_dprintf.c printf_parsing.c get_args.c tool.c\
handle_signed.c handle_unsigned.c handle_npc.c handle_char.c handle_str.c\
handle_fraction.c big_int_manip.c handle_float.c float_compute.c
OBJ = $(addprefix $(OBJDIR), $(SRC:%.c=%.o)) $(PF_OBJ)
PF_OBJ = $(addprefix $(OBJDIR), $(PF_SRC:%.c=%.o))
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
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCL)
	@printf "$(C_MAG)Compiling 'libft.a':           \
	$(C_CYAN)[$(C_ORANGE)$<$(C_CYAN)] $(C_RESET) $(L_CLEAR)\r"

$(OBJDIR)%.o: $(PF_SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCL)
	@printf "$(C_MAG)Compiling 'libft.a':           \
	$(C_CYAN)[$(C_ORANGE)$<$(C_CYAN)] $(C_RESET) $(L_CLEAR)\r"

$(NAME): $(OBJDIR) $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "$(C_CYAN)'libft.a'  : $(C_GREEN)created           \
	$(C_CYAN)[$(C_GREEN)✔$(C_CYAN)]$(C_RESET)"
	@printf "$(L_CLEAR)\n"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

all: $(NAME)

clean:
	@$(REMOVE) $(OBJDIR)
	@printf "$(C_CYAN)'libft.a'  : $(C_RED)objects deleted   \
	$(C_CYAN)[$(C_GREEN)✔$(C_CYAN)]$(C_RESET)\n"

fclean: clean
	@$(REMOVE) $(NAME)
	@printf "$(C_CYAN)'libft.a'  : $(C_RED)deleted           \
	$(C_CYAN)[$(C_GREEN)✔$(C_CYAN)]$(C_RESET)\n"

re: fclean all
