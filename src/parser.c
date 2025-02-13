/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:08:12 by zogorzeb          #+#    #+#             */
/*   Updated: 2025/02/13 19:22:50 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parse_color(char *str)
{
	char	**split;
	int		r;
	int		g;
	int		b;
	int		color;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		free_split(split);
		return (-1);
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_split(split);
	color = (r << 16) | (g << 8) | b;
	return (color);
}

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr("01NSEW ", line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	valid_data(t_game *data)
{
	if (data->n_path != 1 || data->s_path != 1
		|| data->w_path != 1 || data->e_path != 1)
		return (0);
	if (!check_map(data->map))
		return (0);
	find_player_spawn(data, &data->player);
	return (1);
}

int	line_redirection(char *line, int *is_map_started, t_game *data)
{
	if (!ft_strcmp(line, "\n"))
	{
		line = NULL;
		free(line);
		return (1);
	}
	if (!line_check(line, data))
	{
		free(line);
		return (0);
	}
	if (is_map_line(line))
		*is_map_started = 1;
	return (1);
}

int	parsing(t_game *data)
{
	char	*line;
	int		is_map_started;

	is_map_started = 0;
	while (1)
	{
		line = get_next_line(data->fd);
		if (!line)
			break ;
		if (!is_map_started)
		{
			if (!line_redirection(line, &is_map_started, data))
				return (0);
		}
		if (is_map_started)
		{
			create_map(line, data);
			break ;
		}
		if (line)
			free(line);
	}
	return (1);
}
