/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:28:22 by eschula           #+#    #+#             */
/*   Updated: 2024/11/08 15:18:33 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

static char	*read_and_store(int fd, char *buffer)
{
	char *line;
	static char *newline_pos;
	char temp[BUFFER_SIZE + 1];
	ssize_t bytes;
	
	while ((bytes = read(fd, temp, BUFFER_SIZE)) > 0)
	{
		temp[bytes] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if ((newline_pos = ft_strchr(buffer, '\n')))
		{
			break;
		}
	}

	if (bytes <= 0 && (!buffer || !*buffer))
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}

	newline_pos = ft_strchr(buffer, '\n');
	if (newline_pos)
	{
		*newline_pos = '\0';
		line = ft_strdup(buffer);
		buffer = ft_strdup(newline_pos + 1);
		// free(buffer);
		// if (!buffer)
		// 	buffer = temp_buffer;
		// buffer = ft_memcpy(buffer, temp_buffer, ft_strlen(temp_buffer));
		
		// line = ft_strdup(buffer);
		// free(buffer);
		// buffer = NULL;
	}
	return (line);
}

char *get_next_line(int fd)
{
	static char *buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}

	if (!buffer)
	{
		buffer = ft_calloc(1, sizeof(char));
	}
	buffer = read_and_store(fd, buffer);
	if (!buffer || !*buffer)
		return (NULL);
	return (buffer);
}
