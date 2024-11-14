/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <<marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:46:03 by eschula           #+#    #+#             */
/*   Updated: 2024/11/14 19:59:45 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

char	*ler_paragrafo(int fd, char *temp)
{
	char	*buffer;
	ssize_t	quantos_bytes;
	
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	quantos_bytes = 1;
	while (!ft_strchr(temp, '\n') && quantos_bytes > 0)
	{
		quantos_bytes = read(fd, buffer, BUFFER_SIZE);
		if (quantos_bytes == -1)
		{//
			return (NULL);
		}//
		else if (quantos_bytes == 0)
		{//
			break;
		}//
		buffer[quantos_bytes] = '\0';
		temp = ft_strjoin(temp, buffer);
		if (!temp || !*temp)
			return (NULL);
	}
	free(buffer);
	buffer = NULL;
	return (temp);
}

char	*dividir_linha(char *temp, char *linha)
{
	int		i;

	if (!temp || !temp[0])
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	// free(linha);
	// linha = NULL;
	linha = malloc((i + 2) * sizeof(char));
	if (!linha)
		return (NULL);
	i = 0;
	while(temp[i] && temp[i] != '\n')
	{
		linha[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
	{
		linha[i] = '\n';
		i++;
	}
	linha[i] = '\0';
	return (linha);
}

char	*proxima_linha(char *linha)
{
	int		i;
	int		j;
	char	*nova_linha;

	i = 0;
	while (linha[i] && linha[i] != '\n')
		i++;
	if (!linha[i])
	{
		return (NULL);
	}
	nova_linha = malloc((ft_strlen(linha) - i + 1) * sizeof(char));
	if (!nova_linha)
		return (NULL);
	i++;
	j = 0;
	while (linha[i])
		nova_linha[j++] = linha[i++];
	nova_linha[j] = '\0';
	free(linha);
	linha = NULL;
	linha = ft_strdup(nova_linha);
	free(nova_linha);
	nova_linha = NULL;
	return (linha);
}

char	*get_next_line(int fd)
{
	static char	*memoria;
	char		*linha;
	char		*temp;

	if (!memoria)
		memoria = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = memoria;
	temp = ler_paragrafo(fd, temp);
	linha = ft_strdup(temp);
	// free(memoria);
	// memoria = NULL;
	memoria = proxima_linha(linha);
	linha = dividir_linha(temp, linha);
	// free(temp);
	return (linha);
}
