/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:10:11 by eschula           #+#    #+#             */
/*   Updated: 2024/11/04 20:00:05 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>  // Para open
#include <stdio.h>  // Para printf
#include <unistd.h> // Para close

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s /home/emerson/Repositorios/get_next_line/caminho_do_arquivo.txt\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s\n", line);
        free(line); // Libera a memória alocada para a linha
    }

    close(fd); // Fecha o arquivo
    return 0;
}
