/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bcp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <<marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:23:01 by eschula           #+#    #+#             */
/*   Updated: 2024/11/05 16:23:33 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static char	*read_and_store(int fd, char *buffer)
{
	char	temp[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = read(fd, temp, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		temp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, temp, BUFFER_SIZE);
	}
	return (buffer);
}

static char	*extract_line(char *buffer)
{
	char	*newline_pos;
	char	*line;

	newline_pos = ft_strchr(buffer, '\n');
	if (newline_pos)
	{
		*newline_pos = '\0';
		line = ft_strdup(buffer);
	}
	else
	{
		line = ft_strdup(buffer);
	}
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*newline_pos;
	char	*new_buffer;

	newline_pos = ft_strchr(buffer, '\n');
	if (newline_pos)
	{
		new_buffer = ft_strdup(newline_pos + 1);
		free(buffer);
		return (new_buffer);
	}
	free(buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_store(fd, buffer);
	if (!buffer || !*buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = update_buffer(buffer);
	return (line);
}
