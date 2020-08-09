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

int		draw_player(t_window *window, int color)
{
	t_point	*begin;
	t_point	*end;

	if (!(begin = (t_point *)malloc(sizeof(t_point))))
		return (0);
	if (!(end = (t_point *)malloc(sizeof(t_point))))
		return (0);

	begin->x = window->player->center->x;
	begin->y = window->player->center->y;
	end->x = window->player->center->x + window->player->pdx;
	end->y = window->player->center->y + window->player->pdy;
	draw_line_bres(window, begin, end, color);
	free(begin);
	free(end);
	return (1);
}

int		draw_line_bres_low(t_window *window, t_point *begin, t_point *end, int color)
{
	int	dx;
	int	dy;
	int	yi;
	int	p;

	dx = end->x - begin->x;
	dy = end->y - begin->y;
    yi = 1;
    if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
    p = 2*dy - dx;
	while (begin->x <= end->x)
	{
		mlx_pixel_put(window->mlx, window->win, begin->x, begin->y, color);
		if (p > 0)
		{
			begin->y = begin->y + yi;
			p = p - 2*dx;
		}
		p = p + 2*dy;
		begin->x++;
	}
	return (1);
}

int		draw_line_bres_hi(t_window *window, t_point *begin, t_point *end, int color)
{
	int	dx;
	int	dy;
	int	xi;
	int	p;

	dx = end->x - begin->x;
	dy = end->y - begin->y;
    xi = 1;
    if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
    p = 2*dx - dy;
	while (begin->y <= end->y)
	{
		mlx_pixel_put(window->mlx, window->win, begin->x, begin->y, color);
		if (p > 0)
		{
			begin->x = begin->x + xi;
			p = p - 2*dy;
		}
		p = p + 2*dx;
		begin->y++;
	}
	return (1);
}
int		draw_line_bres(t_window *window, t_point *begin, t_point *end, int color)
{
	int dx;
	int dy;

	dx = ((end->x - begin->x) > 0) ? (end->x - begin->x) : -(end->x - begin->x);
	dy = ((end->y - begin->y) > 0) ? (end->y - begin->y) : -(end->y - begin->y);

	if (dy < dx)
	{
		if (begin->x > end->x)
			draw_line_bres_low(window, end, begin, color);
		else
			draw_line_bres_low(window, begin, end, color);
	}
	else
	{
		if (begin->y > end->y)
			draw_line_bres_hi(window, end, begin, color);
		else
			draw_line_bres_hi(window, begin, end, color);
	}
	return (1);
}
