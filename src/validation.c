/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwojtcza <mwojtcza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 12:14:21 by mwojtcza          #+#    #+#             */
/*   Updated: 2025/02/15 12:19:49 by mwojtcza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validation(t_game *data, char *file)
{
	(void)data;
	if (!map_file_validation(file))
		return (error(INVALID_FILE, data));
	return (1);
}

int	map_file_validation(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	close (fd);
	while (*file != '.' && *file)
		file++;
	if (*file && ft_strcmp(file, ".cub") == 0)
		return (1);
	else
		return (0);
	return (1);
}
