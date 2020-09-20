/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:54:22 by sucho             #+#    #+#             */
/*   Updated: 2020/09/20 17:35:18 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	load_image(t_window *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->height; y++)
	{
		for (int x = 0; x < img->width; x++)
		{
			texture[img->width * y + x] = img->data[img->width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_window *window)
{
	t_img	temp;

	load_image(window, window->texture[0], window->cub->no_path, &temp);
	load_image(window, window->texture[1], window->cub->so_path, &temp);
	load_image(window, window->texture[2], window->cub->we_path, &temp);
	load_image(window, window->texture[3], window->cub->ea_path, &temp);
	load_image(window, window->texture[4], window->cub->sprite_path, &temp);
}
void	init_window(t_window *window, char *path)
{
	window->mlx = mlx_init();
	if (!(window->cub = (t_cub *)malloc(sizeof(t_cub))))
		return ;
	cub_read_file(window, path);
	window->win = mlx_new_window(window->mlx,
							window->cub->res_w, window->cub->res_h, "mlx");
	if (!(window->buffer = (int **)malloc(sizeof(int *) * window->cub->res_h)))
		return ;
	int i = 0;
	while (i < window->cub->res_h)
	{
		if (!(window->buffer[i] = (int *)malloc(sizeof(int ) * window->cub->res_w + 1)))
			return ;
		i++;
	}
	if (!(window->texture = (int **)malloc(sizeof(int*) * (TEXTURE_KIND))))
		return ;
	i = 0;
	while (i < TEXTURE_KIND)
	{
		if (!(window->texture[i] = (int *)malloc(sizeof(int ) * (64 * 64))))
			return ;
		i++;
	}
	load_texture(window);
}

void	init_temp(t_window *window)
{
	window->moveSpeed = 0.05;
	window->rotSpeed = 0.05;
	window->img.img = mlx_new_image(window->mlx, window->cub->res_w, window->cub->res_h);
	window->img.data = (int *)mlx_get_data_addr(window->img.img, &window->img.bpp, &window->img.size_l, &window->img.endian);
}

void	init_sprite(t_window *window)
{
	if (!(window->z_buffer = (double *)malloc(sizeof(double) * (window->cub->res_w))))
		return ;
	if (!(window->spriteOrder = (int *)malloc(sizeof(int) * (window->cub->sprite_count))))
		return ;
	if (!(window->spriteDistance = (double *)malloc(sizeof(double) * (window->cub->sprite_count))))
		return ;
}
