/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hitran <hitran@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 22:40:08 by hitran            #+#    #+#             */
/*   Updated: 2024/05/08 12:25:08 by hitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*data[OPEN_MAX];
	char		*line;

	if ((fd < 0) || (BUFFER_SIZE <= 0) || (fd > OPEN_MAX))
		return (NULL);
	data[fd] = ft_read(fd, data[fd]);
	if (!data[fd])
		return (NULL);
	line = ft_line(data[fd]);
	if (!line)
		return (ft_free(&data[fd]));
	data[fd] = ft_next(data[fd]);
	return (line);
}

char	*ft_read(int fd, char *data)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&data));
	bytes = 1;
	while ((data && !ft_strchr(data, '\n') && bytes > 0) || !data)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (ft_free(&data));
		}
		if (!bytes)
			break ;
		buffer[bytes] = '\0';
		data = ft_strjoin(data, buffer);
	}
	free(buffer);
	return (data);
}

char	*ft_line(char *data)
{
	int		i;
	char	*line;

	i = 0;
	if (!data[i])
		return (NULL);
	while (data[i] && (data[i] != '\n'))
		i++;
	if (data[i] == '\n')
		i++;
	line = ft_substr(data, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_next(char *data)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	while (data[i] && (data[i] != '\n'))
		++i;
	if (!data[i])
	{
		free(data);
		return (NULL);
	}
	rest = malloc(sizeof(char) * (ft_strlen(data) - i + 1));
	if (!rest)
	{
		free(data);
		return (NULL);
	}
	++i;
	j = 0;
	while (data[i])
		rest[j++] = data[i++];
	rest[j] = '\0';
	free(data);
	return (rest);
}
