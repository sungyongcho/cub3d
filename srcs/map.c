/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 07:03:47 by sucho             #+#    #+#             */
/*   Updated: 2020/08/09 14:10:57 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/cub3d.h"

int	find_max_row(const char *map)
{
	int	count;

	count = 0;
	while (*map++)
	{
		if (*map =='\n')
			count++;
	}
	return (count);
}

int	find_max_col(const char *map)
{
	int	count;
	int max;

	if (!*map)
		return (0);
	max = 0;
	count = 0;
	count++;
	while (*map)
	{
		if (*map == '\n')
		{
			count--;
			if (max < count)
				max = count;
			count = 0;
		}
		count++;
		map++;
	}
	return (max);
}
char **read_map(const char *path)
{
	char **map;
	char *line;
	int fd = open(path,O_RDONLY);
	map = ft_strdup("");
	while (get_next_line(fd, &line)> 0)
	{
		*map++ = ft_strjoin(map,line);
		free(line);
	}
	return (map);
}
int main()
{
	char **map = read_map("srcs/map_test");
	printf("%s",map);
	printf("max row number: %d\n", find_max_row(map));
	printf("max col number: %d", find_max_col(map));
}
