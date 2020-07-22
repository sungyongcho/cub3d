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
int    draw_line_bres(t_window *window)
{
	int len = window->player-> px + 20;
    int x = window->player->px;
    int y = window->player->py;
    int p;

    p = 2 * window->player->pdx - window->player->pdy;

    while (x <= len)
    {
        mlx_pixel_put(window->mlx, window->win, x, y, 0xFFFFFF);
        x++;
        if (p < 0)
            p = p + 2 * window->player->pdy;
        else
        {
            p = p + 2 * window->player->pdx + 2 * window->player->pdy;
            y++;
        }
    }
}
