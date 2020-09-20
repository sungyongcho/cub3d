/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/04 15:27:36 by sucho             #+#    #+#             */
/*   Updated: 2020/09/21 03:49:36 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

void	cub_parse_f_or_s(t_cub *cub, char **color, char which)
{
	int		i;

	if (which == 'F')
	{
		i = 0;
		while (color[i])
			cub->floor_color = cub->floor_color * 256 + ft_atoi(color[i++]);
	}
	if (which == 'C')
	{
		i = 0;
		while (color[i])
			cub->ceiling_color = cub->ceiling_color * 256 + ft_atoi(color[i++]);
	}
}

void	cub_parse_img(t_cub *cub, char **temp)
{
	if ((char)temp[0][0] == 'N')
	{
		cub->no_path = ft_strdup(temp[1]);
	}
	else if ((char)temp[0][0] == 'E')
	{

		cub->ea_path = ft_strdup(temp[1]);
	}
	else if ((char)temp[0][0] == 'W')
	{
		cub->we_path = ft_strdup(temp[1]);
	}
	else if ((char)temp[0][0] == 'S')
	{
		cub->so_path = ft_strdup(temp[1]);
	}
	else
	{
		write(1, "error detected", 15);
		exit(0);
	}
}

void	cub_parse_rest(t_cub *cub, char **temp)
{
	char**	color_temp;
	int		j;

	j = 0;
	if ((char)temp[0][0] == 'R')
	{
		while (temp[j])
			j++;
		printf("i: %d\n",j);
		if (j != 3)
		{
			write(1,"Error. #1# \n",10);
			exit(1);
		}
		j = 0;
		while (temp[1][j])
		{
			if (!ft_isdigit(temp[1][j++]))
			{
				write(1,"Error.#2#\n",10);
				exit(1);
			}
		}
		while (temp[2][j])
		{
			if (!ft_isdigit(temp[2][j++]))
			{
				write(1,"Error.#3#\n",10);
				exit(1);
			}
		}
		if (cub->res_w != 0 || cub->res_h != 0)
		{
			{
				write(1,"Error.\n",7);
				exit(1);
			}
		}
		cub->res_w = ft_atoi(temp[1]);
		cub->res_h = ft_atoi(temp[2]);
	}
	else if ((char)temp[0][0] == 'S')
		cub->sprite_path = ft_strdup(temp[1]);
	else if ((char)temp[0][0] == 'F' || (char)temp[0][0] == 'C')
	{
		color_temp = ft_split(temp[1], ',');
		cub_parse_f_or_s(cub, color_temp, (char) temp[0][0]); // CHECK memory leah for color_temp
		free_2d_char(color_temp);
	}
	else
	{
		write(1,"Error.\n",7);
		exit(0);
	}

}

void	cub_parse_top_eight(t_cub *cub, char **cub_temp)
{
	int i;
	i = 0;
	char **temp;
	while (i < 8)
	{
		temp = ft_split(cub_temp[i], ' ');
		if (ft_strlen(temp[0]) == 2)
			cub_parse_img(cub, temp);
		else
			cub_parse_rest(cub, temp);
		free_2d_char(temp);
		i++;
	}
}
