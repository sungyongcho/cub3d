/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 15:27:36 by sucho             #+#    #+#             */
/*   Updated: 2020/09/10 01: 9:23by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

int		map_count_end_space(char *s)
{
	int	i;
	int	output;

	i = ft_strlen(s) - 1;
	output = 0;
	while (i != 0)
	{
		if (ft_strchr("NEWS012", s[i]))
			return(output);
		output++;
		i--;
	}
	return (output);
}

void	cub_parse_map(t_cub *cub, char **line, int line_count)
{
	int	i;
	int	end_space_count;

	if (!(cub->map =(char **)malloc(sizeof(char *) * line_count)))
		return ;
	i = 0;
	while (line[i])
	{
		end_space_count = (int)ft_strlen(line[i]) - map_count_end_space(line[i]) + 1;
		if (!(cub->map[i] = (char *)malloc(sizeof(char) * (end_space_count + 1))))
			return ;
		ft_strlcpy(cub->map[i], line[i], end_space_count);
		i++;
	}
}


void	cub_set_player(t_window *window, char pos, int i, int j)
{
	window->posX = i + 0.5;
	window->posY = j + 0.5;
	if (pos == 'N')
	{
		window->dirX = -1;
		window->dirY = 0;
		window->planeX = 0;
		window->planeY = 0.66;
	}
	if (pos == 'E')
	{
		window->dirX = 0;
		window->dirY = -1;
		window->planeX = -0.66;
		window->planeY = 0;
	}
	if (pos == 'W')
	{
		window->dirX = 0;
		window->dirY = 1;
		window->planeX = 0.66;
		window->planeY = 0;
	}
	if (pos == 'S')
	{
		window->dirX = 1;
		window->dirY = 0;
		window->planeX = 0;
		window->planeY = -0.66;
	}
}

void	cub_map_checkout(t_window *window)
{
	int		i;
	int		j;

	i = 0;
	while (i < window->cub->map_row)
	{
		j = 0;
		while (window->cub->map[i][j])
		{
			if (ft_strchr("NEWS", (char) window->cub->map[i][j]))
			{
				cub_set_player(window, (char) window->cub->map[i][j], i, j);
				window->cub->map[i][j] = '0';
			}
			if (window->cub->map[i][j] == '2')
				window->cub->sprite_count++;
			j++;
		}
		i++;
	}
}

void	cub_save_sprite(t_window *window)
{
	int		i;
	int		j;
	int		sprite_count;

	if (!(window->sprite = (t_sprite *)malloc(sizeof(t_sprite) * window->cub->sprite_count)))
		return ;
	sprite_count = 0;
	i = 0;
	while (i < window->cub->map_row)
	{
		j = 0;
		while (window->cub->map[i][j])
		{
			if (window->cub->map[i][j] == '2')
			{
				window->sprite[sprite_count].x = i;
				window->sprite[sprite_count].y = j;
				window->cub->map[i][j] = '0';
				sprite_count++;
			}
			j++;
		}
		i++;
	}
}
