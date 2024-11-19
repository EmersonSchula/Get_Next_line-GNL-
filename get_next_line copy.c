/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <<marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:46:03 by eschula           #+#    #+#             */
/*   Updated: 2024/11/19 20:04:11 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

static void	limpa(char **lixo)
{
	if (*lixo)
	{
		free(*lixo);
		*lixo = NULL;
	}
}

static char	*get_next(int fd, char *buffer, char *rest)
{
	ssize_t	bytes;
	char	*temp;

	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE + 1);
		if (bytes == -1)
		{
			return (NULL);
		}
		if (bytes == 0)
		{
			break ;
		}
		buffer[bytes] = '\0';
		if (rest)
		{
			dup
		}
		
		temp = rest;
		temp = ft_strjoin(rest, buffer);
		rest = temp;
		free(temp)
		if (ft_strchr(temp, '\n'))
		{
			break ;
		}
		
	
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	char		*buffer;
	char		*line;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return(NULL);
	}
	if (!buffer)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	}
	line = ft_strdup(buffer);
	line = get_next(fd, buffer, line);
	
	return (line);
}