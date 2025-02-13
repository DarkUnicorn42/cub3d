/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:13:29 by zogorzeb          #+#    #+#             */
/*   Updated: 2025/02/13 18:28:07 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	change_space_to_wall(char **map, int index)
{
	int		i;
	char	*new;
	char	*line;

	line = map[index];
	if (!line)
		return ;
	new = (char *)malloc(ft_strlen(line) + 1);
	if (!new)
		return ;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			new[i] = '1';
		else
			new[i] = line[i];
		i++;
	}
	new[i] = '\0';
	free(line);
	map[index] = new;
}

bool	is_space_or_one(char back, char front, char up, char down)
{
	if (back != '1' && back != ' ')
		return (false);
	if (front != '1' && front != ' ')
		return (false);
	if (up != '1' && up != ' ')
		return (false);
	if (down != '1' && down != ' ')
		return (false);
	return (true);
}

bool	is_valid_space(char **map, int row, int col)
{
	char	adj_back;
	char	adj_front;
	char	adj_up;
	char	adj_down;

	adj_back = '\0';
	adj_front = '\0';
	adj_up = '\0';
	adj_down = '\0';
	if (col > 0)
		adj_back = map[row][col - 1];
	if (map[row][col + 1] != '\0')
		adj_front = map[row][col + 1];
	if (row > 0 && map[row - 1])
		adj_up = map[row - 1][col];
	if (map[row + 1] && map[row + 1][col] != '\0')
		adj_down = map[row + 1][col];
	if (map[row][col] == ' ')
	{
		if (!is_space_or_one(adj_back, adj_front, adj_up, adj_down))
			return (false);
	}
	return (true);
}

int	adjacent_to_whitespace(char **map, int row)
{
	int	col;

	col = 0;
	while (map[row][col] == ' ' && map[row][col] != '\0')
		col++;
	while (map[row][col] != '\0')
	{
		if (map[row][col] == ' ')
		{
			if (!is_valid_space(map, row, col))
				return (0);
		}
		col++;
	}
	return (1);
}

int	surrounded_by_walls(char **map, int row)
{
	int		col;

	col = 0;
	if (row == 0 || map[row + 1] == NULL)
		return (1);
	while (map[row][col] == ' ')
		col++;
	while (map[row][col])
	{
		if ((ft_strlen(map[row]) > ft_strlen(map[row - 1]))
			&& ((size_t)col > ft_strlen(map[row - 1])))
		{
			if (map[row][col] != '1')
				return (0);
		}
		if ((ft_strlen(map[row]) > ft_strlen(map[row + 1]))
			&& ((size_t)col > ft_strlen(map[row + 1])) && map[row][col] != '1')
		{
			if (map[row][col] != '1')
				return (0);
		}
		col++;
	}
	return (1);
}
