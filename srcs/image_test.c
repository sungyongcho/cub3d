/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 18:41:28 by sucho             #+#    #+#             */
/*   Updated: 2020/09/10 23:06:56 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main()
{
		void *mlx;
		void *win;
		void *img;

		int		img_width;
		int 	img_height;

		mlx = mlx_init();
		win = mlx_new_window(mlx, 500, 500, "my_mlx");
		img = mlx_xpm_file_to_image(mlx, "includes/textures/mossy.xpm", &img_width, &img_height);
		mlx_put_image_to_window(mlx, win, img, 50, 50);
		mlx_loop(mlx);
		return (0);
}
