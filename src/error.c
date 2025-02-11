#include "../include/cub3d.h"

int error(t_error code, t_game *game)
{
	if (code == NO_FILE)
	{
		printf("please provide a file you pookie\n");
	}
	else
	{
		if (game && game->mlx)
		{
			close_game(game);
		}
		if (code == INVALID_FILE)
		{
			printf("invalid file\n");
		}
		else if (code == INVALID_SPAWN)
		{
			printf("invalid spawn point\n");
		}
		else if (code == INVALID_MAP)
		{
			free_map(game->map);
			free_map(game->copy_map);
			printf("invalid map - make sure that it's enclosed in walls\n");
		}
	}
	return (0);
}
