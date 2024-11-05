/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:03:15 by eschula           #+#    #+#             */
/*   Updated: 2024/11/04 14:31:43 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stddef.h> // Para size_t


void *ft_memset(void *ptr, int value, size_t num) {
    unsigned char *p = ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

// Função para retornar o tamanho de uma string
size_t ft_strlen(const char *s) {
    size_t len = 0;
    while (s[len]) {
        len++;
    }
    return len;
}

// Função para duplicar uma string
char *ft_strdup(const char *s1) {
    char *dup;
    size_t len = ft_strlen(s1);

    dup = (char *)malloc(len + 1);
    if (!dup) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        dup[i] = s1[i];
    }
    dup[len] = '\0';
    return dup;
}

// Função para alocar memória
void *ft_calloc(size_t count, size_t size) {
    void *ptr = malloc(count * size);
    if (!ptr) {
        return NULL; // Retorna NULL se malloc falhar
    }
    ft_memset(ptr, 0, count * size); // Usa ft_memset em vez de memset
    return ptr;
}


// Função para extrair uma substring
char *ft_substr(char const *s, unsigned int start, size_t len) {
    if (!s || start >= ft_strlen(s)) {
        return ft_strdup("");
    }
    if (len > ft_strlen(s + start)) {
        len = ft_strlen(s + start);
    }
    char *substr = (char *)malloc(len + 1);
    if (!substr) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        substr[i] = s[start + i];
    }
    substr[len] = '\0';
    return substr;
}

// Função para concatenar duas strings
char *ft_strjoin(char *s1, char *s2) {
    if (!s1 && !s2) {
        return NULL;
    }
    char *joined;
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    
    joined = (char *)malloc(len1 + len2 + 1);
    if (!joined) {
        return NULL;
    }
    for (size_t i = 0; i < len1; i++) {
        joined[i] = s1[i];
    }
    for (size_t j = 0; j < len2; j++) {
        joined[len1 + j] = s2[j];
    }
    joined[len1 + len2] = '\0';
    free(s1); // Libera a memória de s1 se foi alocada
    return joined;
}

char *ft_strchr(const char *s, int c) {
    while (*s) {
        if (*s == (char)c) {
            return (char *)s; // Retorna o ponteiro para o caractere encontrado
        }
        s++;
    }
    return NULL; // Retorna NULL se o caractere não for encontrado
}
