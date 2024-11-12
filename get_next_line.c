/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <<marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:46:03 by eschula           #+#    #+#             */
/*   Updated: 2024/11/11 21:28:48 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*read_to_buffer(int fd, char *buffer)
{
	char	temp[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		temp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (!buffer || !*buffer)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (buffer);
}

char	*extract_line(char **buffer)
{
	char	*line;
	char	*newline_pos;
	char	*temp_buffer;

	if (!buffer || !*buffer)
		return (NULL);
	newline_pos = ft_strchr(*buffer, '\n');
	if (newline_pos)
	{
		*newline_pos = '\0';
		line = ft_strdup(*buffer);
		temp_buffer = ft_strdup(newline_pos + 1);
		if (!temp_buffer)
			return (free(line), NULL);
		free(*buffer);
		*buffer = temp_buffer;
	}
	else
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_to_buffer(fd, buffer);
	if (!buffer || !*buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	ret = extract_line(&buffer);
	if (ret == NULL)
	{
		free (buffer);
		buffer = NULL;
	}
	return (ret);
}
