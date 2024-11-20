/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:46:03 by eschula           #+#    #+#             */
/*   Updated: 2024/11/20 16:04:21 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

static char	*clean(char **lixo)
{
	if (*lixo)
	{
		free(*lixo);
		*lixo = NULL;
	}
	return (NULL);
}

static char	*get_line(int fd, char *buffer, char *rest)
{
	ssize_t	bytes;
	char	*temp;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		if (!rest)
			rest = ft_strdup("");
		temp = rest;
		rest = ft_strjoin(temp, buffer);
		clean(&temp);
		if (ft_strchr(rest, '\n'))
			break ;
	}
	return (rest);
}

static char	*split_lines(char *line)
{
	int		index;
	char	*temp;
	
	index = 0;
	while (line[index] != '\n' && line[index] != '\0')
		index++;
	if (line[index] == '\n')
		index++;
	if (line[index] == '\0')
		return (NULL);
	temp = ft_strdup(line + index);
	line[index] = '\0';
	return (temp);	
}

char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	char		*buffer;
	char		*line;
	
	if (fd == -1 || BUFFER_SIZE <= 0)
		return(NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	line = get_line(fd, buffer, rest);
	clean(&buffer);
	if (!line)
		return (clean(&rest));
	rest = split_lines(line);
	return (line);
}