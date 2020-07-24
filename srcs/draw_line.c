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
	int x_0;
	int y_0;
	int x_1;
	int y_1;

	x_0 = window->player->px;
	y_0 = window->player->py;
	x_1 = window->player->px + window->player->pdx;
	y_1 = window->player->py + window->player->pdy;
	if (draw_line_bres(x_0, y_0, x_1, y_1) != 1)
		return (0);
	return (1);
}
int		draw_line_bres(int x_0, int y_0, int x_1, int y_1)
{
	int dx;
	int dy;

	if (dy < dx)
	{
		if ( < 0)
			draw_line_bres_low(x_1, y_1, x_0, y_0);
		else
			draw_line_bres_low(x_0, y_0, x_1, y_1);
	}
	else
	{
		if ( <0)
			draw_line_bres_hi(x_1, y_1, x_0, y_0);
		else
			draw_line_bres_hi(x_1, y_1, x_0, y_0);
	}
	return (1);
}

int		draw_line_bres_low(t_window *window, int x_0, int y_0,
							int dx, int dy)
{
	int	yi;
	int x;
	int	y;
	int	p;

    yi = 1;
    if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
    p = 2*dy - dx;
	y = y_0;
	while(x = x_0 <= (x_0 +dx))
	{
		mlx_pixel_put(window->mlx, window->win, x, y,0x00FFFF);
		if (p > 0)
		{
			y = y + yi;
			p = p - 2*dx;
		}
		p = p + 2*dy;
		x++;
	}
}

int		draw_line_bres_high(t_window *window, int x_0, int y_0,
							int dx, int dy)
{
	int	xi;
	int x;
	int	y;
	int	p;

    xi = 1;
    if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
    p = 2*dx - dy;
	x = x_0;
	while(y = y_0 <= (y_0 +dy))
	{
		mlx_pixel_put(window->mlx, window->win, x, y,0x00FFFF);
		if (p > 0)
		{
			x = x + xi;
			p = p - 2*dy;
		}
		p = p + 2*dx;
		y++;
	}
}
