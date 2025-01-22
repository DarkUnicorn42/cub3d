#include "../include/cub3d.h"

void	init_player(t_player *player)
{
	player->x = WIDTH / 2;
	player->y = HEIGHT / 2;
	player->angle = PI / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		close_game(game);
		exit(0);
	}
	if(keycode == W)
		game->player.key_up = true;
	if(keycode == S)
		game->player.key_down = true;
	if(keycode == A)
		game->player.key_left = true;
	if(keycode == D)
		game->player.key_right = true;
	if(keycode == LEFT)
		game->player.left_rotate = true;
	if(keycode == RIGHT)
		game->player.right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if(keycode == W)
		player->key_up = false;
	if(keycode == S)
		player->key_down = false;
	if(keycode == A)
		player->key_left = false;
	if(keycode == D)
		player->key_right = false;
	if(keycode == LEFT)
		player->left_rotate = false;
	if(keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void move_player(t_player *player, t_game *game)
{
    int speed = 3;
    float angle_speed = 0.03;

    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;

    float new_x = player->x;
    float new_y = player->y;

    if (player->key_up)
    {
        new_x += cos_angle * speed;
        new_y += sin_angle * speed;
    }
    if (player->key_down)
    {
        new_x -= cos_angle * speed;
        new_y -= sin_angle * speed;
    }
    if (player->key_left)
    {
        new_x += sin_angle * speed;
        new_y -= cos_angle * speed;
    }
    if (player->key_right)
    {
        new_x -= sin_angle * speed;
        new_y += cos_angle * speed;
    }

    // Check for wall collisions before updating position
    if (!touch(new_x, player->y, game))
        player->x = new_x;
    if (!touch(player->x, new_y, game))
        player->y = new_y;
}
