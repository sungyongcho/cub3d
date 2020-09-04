/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2020/09/04 23:59:45 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <float.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"

/*
** for getting inputs on both LINUX & MACOS
*/

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#ifdef _WIN64
	#else
	#endif
#elif __APPLE__
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR
	#elif TARGET_OS_IPHONE
	#elif TARGET_OS_MAC
		# include "./minilibx_mms_20200219/mlx.h"
		# define KEY_W 13
		# define KEY_A 0
		# define KEY_S 1
		# define KEY_D 2
		# define KEY_LEFT_ARROW 123
		# define KEY_RIGHT_ARROW 124
		# define KEY_ESC 53
	#else
	#   error "Unknown Apple platform"
	#endif
#elif __linux__
	#ifndef M_PI
		#define M_PI (3.14159265358979323846)
	#endif
	# include "./minilibx-linux/mlx.h"
	# define KEY_W 119
	# define KEY_A 97
	# define KEY_S 115
	# define KEY_D 100
	# define KEY_LEFT_ARROW 65361
	# define KEY_RIGHT_ARROW 65363
#elif __unix__ // all unices not caught above
	// Unix
#elif defined(_POSIX_VERSION)
	// POSIX
#else
#   error "Unknown compiler"
#endif


/*
** for struct
*/

typedef struct	s_point
{

	int			x;
	int			y;

}				t_point;

typedef struct	s_player
{
	t_point		*vision;

	int			p_color;

	t_point		*center;
	int			pdx;
	int			pdy;
	float		pa;

}				t_player;

typedef struct	s_window
{
	void		*mlx;
	void		*win;

	int			width;
	int			height;
	char		**map;
	int			row_count;
	int			column_count;
	int			total_unit;
	int			box_width;
	int			box_height;

	t_player	*player;

}				t_window;

typedef struct	s_cub
{
	int			res_w;
	int			res_h;
	char*		no_path;
	char*		so_path;
	char*		ea_path;
	char*		we_path;
	char*		sprite_path;
	int			floor_color;
	int			ceiling_color;
	char		**map;
}				t_cub;


/*
** map.c
*/

int		draw_line_bres(t_window *window, t_point *begin, t_point *end, int color);
int		draw_ray_horiz(t_window *window, t_point ray, int color);
int		draw_player(t_window *window, int color);
void	map_read(t_window *window, char *path);
void	map_check_player(t_window *window);
void	drawRay3D(t_window *window);

/*
** main.c
*/


/*
**	for testing purpose only (need to delete after)
*/

typedef struct s_info
{
	int width;
	int height;
	char		**map;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	void	*mlx;
	void 	*win;
	double	moveSpeed;
	double	rotSpeed;
	int		window_width;
	int		window_height;
}				t_info;

/*
**	Keyboard Input
*/

/*
**	key_wasd.c
*/

void		move_player_forward(t_info *info);
void		move_player_backward(t_info *info);
void		move_player_left(t_info *info);
void		move_player_right(t_info *info);

/*
**	key_arrow.c
*/
void		move_player_left_arrow(t_info *info);
void		move_player_right_arrow(t_info *info);
void		fresh(t_info *info);
/*
**	Map Handling
*/

/*
**	map_parse.c
*/

void			cub_parse(t_cub *cub, char *path);

#endif
