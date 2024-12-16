# Variables
NAME = cub3d
CC = clang
CFLAGS = -Wall -Wextra -Werror -g -I./includes

MLX_DIR = include/mlx
MLX = $(MLX_DIR)/libmlx.a
LFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRC = src/main.c src/player.c

OBJ = $(SRC:.c=.o)

# Rules
all: $(MLX) $(NAME)

# Only clone MiniLibX if the directory doesn't exist
$(MLX):
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "Cloning MiniLibX..."; \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_DIR); \
	fi
	make -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
#	rm -rf $(MLX_DIR)

re: fclean all

# Phony Targets
.PHONY: all clean fclean re
