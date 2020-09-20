/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_rest.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:21:08 by sucho             #+#    #+#             */
/*   Updated: 2020/09/21 03:47:35 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	floor_ceiling_to_buffer(t_window *window, int x)
{
	int	y;

	y = 0;
	while (y < window->cub->res_h / 2)
	{
		window->buffer[y][x] = window->cub->ceiling_color;
		y++;
	}
	y = window->cub->res_h / 2;
	while (y < window->cub->res_h)
	{
		window->buffer[y][x] = window->cub->floor_color;
		y++;
	}
}

void	sortSprites(t_window *window)
{
	int	i;
	int	j;
	int	max;
	t_sprite temp;
	i = 0;
	while (i < window->cub->sprite_count)
	{
		window->sprite[i].distance =
			((window->posX - window->sprite[i].x) \
			* (window->posX - window->sprite[i].x) \
			+ (window->posY - window->sprite[i].y) \
			* (window->posY - window->sprite[i].y));
		i++;
	}
	i = 0;
	max = 0;
	while (i < window->cub->sprite_count - 1)
	{
		j = i + 1;
		while (j < window->cub->sprite_count)
		{
			if (window->sprite[j].distance > window->sprite[i].distance)
				max = j;
			j++;
		}
		if (i != max)
		{
			temp = window->sprite[i];
			window->sprite[i] = window->sprite[max];
			window->sprite[max] = temp;
		}
		i++;
	}
}
