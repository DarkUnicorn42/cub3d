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
	for (int i = 0; i < size; i++)
		{
	for (int j = 0; j < size; j++)
		{
		put_pixel(x + i, y + j, color, game);
}
    }
}

void draw_map(t_game *game)
{
    int		y;
	int		x;
	char	**map = game->map;
	int		color = 0x0000FF;

	y = 0;
	x = 0;
	map = game->map;
	color = 0x0000FF;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if(map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
			x++;
		}
		y++;
	}
}

void clear_image(t_game *game)
{
	for(int y = 0; y < HEIGHT; y++)
		for(int x = 0; x < WIDTH; x++)
			put_pixel(x, y, 0, game);
}

// bool touch(float px, float py, t_game *game)
// {
//     int x = (int)(px / BLOCK);
//     int y = (int)(py / BLOCK);

//     // Check if the position is in bounds
//     if (y < 0 || y >= HEIGHT / BLOCK || x < 0 || x >= WIDTH / BLOCK)
//         return true; // Out of bounds

//     if (game->map[y][x] == '1')
//         return true; // Wall collision
//     return false;
// }

bool touch(float px, float py, t_game *game)
{
    int x0 = (int)((px - COLLISION_RADIUS) / BLOCK);
    int x1 = (int)((px + COLLISION_RADIUS) / BLOCK);
    int y0 = (int)((py - COLLISION_RADIUS) / BLOCK);
    int y1 = (int)((py + COLLISION_RADIUS) / BLOCK);

    for (int mapY = y0; mapY <= y1; mapY++)
    {
        for (int mapX = x0; mapX <= x1; mapX++)
        {
            // if (mapY < 0 || mapY >= HEIGHT / BLOCK ||
            //     mapX < 0 || mapX >= WIDTH / BLOCK)
			if (mapY < 0 || game->map[mapY] == NULL || mapX < 0 || game->map[mapY][mapX] == '\0')
            {
                return (true);
            }
            if (game->map[mapY][mapX] == '1')
                return (true);
        }
    }
    return (false);
}

void draw_floor_ceiling(t_game *game)
{
    int		x;
	int		y;

    for (y = 0; y < HEIGHT / 2; y++)
    {
        for (x = 0; x < WIDTH; x++)
            put_pixel(x, y, game->ceiling_color, game);
    }
    for (; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
            put_pixel(x, y, game->floor_color, game);
    }
}
