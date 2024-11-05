/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:03:23 by eschula           #+#    #+#             */
/*   Updated: 2024/11/04 19:55:31 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 42

char    *get_next_line(int fd);
char    *ft_strjoin(char *s1, char *s2);
char    *ft_substr(char const *s, unsigned int start, size_t len);
size_t  ft_strlen(const char *s);
char    *ft_strdup(const char *s1);
void    *ft_calloc(size_t count, size_t size);
char    *ft_strchr(const char *s, int c);
void    *ft_memset(void *ptr, int value, size_t num);

#endif
