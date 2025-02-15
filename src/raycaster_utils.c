/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:15:02 by mwojtcza          #+#    #+#             */
/*   Updated: 2025/02/15 12:20:29 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	calc_delta_dist(t_ray *ray)
{
	if (ray->raydirx == 0)
		ray->deltadistx = 1e30f;
	else
		ray->deltadistx = fabsf(1.0f / ray->raydirx);
	if (ray->raydiry == 0)
		ray->deltadisty = 1e30f;
	else
		ray->deltadisty = fabsf(1.0f / ray->raydiry);
}

void	init_sidedist_step(t_ray *ray, t_player *player)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = ((player->x / BLOCK) - ray->mapx)
			* ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = ((ray->mapx + 1) - (player->x / BLOCK))
			* ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = ((player->y / BLOCK) - ray->mapy)
			* ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = ((ray->mapy + 1) - (player->y / BLOCK))
			* ray->deltadisty;
	}
}
