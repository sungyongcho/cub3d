/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_arrow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 18:37:51 by sucho             #+#    #+#             */
/*   Updated: 2020/09/05 02:19:38 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		move_player_arrow(t_info *info, int key_num)
{
	if (key_num == left_key)
	{
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	else if (key_num == right_key)
	{
		double oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		double oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
}

void	move_player_wasd(t_info *info, int key_num)
{
	if (key_num == 'W')
	{
		if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] == '0')
			info->posX += info->dirX * info->moveSpeed;
		if (info->map[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)] == '0')
			info->posY += info->dirY * info->moveSpeed;
	}
	else if (key_num == 'S')
	{
		if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] == '0')
			info->posX -= info->dirX * info->moveSpeed;
		if (info->map[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)] == '0')
			info->posY -= info->dirY * info->moveSpeed;
	}
	else if (key_num == 'A')
	{
		if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] == '0')
			info->posX -= info->dirY * info->moveSpeed;
		if (info->map[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)] == '0')
			info->posY += info->dirX * info->moveSpeed;
	}
	else if (key_num == 'D')
	{
		if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] == '0')
			info->posX += info->dirY * info->moveSpeed;
		if (info->map[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)] == '0')
			info->posY -= info->dirX * info->moveSpeed;
	}
}

int		press_key(int key, t_info *info)
{

}
