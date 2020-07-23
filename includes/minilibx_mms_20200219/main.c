#include "../includes/cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	init_player(t_window *window, int a, int b)
{
	window->px = a;
	window->py = b;
}

void	init_window_and_grid_num(t_window *window, int a, int b, int c)
{
	window->width = a;
	window->height = b;
	window->grid_count = c;
}


void		move_dot_left(t_window *window)
{
	window->pa -= 0.1;
	if (window->pa <0)
		window->pa += 2 * M_PI;
	window->pdx = cos(window->pa) * 5;
	window->pdy = sin(window->pa) * 5;
	mlx_pixel_put(window->mlx, window->win, --window->px, window->py, 0xFFFF00);
	mlx_pixel_put(window->mlx, window->win, window->px + 1, window->py, 0x000000);
}

void		move_dot_right(t_window *window)
{
	window->pa += 0.1;
	if (window->pa > 2 * M_PI)
		window->pa -= 2 * M_PI;
	window->pdx = cos(window->pa) * 5;
	window->pdy = sin(window->pa) * 5;
	mlx_pixel_put(window->mlx, window->win, ++window->px, window->py, 0xFFFF00);
	mlx_pixel_put(window->mlx, window->win, window->px - 1, window->py, 0x000000);
}

void		move_dot_up(t_window *window)
{
	mlx_pixel_put(window->mlx, window->win, window->px, --window->py, 0xFFFF00);
	mlx_pixel_put(window->mlx, window->win, window->px, window->py + 1, 0x000000);
}

void		move_dot_down(t_window *window)
{
	mlx_pixel_put(window->mlx, window->win, window->px, ++window->py, 0xFFFF00);
	mlx_pixel_put(window->mlx, window->win, window->px, window->py - 1, 0x000000);
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
	if (key == 0)
		move_dot_left(window);
	else if (key == 2)
		move_dot_right(window);
	else if (key == 13)
		move_dot_up(window);
	else if (key == 1)
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

	if (!(window = (t_window *)malloc(sizeof(void *) + 1)))
		return (0);
	window->mlx = mlx_init();
	init_window_and_grid_num(window, 500, 500, 10);
	window->win = mlx_new_window(window->mlx, window->width, window->height, "ASTROWORLD IS WEAK come to suchoworld");
	init_player(window, 250, 250);
	mlx_pixel_put(window->mlx,window->win,window->px,window->py,0xFFFF00);
	mlx_loop_hook(window->mlx, draw_grid, window);
	mlx_hook(window->win, 2, 1, press_key_for_dot, window);
	//mlx_hook(window->win, 3, 2, release_key_for_dot, window);
	mlx_loop(window->mlx);

}
