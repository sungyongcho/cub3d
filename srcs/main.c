/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 02:31:03 by sucho             #+#    #+#             */
/*   Updated: 2020/08/09 14:47:15 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int		init_player(t_window *window, int a, int b, int color)
{
	if (!(window->player = (t_player *)malloc(sizeof(t_player))))
		return (0);
	if (!(window->player->center = (t_point *)malloc(sizeof(t_point))))
		return (0);
	window->player->center->x = a;
	window->player->center->y = b;
	window->player->p_color = color;
	window->player->pa = 0;
	window->player->pdx = cos(window->player->pa) *30;
	window->player->pdy = sin(window->player->pa) *30;
	draw_player(window, window->player->p_color);
	return (1);
}

void	init_window_and_grid_num(t_window *window, int a, int b, int c, int d)
{
	window->width = a;
	window->height = b;
	window->row_count = c;
	window->column_count = d;
}


void		move_dot_right(t_window *window)
{
	draw_player(window, 000000);
	window->player->center->x += -window->player->pdy;
	window->player->center->y += window->player->pdx;
	draw_player(window, window->player->p_color);
}
void		move_dot_left(t_window *window)
{
	draw_player(window, 000000);
	window->player->center->x += window->player->pdy;
	window->player->center->y += -window->player->pdx;
	draw_player(window, window->player->p_color);
}
void		move_dot_left_arrow(t_window *window)
{
	draw_player(window, 000000);
	window->player->pa -= 0.1;
	if (window->player->pa < 0)
		window->player->pa += 2 * M_PI;
	window->player->pdx = cos(window->player->pa)*30;
	window->player->pdy = sin(window->player->pa)*30;
	draw_player(window, window->player->p_color);
}
void		move_dot_right_arrow(t_window *window)
{
	draw_player(window, 000000);
	window->player->pa += 0.1;
	if (window->player->pa > 2 * M_PI)
		window->player->pa = 0;
	window->player->pdx = cos(window->player->pa)*30;
	window->player->pdy = sin(window->player->pa)*30;
	draw_player(window, window->player->p_color);
}

void		move_dot_up(t_window *window)
{
	draw_player(window, 000000);
	window->player->center->x+=window->player->pdx;
	window->player->center->y+=window->player->pdy;
	draw_player(window, window->player->p_color);
}

void		move_dot_down(t_window *window)
{
	draw_player(window, 000000);
	window->player->center->x-=window->player->pdx;
	window->player->center->y-=window->player->pdy;
	draw_player(window, window->player->p_color);
}

int		draw_grid(t_window *window)
{
	int	draw_position;
	int	i;

	i = 1;
	while (i< window->row_count)
	{
		draw_position = 0;
		while (draw_position <= window->width){
			mlx_pixel_put(window->mlx, window->win, draw_position, i * (window->height / window->row_count),0x00FFFF);
			draw_position++;
		}
		i++;
	}
	i = 1;
	while (i< window->column_count)
	{
		draw_position = 0;
		while (draw_position <= window->width){
			mlx_pixel_put(window->mlx, window->win, i * (window->width/ window->column_count), draw_position,0x00FFFF);
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
	else if (key == KEY_LEFT_ARROW)
		move_dot_left_arrow(window);
	else if (key == KEY_RIGHT_ARROW)
		move_dot_right_arrow(window);
	return (0);
}

//int		release_key_for_dot(int key, t_window *window)
//{
	//return (0);
//}

void draw_box(t_window *window, int row_pos, int col_pos, int box_width, int box_height)
{
	t_point	box_begin;
	t_point	box_end;
	box_begin.x = box_width * col_pos;
	box_begin.y = box_height * row_pos;
	box_end.x = box_begin.x + box_width;
	box_end.y = box_begin.y + box_height;

	printf("beginx:%d\tbeginy:%d\t2x:%d\t2y:%d\n",box_begin.x, box_begin.y, box_end.x, box_end.y);
	int i;
	int j = box_begin.y;

	while (j< box_end.y)
	{
		i = box_begin.x;
		while(i <box_end.x)
		{
			mlx_pixel_put(window->mlx, window->win, i, j,0xFFFFFF);
			i++;
		}
		j++;
	}
}

void	draw_wall(t_window *window, char map[10][10])
{
	int r;
	int	c;

	r = 0;
	c = 0;
	int	box_width;
	int box_height;
	box_width = window->width / window->column_count;
	box_height = window->height/ window->row_count;
	while (r != 9)
	{
		if (map[r][c] == '0')
			c++;
		else if (map[r][c] == '1')
		{
			draw_box(window, r, c, box_width, box_height);
			c++;
		}
		if (c == 10)
		{
			r++;
			c = 0;
		}
	}

}

int	main()
{
	t_window	*window;
	char map_temp[10][10] = {{'1','0','0','0','1','0','0','0','0','0'},
			{'0','0','0','0','0','0','0','0','0','0'},
			{'0','0','1','0','0','0','0','1','0','0'},
			{'0','0','0','0','0','0','0','0','0','0'},
			{'0','0','0','0','0','0','0','0','0','0'},
			{'0','0','0','1','0','0','0','0','0','0'},
			{'0','0','0','0','1','0','0','0','0','0'},
			{'0','0','0','0','0','0','0','0','0','0'},
			{'0','0','1','0','0','0','0','1','0','0'},
			{'0','0','0','0','0','0','0','0','0','0'}};

	if (!(window = (t_window *)malloc(sizeof(t_window))))
		return (0);
	window->mlx = mlx_init();
	init_window_and_grid_num(window, 500, 500, 10, 10);
	window->win = mlx_new_window(window->mlx, window->width, window->height, "ASTROWORLD IS WEAK come to suchoworld");
	if (!init_player(window, 250, 250, 0x0000FF))
		return (0);
	draw_wall(window, map_temp);
	mlx_loop_hook(window->mlx, draw_grid, window);
	//mlx_loop_hook(window->mlx, draw_player, window);
	mlx_hook(window->win, 2, 1, press_key_for_dot, window);
	//mlx_hook(window->win, 3, 2, release_key_for_dot, window);
	mlx_loop(window->mlx);
}
