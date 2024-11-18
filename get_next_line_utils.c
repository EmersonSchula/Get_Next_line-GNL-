/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschula <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:03:15 by eschula           #+#    #+#             */
/*   Updated: 2024/11/15 23:15:57 by eschula          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdint.h>

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

	if (!s1)
		s1 = "";
	len = ft_strlen(s1);
	dup = ft_calloc(len + 1, sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len && s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			total;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	if (count == 0 || size == 0)
		total = 1;
	else
		total = count * size;
	ptr = malloc(total * sizeof(char));
	if (!ptr)
	{
		free(ptr);
		return (NULL);
	}
	while (total)
		ptr[--total] = 0;
	return ((void *)ptr);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*dest;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	i = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
	{
		free(dest);
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0' && i < len)
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
