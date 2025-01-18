#include "../include/cub3d.h"

void	init_ray(t_ray *ray, t_player *player, float ray_angle)
{
	ray->raydirx = cosf(ray_angle);
	ray->raydiry = sinf(ray_angle);

	ray->mapx = (int)(player->x / BLOCK);
	ray->mapy = (int)(player->y / BLOCK);
}

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
	/*
	** perform_dda:
	**  - Steps through the grid in increments of 1 tile, either in X or Y,
	**    until we hit a wall ('1').
	**  - Sets ray->side = 0 if we moved in X (vertical boundary),
	**    or 1 if we moved in Y (horizontal boundary).
	*/
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
		perpwalldist = (ray->mapx - (player->x / BLOCK) + (1 - ray->stepx) / 2.0f) / ray->raydirx;
	}
	else
	{
		perpwalldist = (ray->mapy - (player->y / BLOCK) + (1 - ray->stepy) / 2.0f) / ray->raydiry;
	}
	distance_in_pixels = perpwalldist * BLOCK;

	// Fisheye correction
	angle_diff = ray_angle - player->angle;
	distance_in_pixels *= cosf(angle_diff);

	return (distance_in_pixels);
}

void	draw_column(t_game *game, t_texture *texture,
				int column, t_line *line)
{
	int	y;
	int	d;
	int	color;
	int	height;

	height = line->end_y - line->start_y;
	y = line->start_y;
	while (y < line->end_y)
	{
		d = (y - line->start_y) * texture->height / height;
		color = *(int *)(texture->data
			+ (d * texture->size_line + line->texture_x * (texture->bpp / 8)));
		put_pixel(column, y, color, game);
		y++;
	}
}

void	draw_line(t_player *player, t_game *game, float ray_angle, int column)
{
	t_ray		ray;
	t_line		line;
	t_texture	*texture;

	init_ray(&ray, player, ray_angle);
	calc_delta_dist(&ray);
	init_sidedist_step(&ray, player);
	perform_dda(&ray, game);

	// Compute distance
	line.distance = compute_corrected_dist(&ray, player, ray_angle);

	// Pick the texture
	texture = choose_texture(&ray, game);
	if (!texture || !texture->data)
		return ;

	// Compute wall height / startY / endY
	line.wall_height = (BLOCK / line.distance) * (WIDTH / 2.0f);
	line.start_y = (HEIGHT - line.wall_height) / 2;
	line.end_y = line.start_y + line.wall_height;
	if (line.start_y < 0)
		line.start_y = 0;
	if (line.end_y >= HEIGHT)
		line.end_y = HEIGHT - 1;

	// Compute intersection point
	line.hit_x = player->x + ray.raydirx * line.distance;
	line.hit_y = player->y + ray.raydiry * line.distance;

	// Figure out local offset in the tile
	if (ray.side == 0)
		line.wall_hit = fmodf(line.hit_y, BLOCK);
	else
		line.wall_hit = fmodf(line.hit_x, BLOCK);

	line.texture_x = (int)((line.wall_hit / (float)BLOCK) * texture->width);

	draw_column(game, texture, column, &line);
}
