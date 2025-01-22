#include "../include/cub3d.h"

int	init_game(t_game *game, char *file)
{
	if (!validation(game, file))
		return (0);
	init_player(&game->player);
	game->fd = open(file, O_RDONLY);
	if (!parsing(game))
		return (error(INVALID_MAP));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	if (!load_all_textures(game))
        return (error(INVALID_FILE));
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (1);
}

int	close_game(t_game *game)
{
	free_texture_paths(game);
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (1);
}

int close_button(t_game *game)
{
    close_game(game);
    exit(0);
    return (0);
}

int draw_loop(t_game *game)
{
    t_player *player = &game->player;


	move_player(player, game);
    clear_image(game);
	draw_floor_ceiling(game);
    // Debug: Render the 2D map and player position
    if (DEBUG)
    {
        draw_square(player->x, player->y, 10, 0x00FF00, game);
        draw_map(game);
    }

    // Raycasting loop for each column
    float ray_angle = player->angle - (PI / 6); // Start angle
    float angle_increment = (PI / 3) / WIDTH;  // Field of view divided by screen width

    for (int column = 0; column < WIDTH; column++)
    {
        draw_line(player, game, ray_angle, column);
        ray_angle += angle_increment;
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return (0);
}

int	main(int argc, char **argv)
{
	t_game game;

	if (argc != 2)
		return (error(NO_FILE));
	if (!init_game(&game, argv[1]))
		return (0);
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, close_button, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);

	mlx_loop(game.mlx);

	return (0);
}
