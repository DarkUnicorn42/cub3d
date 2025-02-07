/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:56:51 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/12/25 14:54:01 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*ft_strdup_gnl(char *str1 )
{
	char	*str2;
	int		length;
	size_t	i;

	i = 0;
	length = ft_strlen_gnl(str1);
	str2 = malloc(sizeof(char) * (length + 1));
	if (!(str2))
		return (0);
	while (str1[i] != '\0')
	{
		if (str1[i] == ' ')
			str2[i] = '1';
		else
			str2[i] = str1[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}

char	*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char	*substring;
	int		i;

	i = 0;
	if (!s || !len)
		return (NULL);
	if (len > ft_strlen_gnl(s))
		len = ft_strlen_gnl(s);
	if (ft_strlen_gnl(s) <= (size_t)start)
		return (ft_strdup_gnl(""));
	if (ft_strlen_gnl(s) <= len + (size_t)start)
		len = ft_strlen_gnl(s) - start;
	substring = (char *)malloc((len + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	while (len-- > 0)
		substring[i++] = s[start++];
	substring[i] = '\0';
	return (substring);
}

char	*ft_strjoin_gnl(char *buffer, char *new_s)
{
	int		i;
	int		j;
	char	*string;
	int		length;

	length = 0;
	i = 0;
	j = 0;
	if (!buffer || !new_s)
		return (NULL);
	length = ft_strlen_gnl(buffer) + ft_strlen_gnl(new_s);
	string = (char *)malloc((sizeof(char) * (length + 1)));
	if (!string)
		return (NULL);
	while (buffer[i] != '\0')
		string[j++] = buffer[i++];
	i = 0;
	while (new_s[i] != '\0')
		string[j++] = new_s[i++];
	string[j] = '\0';
	if (buffer)
		free(buffer);
	buffer = NULL;
	return (string);
}

size_t	ft_strlen_gnl(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *str, int c)
{
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
		i++;
	}
	if (c == '\0')
		return ((char *)str + i);
	return (NULL);
}
