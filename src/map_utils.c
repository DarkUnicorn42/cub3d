/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:25:51 by zogorzeb          #+#    #+#             */
/*   Updated: 2025/02/15 12:26:02 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*tex_path_creator(char *line)
{
	int		i;
	int		len;
	char	*path;

	i = 2;
	while (line[i] == ' ')
		i++;
	path = ft_substr(line, i, ft_strlen(line) - i);
	if (!path)
		return (NULL);
	len = ft_strlen(path);
	while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == ' '))
	{
		path[len - 1] = '\0';
		len--;
	}
	return (path);
}

int	texture_identifier(int code, char *line, t_game *game)
{
	char	*path;

	path = tex_path_creator(line);
	path_counter(code, game);
	if (!path)
		return (0);
	if (code == 1)
		game->north_texture_path = path;
	else if (code == 2)
		game->south_texture_path = path;
	else if (code == 3)
		game->west_texture_path = path;
	else if (code == 4)
		game->east_texture_path = path;
	return (1);
}

int	line_check(char *line, t_game *data)
{
	if (!ft_strncmp(line, "NO", 2))
		return (texture_identifier(1, line, data));
	else if (!ft_strncmp(line, "SO", 2))
		return (texture_identifier(2, line, data));
	else if (!ft_strncmp(line, "WE", 2))
		return (texture_identifier(3, line, data));
	else if (!ft_strncmp(line, "EA", 2))
		return (texture_identifier(4, line, data));
	else if (!ft_strncmp(line, "F ", 2))
	{
		data->floor_color = parse_color(line + 2);
		return (1);
	}
	else if (!ft_strncmp(line, "C ", 2))
	{
		data->ceiling_color = parse_color(line + 2);
		return (1);
	}
	else if (!ft_strcmp(line, "\n"))
		return (0);
	else
		return (1);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
