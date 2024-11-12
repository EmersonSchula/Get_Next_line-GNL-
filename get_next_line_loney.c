/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_loney.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <<marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:02:45 by eschula           #+#    #+#             */
/*   Updated: 2024/11/11 16:59:39 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	return (NULL);
}

static char	*read_and_store(int fd, char *buffer)
{
	char	temp[BUFFER_SIZE + 1];
	ssize_t	bytes;

	bytes = read(fd, temp, BUFFER_SIZE);
	if (buffer == NULL)
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (NULL);
	}
	while (bytes > 0)
	{
		temp[bytes] = '\0';
		buffer = ft_strjoin(buffer, temp);
		if (!buffer)
		{
			free(buffer);
			return (NULL);
		}
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes = read(fd, temp, BUFFER_SIZE);
	}
	return (buffer);
}

static char	*extract_line(char *buffer)
{
	static char	*newline;
	char		*line;

	newline = ft_strchr(buffer, '\n');
	if (newline)
	{
		*newline = '\0';
		line = ft_strdup(buffer);
		if (!line)
			return (NULL);
	}
	else
	{
		line = ft_strdup(buffer);
		if (!line)
			return (NULL);
	}
	return (line);
}

static char	*update_buffer(char *buffer)
{
	char	*newline;
	char	*new_buffer;

	newline = ft_strchr(buffer, '\n');
	if (newline)
	{
		new_buffer = ft_strdup(newline + 1);
		if (!new_buffer)
		{
			free(buffer);
			return (NULL);
		}
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
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = update_buffer(buffer);
	return (line);
}
