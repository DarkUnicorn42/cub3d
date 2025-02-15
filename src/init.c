/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:02:18 by mwojtcza          #+#    #+#             */
/*   Updated: 2025/02/15 12:21:46 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

void	init_game_struct(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->data = NULL;
	game->map = NULL;
	game->copy_map = NULL;
	game->north_texture_path = NULL;
	game->south_texture_path = NULL;
	game->west_texture_path = NULL;
	game->east_texture_path = NULL;
}

int	init_game(t_game *game, char *file)
{
	init_game_struct(game);
	if (!validation(game, file))
		return (0);
	init_player(&game->player);
	game->fd = open(file, O_RDONLY);
	if (!parsing(game))
		return (error(INVALID_MAP, game));
	if (!valid_data(game))
		return (error(INVALID_MAP, game));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp,
			&game->size_line, &game->endian);
	if (!load_all_textures(game))
		return (error(INVALID_FILE, game));
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (1);
}

void	init_ray(t_ray *ray, t_player *player, float ray_angle)
{
	ray->raydirx = cosf(ray_angle);
	ray->raydiry = sinf(ray_angle);
	ray->mapx = (int)(player->x / BLOCK);
	ray->mapy = (int)(player->y / BLOCK);
}
