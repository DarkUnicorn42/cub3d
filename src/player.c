/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 11:52:18 by mwojtcza          #+#    #+#             */
/*   Updated: 2025/02/15 12:10:41 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		close_game(game);
		exit(0);
	}
	if (keycode == W)
		game->player.key_up = true;
	if (keycode == S)
		game->player.key_down = true;
	if (keycode == A)
		game->player.key_left = true;
	if (keycode == D)
		game->player.key_right = true;
	if (keycode == LEFT)
		game->player.left_rotate = true;
	if (keycode == RIGHT)
		game->player.right_rotate = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = false;
	if (keycode == S)
		player->key_down = false;
	if (keycode == A)
		player->key_left = false;
	if (keycode == D)
		player->key_right = false;
	if (keycode == LEFT)
		player->left_rotate = false;
	if (keycode == RIGHT)
		player->right_rotate = false;
	return (0);
}

void	rotate_player(t_player *player)
{
	float	angle_speed;	

	angle_speed = 0.03;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

void	calc_new_pos(t_player *player, int *new_x, int *new_y, int speed)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	if (player->key_up)
	{
		*new_x += cos_angle * speed;
		*new_y += sin_angle * speed;
	}
	if (player->key_down)
	{
		*new_x -= cos_angle * speed;
		*new_y -= sin_angle * speed;
	}
	if (player->key_left)
	{
		*new_x += sin_angle * speed;
		*new_y -= cos_angle * speed;
	}
	if (player->key_right)
	{
		*new_x -= sin_angle * speed;
		*new_y += cos_angle * speed;
	}
}

void	move_player(t_player *player, t_game *game)
{
	int	speed;
	int	new_x;
	int	new_y;

	new_x = player->x;
	new_y = player->y;
	speed = 3;
	calc_new_pos(player, &new_x, &new_y, speed);
	if (!touch(new_x, player->y, game))
		player->x = new_x;
	if (!touch(player->x, new_y, game))
		player->y = new_y;
}
