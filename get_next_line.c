/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:02:45 by eschula           #+#    #+#             */
/*   Updated: 2024/11/04 14:22:59 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> // Para testes com arquivos

// Função principal para ler a próxima linha do arquivo
char *get_next_line(int fd) {
    static char *buffer;
    char temp[BUFFER_SIZE + 1];
    ssize_t bytes_read;
    char *line;
    char *newline_pos;

    if (fd < 0 || BUFFER_SIZE <= 0) {
        return NULL;
    }

    // Inicializa o buffer, se necessário
    if (!buffer) {
        buffer = ft_calloc(1, sizeof(char));
    }

    // Ler do arquivo até encontrar uma nova linha ou até que não haja mais dados
    while ((bytes_read = read(fd, temp, BUFFER_SIZE)) > 0) {
        temp[bytes_read] = '\0';
        buffer = ft_strjoin(buffer, temp);
        if ((newline_pos = ft_strchr(buffer, '\n'))) {
            break; // Sai do loop se uma nova linha for encontrada
        }
    }

    if (bytes_read <= 0 && (!buffer || !*buffer)) {
        free(buffer); // Libera o buffer se não há mais dados
        buffer = NULL;
        return NULL;
    }

    // Extrai a linha até o caractere de nova linha
    newline_pos = ft_strchr(buffer, '\n');
    if (newline_pos) {
        *newline_pos = '\0'; // Termina a linha antes da nova linha
        line = ft_strdup(buffer); // Duplicata a linha
        char *temp_buffer = ft_strdup(newline_pos + 1); // Aloca e copia o restante do buffer
        free(buffer); // Libera o buffer original
        buffer = temp_buffer; // Atualiza o buffer
    } else {
        line = ft_strdup(buffer); // Se não houver nova linha, duplica todo o buffer
        free(buffer); // Libera o buffer original
        buffer = NULL; // Reseta o buffer
    }

    return line; // Retorna a linha lida
}
