# Variables
NAME = cub3d
CC = clang
CFLAGS = -Wall -Wextra -Werror -g -I./includes

MLX_DIR = include/mlx
LIBFT_DIR = include/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a
LFLAGS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm -lz

SRC = src/main.c src/player.c src/error.c src/graphics.c src/parser.c src/textures.c src/validation.c src/gnl/get_next_line.c src/gnl/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

# Rules
all: $(MLX) $(LIBFT) $(NAME)

# Only clone MiniLibX if the directory doesn't exist
$(MLX):
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "Cloning MiniLibX..."; \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
#	rm -rf $(MLX_DIR)

re: fclean all

# Phony Targets
.PHONY: all clean fclean re

make test1:
	cc tests/test.c unity/src/unity.c src/gnl/get_next_line.c src/gnl/get_next_line_utils.c src/parser.c src/error.c src/validation.c include/libft/libft.a && ./a.out
