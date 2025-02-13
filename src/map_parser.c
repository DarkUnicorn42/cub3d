/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:20:12 by zogorzeb          #+#    #+#             */
/*   Updated: 2025/02/13 18:23:30 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	first_or_last_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	elements_checker(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (!ft_strchr(" 01NSEW", line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (!elements_checker(map[i]))
			return (0);
		if (i == 0 || map[i + 1] == NULL)
		{
			if (!first_or_last_line(map[i]))
				return (0);
		}
		else
		{
			if (!adjacent_to_whitespace(map, i))
				return (0);
		}
		if (!surrounded_by_walls(map, i))
			return (0);
		change_space_to_wall(map, i);
		i++;
	}
	return (1);
}

int	create_map(char *line, t_game *data)
{
	char	*next;

	while (1)
	{
		next = get_next_line(data->fd);
		if (!next)
			break ;
		line = ft_strjoin_gnl(line, next);
		free(next);
	}
	data->map = ft_split(line, '\n');
	data->copy_map = ft_split(line, '\n');
	close(data->fd);
	free(line);
	return (1);
}

void	path_counter(int code, t_game *data)
{
	char	*path;

	if (code == 1)
	{
		data->n_path++;
		path = data->north_texture_path;
	}
	else if (code == 2)
	{
		data->s_path++;
		path = data->south_texture_path;
	}
	else if (code == 3)
	{
		data->w_path++;
		path = data->west_texture_path;
	}
	else if (code == 4)
	{
		data->e_path++;
		path = data->east_texture_path;
	}
	if (data->n_path > 1 || data->s_path > 1
		|| data->w_path > 1 || data->e_path > 1)
		free(path);
}
