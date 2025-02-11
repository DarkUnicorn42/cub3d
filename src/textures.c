#include "../include/cub3d.h"

int load_texture(t_game *game, t_texture *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
    if (!texture->img)
        return (0);
    texture->data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
    return (1);
}

int load_all_textures(t_game *game)
{
    if (!load_texture(game, &game->north_texture, game->north_texture_path))
        return (error(INVALID_FILE));
    if (!load_texture(game, &game->south_texture, game->south_texture_path))
        return (error(INVALID_FILE));
    if (!load_texture(game, &game->west_texture, game->west_texture_path))
        return (error(INVALID_FILE));
    if (!load_texture(game, &game->east_texture, game->east_texture_path))
        return (error(INVALID_FILE));
    return (1);
}

void free_texture(t_game *game, t_texture *texture)
{
    if (texture->img)
        mlx_destroy_image(game->mlx, texture->img);
}

void free_all_textures(t_game *game)
{
    free_texture(game, &game->north_texture);
    free_texture(game, &game->south_texture);
    free_texture(game, &game->west_texture);
    free_texture(game, &game->east_texture);
}

void free_texture_paths(t_game *game)
{
    free(game->north_texture_path);
    free(game->south_texture_path);
    free(game->west_texture_path);
    free(game->east_texture_path);
}

t_texture	*choose_texture(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
	{
		if (ray->raydirx < 0)
			return (&game->west_texture);
		else
			return (&game->east_texture);
	}
	else
	{
		if (ray->raydiry < 0)
			return (&game->north_texture);
		else
			return (&game->south_texture);
	}
}