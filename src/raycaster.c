/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:59:33 by mwojtcza          #+#    #+#             */
/*   Updated: 2025/02/15 13:08:50 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	perform_dda(t_ray *ray, t_game *game)
{
	ray->hit = 0;
	while (!ray->hit)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (game->map[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
	}
}

float	compute_corrected_dist(t_ray *ray, t_player *player, float ray_angle)
{
	float	perpwalldist;
	float	distance_in_pixels;
	float	angle_diff;

	if (ray->side == 0)
	{
		perpwalldist = (ray->mapx - (player->x / BLOCK)
				+ (1 - ray->stepx) / 2.0f) / ray->raydirx;
	}
	else
	{
		perpwalldist = (ray->mapy - (player->y / BLOCK)
				+ (1 - ray->stepy) / 2.0f) / ray->raydiry;
	}
	distance_in_pixels = perpwalldist * BLOCK;
	angle_diff = ray_angle - player->angle;
	distance_in_pixels *= cosf(angle_diff);
	return (distance_in_pixels);
}

void	draw_column(t_game *game, t_tex *texture, int column, t_line *line)
{
	float	step;
	float	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = (float)texture->height / (float)line->wall_height;
	tex_pos = (line->start_y - HEIGHT / 2 + line->wall_height / 2) * step;
	y = line->start_y;
	while (y < line->end_y)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		color = *(int *)(texture->data + (tex_y * texture->size_line
					+ line->texture_x * (texture->bpp / 8)));
		put_pixel(column, y, color, game);
		tex_pos += step;
		y++;
	}
}

void	calc_line(t_player *player, t_ray *ray, t_tex *tex, t_line *line)
{
	float	wall_x;

	line->wall_height = (int)(BLOCK * HEIGHT / line->distance);
	line->start_y = (HEIGHT - line->wall_height) / 2;
	line->end_y = line->start_y + line->wall_height;
	if (line->start_y < 0)
		line->start_y = 0;
	if (line->end_y >= HEIGHT)
		line->end_y = HEIGHT - 1;
	if (ray->side == 0)
		wall_x = (player->y / BLOCK) + ((line->distance / BLOCK)
				* ray->raydiry);
	else
		wall_x = (player->x / BLOCK) + ((line->distance / BLOCK)
				* ray->raydirx);
	wall_x = wall_x - floor(wall_x);
	line->texture_x = (int)(wall_x * tex->width);
	if (line->texture_x < 0)
		line->texture_x = 0;
	if (line->texture_x >= tex->width)
		line->texture_x = tex->width - 1;
}

void	draw_line(t_player *player, t_game *game, float ray_angle, int column)
{
	t_ray		ray;
	t_line		line;
	t_tex		*texture;

	init_ray(&ray, player, ray_angle);
	calc_delta_dist(&ray);
	init_sidedist_step(&ray, player);
	perform_dda(&ray, game);
	texture = choose_texture(&ray, game);
	if (!texture || !texture->data)
		return ;
	line.distance = compute_corrected_dist(&ray, player, ray_angle);
	calc_line(player, &ray, texture, &line);
	draw_column(game, texture, column, &line);
}
