/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_wasd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 18:37:51 by sucho             #+#    #+#             */
/*   Updated: 2020/09/03 02:52:17 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		move_player_forward(t_info *info)
{
	if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] == '0')
		info->posX += info->dirX * info->moveSpeed;
	if (info->map[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)] == '0')
		info->posY += info->dirY * info->moveSpeed;
}

void		move_player_backward(t_info *info)
{
	if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] == '0')
		info->posX -= info->dirX * info->moveSpeed;
	if (info->map[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)] == '0')
		info->posY -= info->dirY * info->moveSpeed;
}
void		move_player_left(t_info *info)
{
	if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] == '0')
		info->posX -= info->dirY * info->moveSpeed;
	if (info->map[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)] == '0')
		info->posY += info->dirX * info->moveSpeed;
}
void		move_player_right(t_info *info)
{
	if (info->map[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)] == '0')
		info->posX += info->dirY * info->moveSpeed;
	if (info->map[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)] == '0')
		info->posY -= info->dirX * info->moveSpeed;
}
