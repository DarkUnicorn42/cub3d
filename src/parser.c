#include "../include/cub3d.h"

int	surrounded_by_walls(char **map, int i)
{
	if (i == 0)
	{
		if ((abs((int)ft_strlen(map[i]) - (int)ft_strlen(map[i + 1]))) >= 2)
			return (0);
	}
	else if (map[i + 1] == NULL)
	{
		if ((abs((int)ft_strlen(map[i]) - (int)ft_strlen(map[i - 1]))) >= 2)
			return (0);
	}
	else
	{
		if ((abs((int)ft_strlen(map[i]) - (int)ft_strlen(map[i - 1]))) >= 2)
			return (0);
		if ((abs((int)ft_strlen(map[i]) - (int)ft_strlen(map[i + 1]))) >= 2)
			return (0);
	}
	return (1);
}

int	first_or_last_line(char *line)
{
	int	i;

	i = 0;
	while(line[i])
	{
		if (line[i] != '1')
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
	if (line[0] != '1' || line[ft_strlen(line) - 1] != '1')
		return (0);
	while (line[i])
	{
		if (!ft_strchr("01NSEW", line[i]))
			return (0);
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
		if (!surrounded_by_walls(map, i))
			return (0);
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
	close(data->fd);
	free(line);
	return (1);
}
// int	texture_identifier(int code, char *line, t_game *data)
// {
// 	int	i;

// 	i = 2;
// 	while (line[i] == ' ')
// 		i++;
// 	if (code == 1)
// 		data->north_texture = ft_substr(line, i, ft_strlen(line) - i);
// 	else if (code == 2)
// 		data->south_texture = ft_substr(line, i, ft_strlen(line) - i);
// 	else if (code == 3)
// 		data->west_texture = ft_substr(line, i, ft_strlen(line) - i);
// 	else if (code == 4)
// 		data->east_texture = ft_substr(line, i, ft_strlen(line) - i);
// 	return (0);
// }
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
    // Assign the path to the correct texture in t_game
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
	else if (!ft_strcmp(line, "\n"))
		return (0);
	else
		return (1);
}
// changed the logic to create map after parsing texture paths
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

            if (ft_strchr(line, '1')) // Map data starts
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

    return (1);
}

