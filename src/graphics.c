#include "../include/cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;

	int index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_game *game)
{
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y, color, game);
	for(int i = 0; i < size; i++)
		put_pixel(x, y + i, color, game);
	for(int i = 0; i < size; i++)
		put_pixel(x + size, y + i, color, game);
	for(int i = 0; i < size; i++)
		put_pixel(x + i, y + size, color, game);
}

void draw_map(t_game *game)
{
	char	**map = game->map;
	int		color = 0x0000FF;
	for(int y = 0; map[y]; y++)
		for(int x = 0; map[y][x]; x++)
			if(map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
}

void clear_image(t_game *game)
{
	for(int y = 0; y < HEIGHT; y++)
		for(int x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0, game);
}

bool touch(float px, float py, t_game *game)
{
    int x = (int)(px / BLOCK);
    int y = (int)(py / BLOCK);

    // Check if the position is in bounds
    if (y < 0 || y >= HEIGHT / BLOCK || x < 0 || x >= WIDTH / BLOCK)
        return true; // Out of bounds

    if (game->map[y][x] == '1')
        return true; // Wall collision
    return false;
}

// distance calculation functions
float distance(float x, float y)
{
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - game->player.angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}

void draw_line(t_player *player, t_game *game, float ray_angle, int column)
{
    t_ray ray;
    ray.angle = ray_angle;
    ray.ray_x = player->x;
    ray.ray_y = player->y;

    float cos_angle = cos(ray.angle);
    float sin_angle = sin(ray.angle);

    while (!touch(ray.ray_x, ray.ray_y, game))
    {
        ray.ray_x += cos_angle;
        ray.ray_y += sin_angle;
    }

    // Calculate distance and hit side
    ray.distance = fixed_dist(player->x, player->y, ray.ray_x, ray.ray_y, game);
    if (fabs(cos_angle) > fabs(sin_angle))
        ray.hit_side = 1;
    else
        ray.hit_side = 0;

    // Determine texture
    t_texture *texture = NULL;
    if (ray.hit_side == 1) // Vertical wall
    {
        if (cos_angle > 0)
            texture = &game->west_texture;
        else
            texture = &game->east_texture;
    }
    else // Horizontal wall
    {
        if (sin_angle > 0)
            texture = &game->north_texture;
        else
            texture = &game->south_texture;
    }

    // Calculate wall height
    float wall_height = (BLOCK / ray.distance) * (WIDTH / 2);
    int start_y = (HEIGHT - wall_height) / 2;
    int end_y = start_y + wall_height;

    // Determine texture X-coordinate
    float wall_hit;
    if (ray.hit_side == 1)
        wall_hit = fmod(ray.ray_y, BLOCK);
    else
        wall_hit = fmod(ray.ray_x, BLOCK);
    int texture_x = (wall_hit / BLOCK) * texture->width;

    // Draw the wall slice with the texture
    for (int y = start_y; y < end_y; y++)
    {
        int texture_y = ((y - start_y) * texture->height) / wall_height;
        int color = *(int *)(texture->data + (texture_y * texture->size_line + texture_x * (texture->bpp / 8)));
        put_pixel(column, y, color, game);
    }
}
