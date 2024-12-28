#include "../include/cub3d.h"

int	validation(t_game *data, char *file)
{
	if (!map_file_validation(file))
		return (error(1));
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
	while (*file != '.')
		file++;
	if (ft_strcmp(file, ".cub") == 0)
		return (1);
	else
		return (0);
	return (1);
}
