/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 17:36:08 by sucho             #+#    #+#             */
/*   Updated: 2020/09/15 10:232 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#define X_EVENT_KEY_PRESS	2

void	draw(t_window *window)
{
	for (int y = 0; y < window->cub->res_h; y++)
	{
		for (int x = 0; x < window->cub->res_w; x++)
		{
			window->img.data[y * window->cub->res_w + x] = window->buffer[y][x];
		}
	}
	mlx_put_image_to_window(window->mlx, window->win, window->img.img, 0, 0);
}


void	calc(t_window *window)
{
	int	x;

	x = 0;
	while (x < window->cub->res_w)
		floor_ceiling_to_buffer(window, x++);
	x = 0;
	while (x < window->cub->res_w)
		wall_to_buffer(window, x++);
	sortSprites(window);
	for(int i = 0; i < window->cub->sprite_count; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = window->sprite[i].x - window->posX;
		double spriteY = window->sprite[i].y - window->posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (window -> planeX * window->dirY - window->dirX * window->planeY); //required for correct matrix multiplication

		double transformX = invDet * (window->dirY * spriteX - window->dirX * spriteY);
		double transformY = invDet * (-window->planeY * spriteX + window->planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

		int spriteScreenX = (int)((window->cub->res_w / 2) * (1 + transformX / transformY));

		//calculate height of the sprite on screen
		int spriteHeight = abs((int)(window->cub->res_h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + window->cub->res_h / 2;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + window->cub->res_h / 2;
		if(drawEndY >= window->cub->res_h) drawEndY = window->cub->res_h - 1;

		//calculate width of the sprite
		int spriteWidth = abs( (int) (window->cub->res_h / (transformY)));
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= window->cub->res_w) drawEndX = window->cub->res_w - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
		  int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
		  //the conditions in the if are:
		  //1) it's in front of camera plane so you don't see things behind you
		  //2) it's on the screen (left)
		  //3) it's on the screen (right)
		  //4) ZBuffer, with perpendicular distance
		  if(transformY > 0 && stripe > 0 && stripe < window->cub->res_w && transformY < window->z_buffer[stripe])
		  {
		  for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
		  {
		    int d = (y) * 256 - window->cub->res_h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
		    int texY = ((d * 64) / spriteHeight) / 256;
		    int color = window->texture[4][64 * texY + texX]; //get current color from the texture
		    if((color & 0x00FFFFFF) != 0) window->buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
		  }
		  }
		}
    }

}

int	main_loop(t_window *window)
{
	calc(window);
	draw(window);
	return (0);
}

int		key_press(int key, t_window *window)
{
	if (key == KEY_W)
		move_player_w(window);
	else if (key == KEY_A)
		move_player_a(window);
	else if (key == KEY_S)
		move_player_s(window);
	else if (key == KEY_D)
		move_player_d(window);
	else if (key == KEY_LEFT_ARROW || key == KEY_RIGHT_ARROW)
		move_player_arrow(window, key);
	else if (key == KEY_ESC)
		exit(0);
	return (0);
}


int	main(int argc, char **argv)
{
	t_window	*window;

	if (!(window = (t_window *)malloc(sizeof(t_window))))
		return (0);

	if (argc == 2)
	{
		init_window(window, argv[1]);
		init_temp(window);
		init_sprite(window);
		mlx_loop_hook(window->mlx, main_loop, window);
		mlx_hook(window->win, X_EVENT_KEY_PRESS, 1, key_press, window);
		mlx_loop(window->mlx);
	}
	else if (argc == 3 && ft_strncmp(argv[2],"--save",6) == 0)
	{
		init_window(window, argv[1]);
		init_temp(window);
		init_sprite(window);
		calc(window);
		draw(window);
		save_bmp(window);
		exit(0);
	}
	else
	{
		write(1, "Error.\n", 6);
	}
	return (0);
}
