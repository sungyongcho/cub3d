/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 02:33:19 by sucho             #+#    #+#             */
/*   Updated: 2020/07/22 05:35:05 by sucho            ###   ########.fr       */
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
    #else
    #   error "Unknown Apple platform"
    #endif
#elif __linux__
    # include "./minilibx-linux/mlx.h"
    # define KEY_W 119
    # define KEY_A 97
    # define KEY_S 115
    # define KEY_D 100
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
	int			pa;

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

int    draw_line_bres(t_window *window);
