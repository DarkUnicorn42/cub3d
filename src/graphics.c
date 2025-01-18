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

// // distance calculation functions
// float distance(float x, float y)
// {
//     return sqrt(x * x + y * y);
// }

// float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
// {
//     float delta_x = x2 - x1;
//     float delta_y = y2 - y1;
//     float angle = atan2(delta_y, delta_x) - game->player.angle;
//     float fix_dist = distance(delta_x, delta_y) * cos(angle);
//     return fix_dist;
// }
