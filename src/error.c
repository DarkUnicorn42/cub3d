#include "../include/cub3d.h"

int	error(t_error code)
{
	if (code == NO_FILE)
		printf("please provide a file you pookie\n");
	if (code == INVALID_FILE)
	{
		printf("invalid file\n");
	}
	if (code == INVALID_SPAWN)
	{
		printf("invalid spawn point\n");
	}
	if (code == INVALID_MAP)
	{
		// clean up?
		printf("invalid map - make sure that it's enclosed in walls\n");
	}
	return (0);
}
