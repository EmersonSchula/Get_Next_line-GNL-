/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <<marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:46:03 by eschula           #+#    #+#             */
/*   Updated: 2024/11/19 16:22:40 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

void	limpa(char **lixo)
{
	if (*lixo)
	{
		free(*lixo);
		*lixo = NULL;
	}
}

char	*ler_paragrafo(int fd, char *temp)
{
	char	*buffer;
	char	*temp2;
	ssize_t	bytes;

	if (!temp)
		temp = ft_strdup("");	
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(temp, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (NULL);
		else if (bytes == 0)
		{
			break;
		}
		buffer[bytes] = '\0';
		temp2 = ft_strjoin(temp, buffer);
		if (!temp2 || !*temp2)
			return (NULL);
		limpa(&temp);
		temp = temp2;
	}
	limpa(&buffer);
	return (temp);
}

char	*dividir_linha(char *temp, char *memoria)
{
	int		i;
	char	*buffer;

	if (!temp || !temp[0])
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	buffer = ft_calloc((i + 2), sizeof(char));
	if (!buffer)
	{
		limpa(&buffer);
		return (NULL);
	}
	i = 0;
	while (temp[i] && temp[i] != '\n')
	{
		buffer[i] = temp[i];
		i++;
	}
	if (temp[i] == '\n')
	{
		buffer[i] = '\n';
		i++;
	}
	buffer[i] = '\0';
	temp = ft_strdup(buffer);
	limpa(&buffer);
	temp[i] = '\0';
	memoria = &temp[i + 1];
	
	return (temp);
}

// static char	*proxima_linha(char *temp)
// {
// 	int		i;
// 	int		j;
// 	char	*nova_linha;

// 	i = 0;
// 	while (temp[i] && temp[i] != '\n')
// 		i++;
// 	nova_linha = ft_calloc((ft_strlen(temp) - i + 1), sizeof(char));
// 	if (!nova_linha)
// 		return (NULL);
// 	i++;
// 	j = 0;
// 	while (temp[i])
// 		nova_linha[j++] = temp[i++];
// 	nova_linha[j] = '\0';
// 	temp = ft_strdup(nova_linha);
// 	limpa(&nova_linha);
// 	return (temp);
// }

char	*get_next_line(int fd)
{
	static char	*memoria;
	char		*linha;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!memoria)
		memoria = ft_calloc(1, 1);
	temp = memoria;
	temp = ler_paragrafo(fd, temp);
	if (!temp)
		return (NULL);
	linha = memoria;
	linha = dividir_linha(temp, memoria);
	if (!memoria)
	{
		limpa(&memoria);
		limpa(&temp);
		return (NULL);
	}
	limpa(&temp);
	return (linha);
}
