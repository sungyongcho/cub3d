/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 02:32:29 by sucho             #+#    #+#             */
/*   Updated: 2020/07/22 05:5 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		draw_player(t_window *window)
{
	int x_1;
	int y_1;
	int x_0;
	int y_0;

	x_0 = window->player->px;
	y_0 = window->player->py;
	x_1 = window->player->px + window->player->pdx;
	y_1 = window->player->py + window->player->pdy;

	draw_line_bres(window, x_0, y_0, x_1, y_1);
	return (1);
}

int		draw_line_bres_low(t_window *window, int x_0, int y_0,
							int x_1, int y_1)
{
	int	dx;
	int	dy;
	int	yi;
	int	p;

	dx = x_1 - x_0;
	dy = y_1 - y_0;
    yi = 1;
    if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
    p = 2*dy - dx;
	while (x_0 <= x_1)
	{
		mlx_pixel_put(window->mlx, window->win, x_0, y_0,0x00FFFF);
		if (p > 0)
		{
			y_0 = y_0 + yi;
			p = p - 2*dx;
		}
		p = p + 2*dy;
		x_0++;
	}
	return (1);
}

int		draw_line_bres_hi(t_window *window, int x_0, int y_0,
							int x_1, int y_1)
{
	int	dx;
	int	dy;
	int	xi;
	int	p;

	dx = x_1 - x_0;
	dy = y_1 - y_0;
    xi = 1;
    if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
    p = 2*dx - dy;
	while (y_0 <= y_1)
	{
		mlx_pixel_put(window->mlx, window->win, x_0, y_0,0x00FFFF);
		if (p > 0)
		{
			x_0 = x_0 + xi;
			p = p - 2*dy;
		}
		p = p + 2*dx;
		y_0++;
	}
	return (1);
}
int		draw_line_bres(t_window *window, int x_0, int y_0, int x_1, int y_1)
{
	int dx;
	int dy;

	dx = ((x_1 - x_0) > 0) ? (x_1 - x_0) : -(x_1 - x_0);
	dy = ((y_1 - y_0) > 0) ? (y_1 - y_0) : -(y_1 - y_0);

	if (dy < dx)
	{
		if (x_0 > x_1)
			draw_line_bres_low(window, x_1, y_1, x_0, y_0);
		else
			draw_line_bres_low(window, x_0, y_0, x_1, y_1);
	}
	else
	{
		if (y_0 > y_1)
			draw_line_bres_hi(window, x_1, y_1, x_0, y_0);
		else
			draw_line_bres_hi(window, x_0, y_0, x_1, y_1);
	}
	return (1);
}
