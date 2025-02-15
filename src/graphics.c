/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:49:04 by mwojtcza          #+#    #+#             */
/*   Updated: 2025/02/15 11:20:25 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int color, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < BLOCK)
	{
		j = 0;
		while (j < BLOCK)
		{
			put_pixel(x + i, y + j, color, game);
			j++;
		}
		i++;
	}
}

void	draw_sq_mm(int x, int y, int color, t_game *game)
{
	int	i;
	int	j;
	int	block_size;

	block_size = 8;
	x *= block_size;
	y *= block_size;
	i = 0;
	while (i < block_size)
	{
		j = 0;
		while (j < block_size)
		{
			put_pixel(x + i, y + j, color, game);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int		y;
	int		x;
	int		color;
	char	**map;


	y = 0;
	x = 0;
	map = game->map;
	color = 0x0000FF;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, color, game);
			x++;
		}
		y++;
	}
}

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

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
