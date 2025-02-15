/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:26:46 by mwojtcza          #+#    #+#             */
/*   Updated: 2025/02/15 12:27:08 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	touch(float px, float py, t_game *game)
{
	int	x1;
	int	y1;
	int	mapx;
	int	mapy;

	x1 = (int)((px + COLLISION_RADIUS) / BLOCK);
	y1 = (int)((py + COLLISION_RADIUS) / BLOCK);
	mapy = (int)((py - COLLISION_RADIUS) / BLOCK);
	while (mapy <= y1)
	{
		mapx = (int)((px - COLLISION_RADIUS) / BLOCK);
		while (mapx <= x1)
		{
			if (mapy < 0 || game->map[mapy] == NULL || mapx < 0
				|| game->map[mapy][mapx] == '\0'
				|| game->map[mapy][mapx] == '1')
				return (true);
			mapx++;
		}
		mapy++;
	}
	return (false);
}

void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;	

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, game->ceiling_color, game);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, game->floor_color, game);
			x++;
		}
		y++;
	}
}
