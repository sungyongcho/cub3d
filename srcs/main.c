/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 02:31:03 by sucho             #+#    #+#             */
/*   Updated: 2020/09/02 19:08:45 by sucho            ###   ########.fr       */
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

int		init_player(t_window *window,int color)
{
	if (!(window->player = (t_player *)malloc(sizeof(t_player))))
		return (0);
	if (!(window->player->center = (t_point *)malloc(sizeof(t_point))))
		return (0);
	map_check_player(window);
	window->player->p_color = color;
	window->player->pdx = cos(window->player->pa) *30;
	window->player->pdy = sin(window->player->pa) *30;
	draw_player(window, window->player->p_color);
	return (1);
}

void	init_window(t_window *window, int a, int b)
{
	window->width = a;
	window->height = b;
}

int			is_moving_to_wall(t_point *center)
{
	if ((0 <= center->x && center->x <=50) &&
		(0 <= center->y && center->y <=50))
		return (0);
	return (1);
}

static void		move_dot_right(t_window *window)
{
	if ((0 <=window->player->center->x && window->player->center->x <= window->width)
	&& (0 <=window->player->center->y && window->player->center->y <= window->height))
	{
		draw_player(window, 000000);
		window->player->center->x += -window->player->pdy;
		window->player->center->y += window->player->pdx;
		draw_player(window, window->player->p_color);
		drawRay3D(window);
	}
}
static void		move_dot_left(t_window *window)
{
	if ((0 <=window->player->center->x && window->player->center->x <= window->width)
	&& (0 <=window->player->center->y && window->player->center->y <= window->height))
	{
		draw_player(window, 000000);
		window->player->center->x += window->player->pdy;
		window->player->center->y += -window->player->pdx;
		draw_player(window, window->player->p_color);
			drawRay3D(window);
	}
}
static void		move_dot_left_arrow(t_window *window)
{
	if ((0 <=window->player->center->x && window->player->center->x <= window->width)
	&& (0 <=window->player->center->y && window->player->center->y <= window->height))
	{
		draw_player(window, 000000);
		window->player->pa -= M_PI / 180 * 5;
		if (window->player->pa < 0)
			window->player->pa += 2 * M_PI;
		window->player->pdx = cos(window->player->pa)*30;
		window->player->pdy = sin(window->player->pa)*30;
		draw_player(window, window->player->p_color);
			drawRay3D(window);
	}
}
static void		move_dot_right_arrow(t_window *window)
{
	if ((0 <=window->player->center->x && window->player->center->x <= window->width)
	&& (0 <=window->player->center->y && window->player->center->y <= window->height))
	{
		draw_player(window, 000000);
		window->player->pa += M_PI / 180 * 5;
		if (window->player->pa > 2 * M_PI)
			window->player->pa = 0;
		window->player->pdx = cos(window->player->pa)*30;
		window->player->pdy = sin(window->player->pa)*30;
		draw_player(window, window->player->p_color);
			drawRay3D(window);
	}
}

static void		move_dot_up(t_window *window)
{
	if ((0 <=window->player->center->x && window->player->center->x <= window->width)
	&& (0 <=window->player->center->y && window->player->center->y <= window->height))
	{
		draw_player(window, 000000);
		window->player->center->x+=window->player->pdx;
		window->player->center->y+=window->player->pdy;
		draw_player(window, window->player->p_color);
			drawRay3D(window);
	}
}

static void		move_dot_down(t_window *window)
{
	if ((0 <=window->player->center->x && window->player->center->x <= window->width)
	&& (0 <=window->player->center->y && window->player->center->y <= window->height))
	{
		draw_player(window, 000000);
		window->player->center->x-=window->player->pdx;
		window->player->center->y-=window->player->pdy;
		draw_player(window, window->player->p_color);
			drawRay3D(window);
	}
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

void	draw_wall(t_window *window)
{
	int r;
	int	c;

	r = 0;
	c = 0;
	window->box_width = window->width / window->column_count;
	window->box_height = window->height/ window->row_count;
	while (r < window->row_count)
	{
		if (ft_strchr("NEWS 0", window->map[r][c]))
			c++;
		else if (window->map[r][c] == '1')
		{
			draw_box(window, r, c, window->box_width, window->box_height);
			c++;
		}
		if (c == window->column_count )
		{
			r++;
			c = 0;
		}
	}

}

float	ray_dist(t_point *center, float ray_x, float ray_y)
{
	return (sqrt((center->x - ray_x) * (center->x - ray_x) + (center->y - ray_y) * (center->y - ray_y)));
}

void	drawRay3D(t_window *window)
{
	t_point ray;
	t_point h_ray, v_ray;
	int	r, mx, my, mp, hit;
	float ra, rx, ry, xo, yo, aTan, distH, distV;
	ra = window->player->pa - (30 * M_PI/180);
	if (ra < 0)
		ra += 2*M_PI;
	if (ra > 2 *M_PI)
		ra -= 2*M_PI;
	r = 0;
	while (r < 1)
	{
		hit = 0;
		aTan = -1 / tan(ra);
		if (ra > M_PI && ((int) (ra / M_PI * 180)) != 180)
		{
			ray.y = window->player->center->y / window->box_height * window->box_height;
			ray.x = (window->player->center->y - ray.y) * aTan + window->player->center->x;
			yo = - window->box_height;
			xo = -yo * aTan;
		}
		else if (ra < M_PI && ((int) (ra / M_PI * 180)) != 0)
		{
			ray.y = window->player->center->y / window->box_height * window->box_height + window->box_height;
			ray.x = (window->player->center->y - ray.y) * aTan + window->player->center->x;
			yo = window->box_height;
			xo = -yo * aTan;
		}
		else if ( ((int) (ra / M_PI * 180)) == 180)
		{
			printf("##########hello########\n");
			ray.y = window->player->center->y;
			ray.x = window->player->center->x / window->box_width * window->box_width;
			yo = 0;
			xo = -window->box_width;
		}
		else if (((int) (ra / M_PI * 180)) == 0)
		{
			printf("##########bye########\n");
			ray.y = window->player->center->y;
			ray.x = window->player->center->x / window->box_width * window->box_width + window->box_width;
			yo = 0;
			xo = window->box_width;
		}
		while (!hit)
		{
			mx = (int)ray.x / window->box_width; my = (int)ray.y / window->box_height;
			mp = my * window->row_count + mx;
			printf("$$$mx: %d###\t###my: %d###\t###mp: %d$$$\t\n", mx,my,mp);
			if (0 < mp && mp < (window->row_count * window->column_count) && window->map[my][mx] == '1')
			{
				hit = 1;
				ray.y-=yo;
				ray.x-=xo;
				h_ray.x = ray.x;
				h_ray.y = ray.y;
				distH = ray_dist(window->player->center, h_ray.x, h_ray.y);
				printf("bitchmx: %d\tmy: %dbitch\n", mx,my);
				printf("bitchray_x: %d\tray_y: %dbitch\n", ray.x,ray.y);
				break;
			}
			else if ((0 <= mx && mx < window->column_count) && (0 <= my && my < window->row_count))
			{
				ray.y+=yo;
				ray.x+=xo;
			}
			else
			{
				hit = 1;
			}
		}
		hit = 0;
		float nTan = -tan(ra);
		if ((ra > M_PI/2) && (ra < 3 * M_PI / 2))
		{
			ray.x = window->player->center->x / window->box_width * window->box_width;
			ray.y = (window->player->center->x - ray.x) * nTan + window->player->center->y;
			xo = - window->box_width;
			yo = -xo * nTan;
		}
		else if ((ra < M_PI/2) || (ra > 3 * M_PI / 2))
		{
			ray.x = window->player->center->x / window->box_width * window->box_width + window->box_width;
			ray.y = (window->player->center->x - ray.x) * nTan + window->player->center->y;
			xo = - window->box_width;
			yo = -xo * nTan;
		}
		else if ( ((int) (ra / M_PI * 180)) == 0)
		{
			printf("##########hello########\n");
			ray.y = window->player->center->y;
			ray.x = window->player->center->x / window->box_width * window->box_width;
			yo = 0;
			xo = -window->box_width;
		}
		else if ( ((int) (ra / M_PI * 180)) == 180)
		{
			printf("##########hello########\n");
			ray.y = window->player->center->y;
			ray.x = window->player->center->x / window->box_width * window->box_width + window->box_width;
			yo = 0;
			xo = -window->box_width;
		}
		while (!hit)
		{
			mx = (int)ray.x / window->box_width; my = (int)ray.y / window->box_height;
			mp = my * window->row_count + mx;
			printf("###mx: %d###\t###my: %d###\t###mp: %d###\t\n", mx,my,mp);
			if (0 < mp && mp < (window->row_count * window->column_count) && window->map[my][mx] == '1')
			{
				hit = 1;
				v_ray.x = ray.x;
				v_ray.y = ray.y;
				distV = ray_dist(window->player->center, ray.x, ray.y);
				printf("BITCHmx: %d\tmy: %dBITCH\n", mx,my);
				printf("BITCHray.x: %d\tray.y: %dBITCH\n", ray.x,ray.y);
				break;
			}
			else if (0 < mp && mp < (window->row_count * window->column_count))
			{
				ray.y+=yo;
				ray.x+=xo;
			}
			else
			{
				hit = 1;
			}
		}

		if (distV > distH)
		{ray.x = v_ray.x; ray.y = v_ray.y;}
		if (distV < distH)
		{ray.x = h_ray.x; ray.y = h_ray.y;}
		printf("distV:%f\tdistH:%f\n", distV,distH);
		printf("ray.x:%d\tray.y:%d\n", ray.x, ray.y);
		draw_ray_horiz(window, ray, 0x00ccff);
		ra+=(M_PI/180);
		if (ra < 0)
			ra += 2*M_PI;
		if (ra > 2 *M_PI)
			ra -= 2*M_PI;
		r++;
	}
}


int	main()
{
	t_window	*window;


	if (!(window = (t_window *)malloc(sizeof(t_window))))
		return (0);
	window->mlx = mlx_init();
	init_window(window, 500, 500);
	map_read(window, "srcs/map_test");
	window->win = mlx_new_window(window->mlx, window->width, window->height, "ASTROWORLD IS WEAK come to suchoworld");
	if (!init_player(window, 0x0000FF))
		return (0);
	draw_wall(window);
	drawRay3D(window);
	mlx_loop_hook(window->mlx, draw_grid, window);
	//mlx_loop_hook(window->mlx, draw_player, window);
	mlx_hook(window->win, 2, 1, press_key_for_dot, window);
	//mlx_hook(window->win, 3, 2, release_key_for_dot, window);
	mlx_loop(window->mlx);
}
