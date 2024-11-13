/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <<marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:46:03 by eschula           #+#    #+#             */
/*   Updated: 2024/11/13 20:24:56 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*leitura_paragrafo(int fd, char *leitura)
{
	char	*buffer;
	char	*temp;
	ssize_t	quantos_bytes;
	
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	quantos_bytes = 1;
	while (!ft_strchr(leitura, '\n') && quantos_bytes > 0)
	{
		quantos_bytes = read(fd, buffer, BUFFER_SIZE);
		if (quantos_bytes == -1)
		{
			return (NULL);
		}
		else if (quantos_bytes == 0)
		{
			break;
		}
		buffer[quantos_bytes] = '\0';
		temp = leitura;
		leitura = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (!leitura || !*leitura)
			return (NULL);
	}
	free(buffer);
	buffer = NULL;
	return (leitura);
}

char	*limpa_linha(char *stored)
{
	int		i;
	char	*line;

	if (!stored || !stored[0])
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while(stored[i] && stored[i] != '\n')
	{
		line[i] = stored[i];
		i++;
	}
	if (stored[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*proxima_linha(char *stored)
{
	int		i;
	int		j;
	char	*nova_linha;

	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
	{
		return (NULL);
	}
	nova_linha = malloc((ft_strlen(stored) - i + 1) * sizeof(char));
	if (!nova_linha)
		return (NULL);
	i++;
	j = 0;
	while (stored[i])
		nova_linha[j++] = stored[i++];
	nova_linha[j] = '\0';
	return (nova_linha);
}

char	*get_next_line(int fd)
{
	static char	*paragrafo;
	char		*linha;
	char		*temp;

	if (!paragrafo)
		paragrafo = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = paragrafo;
	paragrafo = leitura_paragrafo(fd, temp);
	if(!temp)
	{
		free(temp);
		temp = NULL;
	}
	if (!paragrafo || !*paragrafo)
	{
		free(paragrafo);
		paragrafo = NULL;
		return (NULL);
	}
	linha = limpa_linha(paragrafo);
	paragrafo = proxima_linha(paragrafo);
	if(!temp)
	{
		free(temp);
		temp = NULL;
	}
	if (!paragrafo || !*paragrafo)
	{
		free(paragrafo);
		paragrafo = NULL;
	}
	return (linha);
}
