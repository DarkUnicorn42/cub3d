#include "../include/cub3d.h"

int	init_game(t_game *game, char *file)
{
	if (!validation(game, file))
		return (0);
	init_player(&game->player);
	game->fd = open(file, O_RDONLY);
	if (!parsing(game))
		return (error(INVALID_MAP));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	if (!load_all_textures(game))
		return (error(INVALID_FILE));
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (1);
}

void free_map(char **map)
{
	int i = 0;
	if (!map)
		return;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	close_game(t_game *game)
{
	free_texture_paths(game);
	free_all_textures(game);
	free_map(game->map);
	free_map(game->copy_map);
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (1);
}

int close_button(t_game *game)
{
	close_game(game);
	exit(0);
	return (0);
}

void draw_minimap(t_game *game)
{
	int		map_x;
	int		map_y;
	int		block_size = 8;
	int		color;

	map_y = 0;
	while (game->map[map_y])
	{
		map_x = 0;
		while (game->map[map_y][map_x])
		{
			if (game->map[map_y][map_x] == '1')
				color = 0xFFFFFF;
			else if (ft_strchr("0NSEW", game->map[map_y][map_x]))
				color = 0x000000;
			else
			{
				map_x++;
				continue;
			}
			draw_square(map_x * block_size, map_y * block_size, block_size, color, game);
			map_x++;
		}
		map_y++;
	}
	draw_square(game->player.x / BLOCK * block_size, game->player.y / BLOCK * block_size, block_size / 2, 0x00FF00, game);
}

int draw_loop(t_game *game)
{
	t_player	*player;
	float		ray_angle;
	float		angle_increment;
	int			column;

	player = &game->player;
	move_player(player, game);
	clear_image(game);
	draw_floor_ceiling(game);
	ray_angle = player->angle - (PI / 6);
	angle_increment = (PI / 3) / WIDTH;
	column = 0;
	while (column < WIDTH)
	{
		draw_line(player, game, ray_angle, column);
		ray_angle += angle_increment;
		column++;
	}
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game game;

	if (argc != 2)
		return (error(NO_FILE));
	if (!init_game(&game, argv[1]))
		return (0);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, close_button, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);

	mlx_loop(game.mlx);

	return (0);
}
