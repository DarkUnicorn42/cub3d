/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:07:03 by mwojtcza          #+#    #+#             */
/*   Updated: 2025/02/15 12:11:00 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	find_player_spawn(t_game *game, t_player *player)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (is_spawn_char(game->map[y][x]))
			{
				init_player_position(player, x, y, game->map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
	error(INVALID_SPAWN, game);
	exit(1);
}

bool	is_spawn_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	init_player_position(t_player *player, int x, int y, char spawn_char)
{
	player->x = (x + 0.5f) * BLOCK;
	player->y = (y + 0.5f) * BLOCK;
	if (spawn_char == 'N')
		player->angle = 3 * (PI / 2);
	else if (spawn_char == 'S')
		player->angle = PI / 2;
	else if (spawn_char == 'E')
		player->angle = 0;
	else if (spawn_char == 'W')
		player->angle = PI;
}
