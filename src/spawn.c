#include "../include/cub3d.h"

void find_player_spawn(t_game *game, t_player *player)
{
    int y = 0;
    while (game->map[y])
    {
        int x = 0;
        while (game->map[y][x])
        {
            if (is_spawn_char(game->map[y][x])) // NSEW
            {
                init_player_position(player, x, y, game->map[y][x]);
                // Optionally replace the map char with '0' or something
                // so you don't treat that as a wall later
               // game->map[y][x] = '0';
                return;
            }
            x++;
        }
        y++;
    }
    // If we exit the loop, we found no spawn => error
    ft_putendl_fd("Error: No spawn point found!", 2);
    exit(1);
}

bool is_spawn_char(char c)
{
    return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void init_player_position(t_player *player, int x, int y, char spawn_char)
{
    // Center the player inside the tile
    player->x = (x + 0.5f) * BLOCK;
    player->y = (y + 0.5f) * BLOCK;

    // Set angle based on the spawn direction
    if (spawn_char == 'N')
        player->angle = 3 * (PI / 2);
    else if (spawn_char == 'S')
        player->angle = PI / 2;
    else if (spawn_char == 'E')
        player->angle = 0;
    else if (spawn_char == 'W')
        player->angle = PI;
}
