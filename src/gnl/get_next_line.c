/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:55:50 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/12/25 14:53:27 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*ft_newline(char **buffer)
{
	char	*newline;
	char	*temp;
	int		i;

	i = 0;
	if (!*buffer)
		return (NULL);
	temp = *buffer;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	newline = ft_substr_gnl(temp, 0, i);
	*buffer = ft_substr_gnl(temp, i, ft_strlen_gnl(temp) - i);
	if (temp)
		free(temp);
	temp = NULL;
	return (newline);
}

static char	*write_to_buffer(char *buffer, int fd)
{
	int		read_bytes;
	char	*new;

	new = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer || !new)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr_gnl(buffer, '\n'))
	{
		read_bytes = read(fd, new, BUFFER_SIZE);
		if (read_bytes == 0)
			break ;
		if (read_bytes == -1)
		{
			free(new);
			free(buffer);
			return (NULL);
		}
		new[read_bytes] = '\0';
		buffer = ft_strjoin_gnl(buffer, new);
	}
	if (new)
		free(new);
	new = NULL;
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*newline;

	newline = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), buffer = NULL, NULL);
	if (!buffer)
	{
		buffer = (char *)malloc(sizeof(char) * 1);
		buffer[0] = '\0';
	}
	buffer = write_to_buffer(buffer, fd);
	newline = ft_newline(&buffer);
	return (newline);
}
