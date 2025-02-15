/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:12:33 by mwojtcza          #+#    #+#             */
/*   Updated: 2025/02/15 12:12:52 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_texture(t_game *game, t_texture *texture)
{
	if (texture->img)
		mlx_destroy_image(game->mlx, texture->img);
}

void	free_all_textures(t_game *game)
{
	free_texture(game, &game->north_texture);
	free_texture(game, &game->south_texture);
	free_texture(game, &game->west_texture);
	free_texture(game, &game->east_texture);
}

void	free_texture_paths(t_game *game)
{
	if (game->north_texture_path)
		free(game->north_texture_path);
	if (game->south_texture_path)
		free(game->south_texture_path);
	if (game->west_texture_path)
		free(game->west_texture_path);
	if (game->east_texture_path)
		free(game->east_texture_path);
}
