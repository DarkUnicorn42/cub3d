#include "../include/cub3d.h"

int load_texture(t_game *game, t_texture *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
    if (!texture->img)
        return (0); // Failed to load texture
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

void free_texture_paths(t_game *game)
{
    free(game->north_texture_path);
    free(game->south_texture_path);
    free(game->west_texture_path);
    free(game->east_texture_path);
}
