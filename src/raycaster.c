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

void draw_line(t_player *player, t_game *game, float ray_angle, int column)
{
    t_ray ray;
    float distanceInPixels;
    float wall_height;
    int start_y, end_y;

	init_ray(&ray, player, ray_angle);

	// distance the ray travels to go from one x-grid to the next
	calc_delta_dist(&ray);

	// calculate the initial side distance and the step direction
	init_sidedist_step(&ray, player);

	/*
	** perform_dda:
	**  - Steps through the grid in increments of 1 tile, either in X or Y,
	**    until we hit a wall ('1').
	**  - Sets ray->side = 0 if we moved in X (vertical boundary),
	**    or 1 if we moved in Y (horizontal boundary).
	*/
	perform_dda(&ray, game);

	// Compute the distance to the wall
	distanceInPixels = compute_corrected_dist(&ray, player, ray_angle);

	// Choose the texture based on the side of the wall
	t_texture *texture = choose_texture(&ray, game);

    // Compute the wall slice height using corrected distance
    wall_height = (BLOCK / distanceInPixels) * (WIDTH / 2.0f);
    start_y = (HEIGHT - wall_height) / 2;
    end_y = start_y + wall_height;
    if (start_y < 0) start_y = 0;
    if (end_y >= HEIGHT) end_y = HEIGHT - 1;

    // Figure out texture X offset
    float hitX = player->x + ray.raydirx * (distanceInPixels);
    float hitY = player->y + ray.raydiry * (distanceInPixels);

    float wall_hit;
    if (ray.side == 0)
        wall_hit = fmodf(hitY, BLOCK);
    else
        wall_hit = fmodf(hitX, BLOCK);

    int texture_x = (int)((wall_hit / BLOCK) * texture->width);

    if (ray.side == 0 && ray.raydirx > 0)
        texture_x = texture->width - texture_x - 1;
    if (ray.side == 1 && ray.raydiry < 0)
        texture_x = texture->width - texture_x - 1;

    // Draw the wall slice
    for (int y = start_y; y < end_y; y++)
    {
        int d = (y - start_y) * texture->height / (end_y - start_y);
        int color = *(int *)(texture->data +
                     (d * texture->size_line + texture_x * (texture->bpp / 8)));
        put_pixel(column, y, color, game);
    }
}
