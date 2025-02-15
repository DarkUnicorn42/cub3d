/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:19:09 by mwojtcza          #+#    #+#             */
/*   Updated: 2025/02/15 12:26:26 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_game(t_game *game)
{
	free_texture_paths(game);
	free_all_textures(game);
	if (game->map)
		free_map(game->map);
	if (game->copy_map)
		free_map(game->copy_map);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	return (1);
}

int	close_button(t_game *game)
{
	close_game(game);
	exit(0);
	return (0);
}

void	draw_minimap(t_game *game)
{
	int		map_x;
	int		map_y;
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
				continue ;
			}
			draw_sq_mm(map_x, map_y, color, game);
			map_x++;
		}
		map_y++;
	}
	draw_sq_mm(game->player.x / BLOCK, game->player.y / BLOCK, 0x00FF00, game);
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		ray_angle;
	float		angle_increment;
	int			column;

	player = &game->player;
	rotate_player(player);
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
	t_game	game;

	if (argc != 2)
		return (error(NO_FILE, &game));
	game.s_path = 0;
	game.n_path = 0;
	game.e_path = 0;
	game.w_path = 0;
	if (!init_game(&game, argv[1]))
		return (0);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, close_button, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
