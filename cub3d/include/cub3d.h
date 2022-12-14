/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoseo <yoseo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 21:06:55 by yoseo             #+#    #+#             */
/*   Updated: 2022/09/01 17:29:44 by yoseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# define PI						3.14159265359
# define RADIN					0.0174533
# define WINDOW_SIZE_X			500
# define WINDOW_SIZE_Y			500
# define CAMERA_RANGE			60
# define MINIMAP_SIZE			3
# define MINIMAP_BOX_SIZE		8
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17
# define KEY_ESC				53
# define KEY_A					0
# define KEY_S					1
# define KEY_D					2
# define KEY_W					13
# define KEY_LEFT				123
# define KEY_RIGHT				124
# define MAP_X					16
# define MAP_Y					16

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_vf2d
{
	float	x;
	float	y;
}	t_vf2d;

typedef struct s_vi2d
{
	int	x;
	int	y;
}	t_vi2d;

typedef struct s_map_info
{
	int		width;
	int		height;
	char	*map;
}	t_map_info;

typedef struct s_image
{
	void	*mlx_img;
	char	*data_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_object
{
	void		*mlx;
	void		*win;
	t_image		buff_win;
	t_image		we_texture;
	t_image		ea_texture;
	t_image		no_texture;
	t_image		so_texture;
	t_map_info	map_info;
	t_vf2d		direction;
	t_vf2d		position;
	float		pa;
	int			ccolor;
	int			fcolor;
	int			keymap[4];
	int			keyarrow[2];
}	t_object;

typedef enum e_wall_dir
{
	WE = 0,
	EA,
	NO,
	SO,
}	t_wall_dir;

typedef enum e_parse_error
{
	ERROR = 1,
}	t_error;

typedef struct s_raycast_hit
{
	t_vf2d		unit_step_size;
	t_vi2d		map_check;
	t_vi2d		step;
	t_vf2d		disthv;
	char		is_disth;
	char		is_hit;
	float		distance;
	t_wall_dir	wall_dir;
	t_vf2d		hit_point;
}	t_raycast_hit;

/*
 parsing
 */
int				parse(t_object *info, char *path);
/*
raycasting
*/
t_raycast_hit	raycasting(t_map_info *map_info,
					t_vf2d start, t_vf2d direct, float max_dist);
/*
img_draw 
*/
int				img_init(void *mlx_ptr, int size_x, int size_y, t_image *image);
int				img_file_init(void *mlx_ptr, char *file_name, t_image *image);
/*		
img_draw		
*/		
int				img_draw_pixel(t_image *image, int x, int y, int color);
int				img_draw_line(t_image *image,
					t_vi2d start, t_vi2d end, int color);
int				img_draw_fill_rectangle(t_image *image,
					t_vi2d start, t_vi2d len, int color);
int				img_get_color(t_image *image, int x, int y);
/*		
keyevent		
*/		
int				key_press(int keycode, t_object *player);
int				key_release(int keycode, t_object *_player);
int				main_loop(t_object *player);
/*		
colorhelper
*/		
int				alpha_blend(int bk, int fr);
int				img_get_color(t_image *image, int x, int y);
int				rgbtod(int r, int g, int b);
/*		
math_helper
*/		
float			safe_ra(float ra);
float			distance(t_vf2d start, t_vf2d end);
void			ft_bzero(void *s, size_t n);
/*		
rendering
*/		
void			rendering_word(t_object *player);
void			rendering_minimap(t_object *player);
/*
 win_exit
 */
int				win_exit(t_object *player);
/*		
vector_helper
*/		
t_vf2d			casting_vf2d(t_vi2d vi2d);
t_vf2d			new_vf2d(float x, float y);
t_vf2d			new_vf2d_multi(t_vf2d vf2d, float value);
t_vf2d			vf2d_multi(t_vf2d vf2d, float mul);
t_vf2d			rad_to_dir(float radin);
t_vf2d			vf2d_add(t_vf2d a, t_vf2d b);
t_vi2d			new_vi2d(int x, int y);
t_vi2d			casting_vi2d(t_vf2d vf2d);
t_vi2d			new_vi2d_multi(t_vi2d vi2d, int value);

#endif
