/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <<marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:10:11 by eschula           #+#    #+#             */
/*   Updated: 2024/11/07 16:47:59 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>  // Para open
#include <stdio.h>  // Para printf
#include <unistd.h> // Para close

int	main(void)
{
	char	*line;
	int		fd;

	fd = open("caminho_do_arquivo.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Erro ao abrir o arquivo");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}
