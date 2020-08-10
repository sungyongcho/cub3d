/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 07:03:47 by sucho             #+#    #+#             */
/*   Updated: 2020/08/10 18:41:42 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/cub3d.h"

char 	*read_map_oneline(const char *path)
{
	char *map;
	char *line;
	int	temp;
	int fd;

	fd = open(path,O_RDONLY);
	map = ft_strdup("");
	while (get_next_line(fd, &line)> 0)
	{
		map = ft_strjoin(map,line);
		map = ft_strjoin(map,"\n");
		free(line);
	}
	temp = 0;
	while (*(map + temp))
	{
		if (*(map+temp) == ' ')
			*(map+temp) = '1';
		temp++;
	}
	return (map);
}

int		map_check_row_num(char *map_oneline)
{
	int	output;

	output = 0;
	while (*map_oneline++)
	{
		if (*map_oneline == '\n')
			output++;
	}
	return (output);
}

int		map_check_col_num(char *map_oneline)
{
	int	output;
	int	max_num;
	output = 0;
	max_num = 0;
	while (*map_oneline++)
	{
		if (*map_oneline == '\n')
		{
			if (max_num > output)
				output = max_num - 1;
			max_num = 0;
		}
		max_num++;
	}
	return (output);
}

void	save_map(t_window *window, char *map_oneline, int row, int col)
{
	char	output[row][col];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < row)
	{
		while (j < col)
		{
			if (*map_oneline == '\n')
			{
				map_oneline++;
				continue ;
			}
			output[i][j] = *map_oneline++;
			j++;
		}
	}
}
void	map_convert_spaces(char **map, int row_num, int col_num)
{
	int	i;
	int	j;
	int	space_count;
	char *space;
	i = 0;

	while (map[i])
	{
		if (ft_strlen(map[i]) < col_num)
		{
			space_count = col_num - ft_strlen(map[i]);
			if (!(space = (char *)malloc(sizeof(char) * (space_count + 1))))
				return ;
			j = 0;
			while (j < space_count)
				*(space + j++) = '1';
			*(space + j)= '\0';
			map[i] = ft_strjoin(map[i],space);
		}
		i++;
	}
}

void	map_read(t_window *window, char *path)
{
	char	*map_oneline;

	map_oneline = read_map_oneline(path);
	window->row_count = map_check_row_num(map_oneline);
	printf("%d\n",window->row_count);
	window->column_count = map_check_col_num(map_oneline);
	window->map = ft_split(map_oneline, '\n');
	map_convert_spaces(window->map, window->row_count, window->column_count);
	int i =0;
	while (window->map[i])
		printf("%s\n",window->map[i++]);
}
