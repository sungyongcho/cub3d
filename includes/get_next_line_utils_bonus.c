/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 02:40:10 by sucho             #+#    #+#             */
/*   Updated: 2020/05/09 02:40:15 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t					ft_strlen(const char *s)
{
	size_t				i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

char					*ft_substr(char const *s,
						unsigned int start, size_t len)
{
	char				*result;
	size_t				s_size;
	size_t				i;
	size_t				j;

	if (!s)
		return (NULL);
	s_size = ft_strlen(s);
	if (start >= s_size)
		return (ft_strdup(""));
	if (!(result = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = start;
	j = 0;
	while (j < len && *(s + i) != '\0')
	{
		*(result + j) = *(s + i);
		j++;
		i++;
	}
	*(result + j) = '\0';
	return (result);
}

char					*ft_strjoin(char const *s1, char const *s2)
{
	char				*result;
	unsigned int		i;
	unsigned int		j;

	if (!s1 || !s2)
		return (ft_strdup(""));
	if (!(result = (char *)malloc(sizeof(char) *
	(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (*(s1 + i) != '\0')
	{
		*(result + i) = *(s1 + i);
		i++;
	}
	j = 0;
	while (*(s2 + j) != '\0')
	{
		*(result + i + j) = *(s2 + j);
		j++;
	}
	*(result + i + j) = '\0';
	return (result);
}

char					*ft_strdup(const char *s1)
{
	char				*result;
	size_t				len;
	size_t				i;

	len = ft_strlen(s1);
	if (!(result = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	if (result)
	{
		while (*(s1 + i) && i < len)
		{
			*(result + i) = *(s1 + i);
			i++;
		}
		*(result + i) = '\0';
	}
	else
		return (0);
	return (result);
}

char					*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (c == *s)
			return ((char *)s);
		s++;
	}
	if (!c && !*s)
		return ((char *)s);
	return (NULL);
}
