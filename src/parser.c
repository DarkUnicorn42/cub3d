#include "../include/cub3d.h"

#include <stdlib.h>
#include <string.h>  // for strlen()

static void change_space_to_wall(char **map, int index)
{
	int		i;
	char	*new;
	char	*line;

	line = map[index]; // Get the current line
	if (!line) // Ensure line is valid
		return;

	// Allocate memory for the new modified line
	new = (char *)malloc(strlen(line) + 1);
	if (!new) // Check if malloc failed
		return;

	// Replace spaces and tabs with '1'
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')  // Use '\t' instead of '	'
			new[i] = '1';
		else
			new[i] = line[i];
		i++;
	}
	new[i] = '\0';

	// Free old line and update the map
	free(line);
	map[index] = new; // Assign the modified string back to the map
}

static bool	is_space_or_one(char back, char front, char up, char down)
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

static bool is_valid_space(char **map, int row, int col)
{
	char adj_back = '\0';
	char adj_front = '\0';
	char adj_up = '\0';
	char adj_down = '\0';

	// Ensure column is within bounds before accessing
	if (col > 0)
		adj_back = map[row][col - 1];
	if (map[row][col + 1] != '\0')  // Avoid reading out of bounds
		adj_front = map[row][col + 1];

	// Ensure row is within bounds before accessing
	if (row > 0 && map[row - 1])
		adj_up = map[row - 1][col];
	if (map[row + 1] && map[row + 1][col] != '\0')
		adj_down = map[row + 1][col];

	// Validate space rules
	if (map[row][col] == ' ')
	{
		if (!is_space_or_one(adj_back, adj_front, adj_up, adj_down))
			return (false);
	}
	return (true);
}



static int adjacent_to_whitespace(char **map, int row)
{
	int col;
	col = 0;
	while (map[row][col] == ' ' && map[row][col] != '\0')
		col++;
	// Ensure row exists
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


static int	 surrounded_by_walls(char **map, int row)
{
	int		col;

	col = 0;
	if (row == 0 || map[row + 1] == NULL)
		return (1);
	while (map[row][col] == ' ')
		col++;
	while (map[row][col])
	{
		if ((ft_strlen(map[row]) > ft_strlen(map[row - 1])) && ((size_t)col > ft_strlen(map[row - 1])))
		{
			if (map[row][col] != 1)
				return (0);
		}
		if ((ft_strlen(map[row]) > ft_strlen(map[row + 1])) && ((size_t)col > ft_strlen(map[row + 1])) && map[row][col] != '1')
		{
			if (map[row][col] != 1)
				return (0);
		}
		col++;
	}
	return (1);

}

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
		// if (line[i] )
		i++;
	}
	return (1);
}

int	 check_map(char **map)
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
		// printf("%s\n", map[i]);
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

int texture_identifier(int code, char *line, t_game *game)
{
    int i = 2; // Skip the identifier (e.g., "NO")
    while (line[i] == ' ')
        i++;

    char *path = ft_substr(line, i, ft_strlen(line) - i);
    if (!path)
        return (0);

    // Strip trailing newline or spaces in the texture path
    int len = ft_strlen(path);
    while (len > 0 && (path[len - 1] == '\n' || path[len - 1] == ' '))
    {
        path[len - 1] = '\0';
        len--;
    }
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

int	parse_color(char *str)
{
	char	**split;
	int		r, g, b;
	int		color;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		free_split(split);
		// handle error
		return (-1);
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_split(split);

	color = (r << 16) | (g << 8) | b;
	return (color);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
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

int parsing(t_game *data)
{
    char *line;
    int is_map_started = 0;

    while ((line = get_next_line(data->fd)) != NULL)
    {
        if (!is_map_started) // Process texture lines and skip empty lines
        {
            if (!ft_strcmp(line, "\n")) // Skip empty lines
            {
                free(line);
                continue;
            }
            if (!line_check(line, data)) // Process texture lines
            {
                free(line);
                return (0);
            }
            if (is_map_line(line)) // Map data starts
                is_map_started = 1;
        }
        if (is_map_started) // Create the map
        {
            create_map(line, data);
            break;
        }
        free(line);
    }
    if (!check_map(data->map)) // Validate the map
		return (0);
	find_player_spawn(data, &data->player); // Find the player spawn
    return (1);
}

