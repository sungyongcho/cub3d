/* ************************************************************************** */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 02:33:19 by sucho             #+#    #+#             */
/*   Updated: 2020/08/25 15:31:31 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <fcntl.h>
#include "./get_next_line/get_next_line.h"
#include "./libft/libft.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	//define something for Windows (32-bit and 64-bit, this part is common)
	#ifdef _WIN64
	//define something for Windows (64-bit only)
	#else
	//define something for Windows (32-bit only)
	#endif
#elif __APPLE__
	#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR
		 // iOS Simulator
	#elif TARGET_OS_IPHONE
		// iOS device
	#elif TARGET_OS_MAC
		# include "./minilibx_mms_20200219/mlx.h"
		# define KEY_W 13
		# define KEY_A 0
		# define KEY_S 1
		# define KEY_D 2
		# define KEY_LEFT_ARROW 123
		# define KEY_RIGHT_ARROW 124
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

int		draw_line_bres(t_window *window, t_point *begin, t_point *end, int color);
int		draw_ray_horiz(t_window *window, t_point ray, int color);
int		draw_player(t_window *window, int color);
void	map_read(t_window *window, char *path);
void	map_check_player(t_window *window);
void	drawRay3D(t_window *window);
