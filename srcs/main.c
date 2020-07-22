/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 02:31:03 by sucho             #+#    #+#             */
/*   Updated: 2020/07/22 06:33:56 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#define PI 3.1415926535

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		init_player(t_window *window, int a, int b)
{
	if (!(window->player = (t_player *)malloc(sizeof(t_player) + 1)))
		return (0);
	window->player->px = a;
	window->player->py = b;
	window->player->pa = 0;
	window->player->pdx = window->player->px + cos(window->player->pa) *5;
	window->player->pdy = window->player->py + sin(window->player->pa) *5;
}

void	init_window_and_grid_num(t_window *window, int a, int b, int c)
{
	window->width = a;
	window->height = b;
	window->grid_count = c;
}


void		move_dot_left(t_window *window)
{
	window->player->pa -= 0.1;
	if (window->player->pa < 0)
		window->player->pa += 2 * PI;
	window->player->pdx = window->player->px - cos(window->player->pa) * 5;
	window->player->pdy = window->player->py - sin(window->player->pa) * 5;
}

void		move_dot_right(t_window *window)
{
	window->player->pa += 0.1;
	if (window->player->pa > 2 * PI)
		window->player->pa -= 2 * PI;
	window->player->pdx = window->player->px +cos(window->player->pa) * 5;
	window->player->pdy = window->player->py + sin(window->player->pa) * 5;
}

void		move_dot_up(t_window *window)
{
	--window->player->py;
}

void		move_dot_down(t_window *window)
{
	++window->player->py;
}

int		draw_grid(t_window *window)
{
	int	draw_position;
	int	i;

	i = 1;
	while (i< window->grid_count)
	{
		draw_position = 0;
		while (draw_position <= window->width){
			mlx_pixel_put(window->mlx, window->win, draw_position, i * (window->height / window->grid_count),0xFFFFFF);
			draw_position++;
		}
		i++;
	}
	i = 1;
	while (i< window->grid_count)
	{
		draw_position = 0;
		while (draw_position <= window->width){
			mlx_pixel_put(window->mlx, window->win, i * (window->width/ window->grid_count), draw_position,0xFFFFFF);
			draw_position++;
		}
		i++;
	}
	return (0);
}

int		press_key_for_dot(int key, t_window *window)
{
	printf("key: %d\n",key);
	if (key == KEY_A)
		move_dot_left(window);
	else if (key == KEY_D)
		move_dot_right(window);
	else if (key == KEY_W)
		move_dot_up(window);
	else if (key == KEY_S)
		move_dot_down(window);
	return (0);
}

//int		release_key_for_dot(int key, t_window *window)
//{
	//return (0);
//}

int	main()
{
	t_window	*window;

	if (!(window = (t_window *)malloc(sizeof(t_window) + 1)))
		return (0);
	window->mlx = mlx_init();
	init_window_and_grid_num(window, 500, 500, 10);
	window->win = mlx_new_window(window->mlx, window->width, window->height, "ASTROWORLD IS WEAK come to suchoworld");
	init_player(window, 250, 250);
	mlx_pixel_put(window->mlx,window->win, window->player->px, window->player->py,0xFFFF00);
	mlx_loop_hook(window->mlx, draw_grid, window);
	mlx_loop_hook(window->mlx, draw_line_bres, window);
	mlx_hook(window->win, 2, 1, press_key_for_dot, window);
	//mlx_hook(window->win, 3, 2, release_key_for_dot, window);
	mlx_loop(window->mlx);
}
