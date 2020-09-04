/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untextured_raycast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 18:12:46 by sucho             #+#    #+#             */
/*   Updated: 2020/09/04 00:19:39 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_EXIT	17
#define mapWidth 24
#define mapHeight 24
void fresh(t_info *info)
{
	int x = 0;
	while (x <= info->width)
	{
		int y = 0;
		while (y <= info->height)
		{
			mlx_pixel_put(info->mlx, info->win, x, y, 0x000000);
			y++;
		}
	}
}

static int		press_key(int key, t_info *info)
{
	printf("key: %d\n",key);
	if (key == KEY_A)
		move_player_left(info);
	else if (key == KEY_D)
		move_player_right(info);
	else if (key == KEY_W)
		move_player_forward(info);
	else if (key == KEY_S)
		move_player_backward(info);
	else if (key == KEY_LEFT_ARROW)
		move_player_left_arrow(info);
	else if (key == KEY_RIGHT_ARROW)
		move_player_right_arrow(info);
	else if (key == KEY_ESC)
		exit(0);
	return (0);
}

void	verLine(t_info *info, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(info->mlx, info->win, x, y, color);
		y++;
	}
}


void	calc(t_info *info)
{
	int	x_0,x_1;

	x_0 = 0;
	while (x_0 < info->width)
	{
		int y = 0;
		while (y < info->height / 2)
		{
			mlx_pixel_put(info->mlx, info->win, x_0, y, 0xEE11FF);
			y++;
		}
		y = info->height / 2;
		while (y < info->height)
		{
			mlx_pixel_put(info->mlx, info->win, x_0, y, 0xff3322);
			y++;
		}
		x_0++;
	}
	x_1 = 0;
	while (x_1 < info->width)
	{
		double cameraX = 2 * x_1 / (double)info->width - 1;
		double rayDirX = info->dirX + info->planeX * cameraX;
		double rayDirY = info->dirY + info->planeY * cameraX;

		int mapX = (int)info->posX;
		int mapY = (int)info->posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (info->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (info->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (info->map[mapX][mapY] != '0')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(info->height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + info->height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + info->height / 2;
		if(drawEnd >= info->height)
			drawEnd = info->height - 1;

		int	color;
		if (info->map[mapX][mapY] == '1')
			color = 0xFF0000;
		else if (info->map[mapX][mapY] == '2')
			color = 0x00FF00;
		else if (info->map[mapX][mapY] == '3')
			color = 0x0000FF;
		else if (info->map[mapX][mapY] == '4')
			color = 0xFFFFFF;
		else
			color = 0xFFFF00;
		if (side == 1)
			color = color / 2;

		verLine(info, x_1, drawStart, drawEnd, color);

		x_1++;
	}


}

void	init_info(t_info *info, int width, int height)
{
	info->width = width;
	info->height = height;
	info->mlx = mlx_init();
	info->posX = 12;
	info->posY = 5;
	info->dirX = -1;
	info->dirY = 0;
	info->planeX = 0;
	info->planeY = 0.66;
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;
}


int	main_loop(t_info *info)
{
	calc(info);

	// mlx_put_image_to_window(info->mlx, info->win, &info->img, 0, 0);
	return (0);
}

int	main()
{
	t_info	*info;
	if (!(info = (t_info *)malloc(sizeof(t_info))))
		return (0);
	init_info(info, 1920, 1080);
	map_return(info, "srcs/map_info_test");

	info->win = mlx_new_window(info->mlx, info->width, info->height, "untextured_raycast_test");

	mlx_loop_hook(info->mlx, main_loop, info);
	mlx_hook(info->win, X_EVENT_KEY_PRESS, 1, press_key, info);

	mlx_loop(info->mlx);
}
