/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:28:22 by eschula           #+#    #+#             */
/*   Updated: 2024/11/08 13:41:02 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
char *get_next_line(int fd)
{
	static char *buffer;
	char temp[BUFFER_SIZE + 1];
	ssize_t bytes_read;
	char *line;
	char *newline_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}

	if (!buffer)
	{
		buffer = ft_calloc(1, sizeof(char));
	}

	while ((bytes_read = read(fd, temp, BUFFER_SIZE)) > 0)
	{
		temp[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if ((newline_pos = ft_strchr(buffer, '\n')))
		{
			break;
		}
	}

	if (bytes_read <= 0 && (!buffer || !*buffer))
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
		char *temp_buffer = ft_strdup(newline_pos + 1);
		free(buffer);
		buffer = temp_buffer;
		line = ft_strdup(buffer);
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
