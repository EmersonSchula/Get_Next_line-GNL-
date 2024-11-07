/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <<marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:02:45 by eschula           #+#    #+#             */
/*   Updated: 2024/11/07 19:53:50 by eschula          ###   ########.fr       */
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

static char	*read_and_store(int fd, char *buffe)
{
	char	temp[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	bytes_read = read(fd, temp, BUFFER_SIZE);
	if (buffe == NULL)
	{
		buffe = ft_strdup("");
		if (!buffe)
			return (NULL);
	}
	while (bytes_read > 0)
	{
		temp[bytes_read] = '\0';
		buffe = ft_strjoin(buffe, temp);
		if (!buffe)
		{
			free(buffe);
			return (NULL);
		}
		if (ft_strchr(buffe, '\n'))
			break ;
		bytes_read = read(fd, temp, BUFFER_SIZE);
	}
	return (buffe);
}

static char	*extract_line(char *buff)
{
	char	*newline_pos;
	char	*lin;

	newline_pos = ft_strchr(buff, '\n');
	if (newline_pos)
	{
		*newline_pos = '\0';
		lin = ft_strdup(buff);
		if (!lin)
        	return (NULL);
	}
	else
	{
		lin = ft_strdup(buff);
		if (!lin)
        	return (NULL);
	}
	return (lin);
}

static char	*update_buffer(char *buf)
{
	char	*newline_pos;
	char	*new_buffer;

	newline_pos = ft_strchr(buf, '\n');
	if (newline_pos)
	{
		new_buffer = ft_strdup(newline_pos + 1);
		if (!new_buffer)
		{
			free(buf);
			return (NULL);
		}
		//free(buf);
		return (new_buffer);
	}
	free(buf);
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