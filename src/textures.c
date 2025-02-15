/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:11:06 by mwojtcza          #+#    #+#             */
/*   Updated: 2025/02/15 12:20:01 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (0);
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	return (1);
}

int	load_all_textures(t_game *game)
{
	if (!load_texture(game, &game->north_texture, game->north_texture_path))
		return (error(INVALID_FILE, game));
	if (!load_texture(game, &game->south_texture, game->south_texture_path))
		return (error(INVALID_FILE, game));
	if (!load_texture(game, &game->west_texture, game->west_texture_path))
		return (error(INVALID_FILE, game));
	if (!load_texture(game, &game->east_texture, game->east_texture_path))
		return (error(INVALID_FILE, game));
	return (1);
}

t_texture	*choose_texture(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
	{
		if (ray->raydirx < 0)
			return (&game->west_texture);
		else
			return (&game->east_texture);
	}
	else
	{
		if (ray->raydiry < 0)
			return (&game->north_texture);
		else
			return (&game->south_texture);
	}
}
