#include "../include/cub3d.h"

int	validation(t_game *data, char *file)
{
	(void)data;

	if (!map_file_validation(file))
		return (error(INVALID_FILE));
	return (1);
}

int	map_file_validation(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	close (fd);
	// if *file == '.'
	// *file++;
	while (*file != '.' && *file)
		file++;
	if (*file && ft_strcmp(file, ".cub") == 0)
		return (1);
	else
		return (0);
	return (1);
}
