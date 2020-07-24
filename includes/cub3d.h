/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 02:33:19 by sucho             #+#    #+#             */
/*   Updated: 2020/07/25 03:05:51 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <math.h>

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

typedef struct	s_player
{
	int			px;
	int			py;

	int			pdx;
	int			pdy;
	double		pa;

}				t_player;

typedef struct	s_window
{
	void		*mlx;
	void		*win;

	int			width;
	int			height;
	int			grid_count;

	t_player	*player;

}				t_window;

int				draw_line_bres(t_window *window, int x_0, int y_0, int x_1, int y_1);
int				draw_player(t_window *window);
