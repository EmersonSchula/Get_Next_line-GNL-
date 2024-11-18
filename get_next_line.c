/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:46:03 by eschula           #+#    #+#             */
/*   Updated: 2024/11/15 23:20:49 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

void	limpa(char *lixo)
{
	size_t	i;

	i = ft_strlen(lixo);
	while (i > 0)
	{
		lixo[i - 1] = '\0';
		i--;
	}
	free(lixo);
	lixo = NULL;
}

char	*ler_paragrafo(int fd, char *temp)
{
	char	*buffer;
	ssize_t	bytes;

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
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(temp, buffer);
		if (!temp || !*temp)
			return (NULL);
	}
	limpa(buffer);
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
	linha = ft_calloc((i + 2), sizeof(char));
	if (!linha)
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
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
		return (NULL);
	nova_linha = ft_calloc((ft_strlen(linha) - i + 1), sizeof(char));
	if (!nova_linha)
		return (NULL);
	i++;
	j = 0;
	while (linha[i])
		nova_linha[j++] = linha[i++];
	nova_linha[j] = '\0';
	limpa(linha);
	linha = ft_strdup(nova_linha);
	limpa(nova_linha);
	return (linha);
}

char	*get_next_line(int fd)
{
	static char	*memoria;
	char		*linha;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = ft_strdup(memoria);
	if (!temp)
		return (NULL);
	temp = ler_paragrafo(fd, temp);
	if (!temp)
		return (NULL);
	linha = "";
	linha = dividir_linha(temp, linha);
	if (!linha)
	{
		limpa(linha);
		limpa(temp);
		return (NULL);
	}
	temp = proxima_linha(temp);
	if (!memoria)
		memoria = ft_calloc(ft_strlen(temp), sizeof(char));
	if (!memoria)
		limpa(memoria);
	memoria = ft_strdup(temp);
	limpa(temp);
	return (linha);
}
