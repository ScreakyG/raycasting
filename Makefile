NAME = cub3D
CFLAGS = -Wall -Wextra -Werror -g
CC = gcc

## COLORS ##

RED = \033[31m
GRE = \033[32m
GRA = \033[37m
BLU = \033[34m
EOC = \033[0m

#############


SRCS_DIR = srcs/
SRCS_FILES = main.c raycasting.c render.c movements.c
SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
SRCS_OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR) $(LIBFT_NAME)

MLX_DIR = minilibx-linux
MLX_NAME = libmlx.a
MLX = $(MLX_DIR) $(MLX_NAME)


%.o: %.c
		@echo "$(BLU) ● Compiling $^ 🔧$(EOC)"
		@$(CC) $(CFLAGS) -I/usr/include -Iminilibx-linux -c $< -o $@

all: $(LIBFT) $(MLX) $(NAME)


$(NAME): $(SRCS_OBJS)
		@echo "$(GRE)● cub3D ready ⚙️ $(EOC)"
		@$(CC) $(CFLAGS) $(SRCS_OBJS) -Lminilibx-linux -lmlx -L/usr/lib -L$(LIBFT_DIR) -lft -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT):
		@echo "$(GRE) Creating libft library ⚙️ $(EOC)"
		@make -sC $(LIBFT_DIR)

$(MLX):
		@echo "$(GRE) Creating minilibx library ⚙️$(EOC)"
		@make -sC $(MLX_DIR)


clean:
		@echo "$(RED)● Cleaning .o files 📁$(EOC)"
		@rm -rf $(SRCS_OBJS)
		@make clean -sC $(MLX_DIR)
		@make clean -sC $(LIBFT_DIR)

fclean: clean
		@echo "$(RED)● Deleting $(NAME) $(EOC)"
		@rm -rf $(NAME)
		@make clean -sC $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re



