/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2020/09/21 02:38:35 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <math.h>
# include <float.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include "./get_next_line/get_next_line.h"
# include "./libft/libft.h"
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17
# define texWidth 64
# define texHeight 64
# define TEXTURE_KIND 5
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
**	for struct
*/

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;

	int		width;
	int		height;
}				t_img;

typedef struct	s_sprite
{
	double		x;
	double		y;
	double		distance;
}				t_sprite;

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

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
	int			map_row;
	int			max_col;
	int			sprite_count;
}				t_cub;

typedef struct	s_window
{
	void		*mlx;
	void		*win;
	t_cub		*cub;
	t_img		img;
	t_sprite	*sprite;
	double		*z_buffer;
	int			*spriteOrder;
	double		*spriteDistance;
	int			sprite_count;
	int			**texture;
	int			**buffer;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		moveSpeed;
	double		rotSpeed;
}				t_window;

typedef struct	s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			line_height;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	int			tex_num;
	int			draw_start;
	int			draw_end;
}				t_ray;

/*
**	main.c
*/

int		key_press(int key, t_window *window);

/*
**	init.c
*/
void	init_window(t_window *window, char *path);
void	init_temp(t_window *window);
void	init_sprite(t_window *window);

/*
**	Keyboard Input
*/
/*
**	key.c
*/
void	move_player_w(t_window *window);
void	move_player_a(t_window *window);
void	move_player_s(t_window *window);
void	move_player_d(t_window *window);
void 	move_player_arrow(t_window *window, int key);

/*
**	Map Parsing / Handling
*/

/*
**	cub_parse.c
*/
void			free_2d_char(char **ptr);
void			cub_read_file(t_window *window, const char *path);
char			**cub_read_line(const char *path);

/*
**	cub_parse_path.c
*/

void	cub_parse_f_or_s(t_cub *cub, char **color, char which);
void	cub_parse_img(t_cub *cub, char **temp);
void	cub_parse_rest(t_cub *cub, char **temp);
void	cub_parse_top_eight(t_cub *cub, char **cub_temp);

/*
**	cub_parse_map.c
*/
void	cub_parse_map(t_cub *cub, char **line, int line_count);
void	cub_set_player(t_window *window, char pos, int i, int j);
void	cub_map_checkout(t_window *window);
void	cub_save_sprite(t_window *window);

/*
**	Drawing and Raycasting
*/


/*
**	raycast_wall.c
*/
void	floor_ceiling_to_buffer(t_window *window, int x);
void	init_ray(int x, t_window *window, t_ray *ray);
void	set_step_and_side(t_window *window, t_ray *ray);
void	find_and_calc_wall(t_window *window, t_ray *ray);
void	calculate_wall_texture(t_window *window, t_ray *ray);
void	wall_to_buffer(t_window *window, int x);
/*
**	raycast_sprite.c
*/
void	sortSprites(t_window *window);
/*
**	bmp.c
*/
void	set_int_in_char(unsigned char *start, int value);
void	write_bmp_header(t_window *window, int fd, int size);
void	write_data(t_window *window, int fd);
int		save_bmp(t_window *window);

/*
**	map_validity.c
*/
void	check_map_validity(t_window *window, double posX, double posY);
char	**create_padded_square(t_window *window);
#endif
