/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:55:02 by eagoumi           #+#    #+#             */
/*   Updated: 2024/02/06 23:10:05 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>
# include <libc.h>
# include <float.h>
# include <math.h>
# include "libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"

# define MAX_FLAGS_NUMBER	6
# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20
# define WINDOW_HEIGHT 768
# define WINDOW_WIDTH 1024
# define TILE 64
# define PLAYER_TILE 8
# define RAY_WIDTH 1
# define NUM_OF_RAYS WINDOW_WIDTH
# define RAYS 60
# define FOV (60 * (M_PI / 180))
# define MINIMAP_SCALE 64
# define DEFAULT_PLAYER_SPEED     		0.2
# define DEFAULT_PLAYER_ROTATION_ANGLE	0.1

typedef float	t_double;

typedef struct s_map3d
{
	int				fd;
	unsigned int	floor;
	unsigned int	ceiling;
	int				width;
	int				height;
	char			*map1d;
	int				players;
	t_double		player_x;
	t_double		player_y;
	t_double		player_speed;
	t_double		player_angle;
	t_double		player_rotation_angle;
	int				not_valid;
	int				lines;
	int				offset;
	int				flags_number;
	char			north[PATH_MAX];
	char			south[PATH_MAX];
	char			east[PATH_MAX];
	char			west[PATH_MAX];
	char			*filename;
	int				bodystart;
}	t_map3d;

char			map_get10(int x, int y);
t_map3d			*getmap(void);
void			cub3d_clear_image(mlx_image_t *img);
void			map_error(const char *msgerr);
//

typedef struct s_color_rgb
{
	int			*tab_color;
}	t_color_rgb;

typedef struct s_map_data
{
	t_color_rgb	f_c_color;
}	t_map_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
}	t_mlx;

typedef struct s_ray_info
{
	t_double	ray_angle;
	t_double	wall_hit_x;
	t_double	wall_hit_y;
	t_double	distance;
	int			was_hit_vertical;
	int			ray_facing_up;
	int			ray_facing_down;
	int			ray_facing_left;
	int			ray_facing_right;
	t_double	next_horizontal_hit_x;
	t_double	next_horizontal_hit_y;
	t_double	x_step;
	t_double	y_step;
	t_double	x_inter;
	t_double	y_inter;
	t_double	x_check;
	t_double	y_check;
	t_double	next_vertical_hit_x;
	t_double	next_vertical_hit_y;
	int			horizontal_wall_hit;
	t_double	horizontal_wall_hit_x;
	t_double	horizontal_wall_hit_y;
	int			vertical_wall_hit;
	t_double	vertical_wall_hit_x;
	t_double	vertical_wall_hit_y;
	t_double	horizontal_distance;
	t_double	vertical_distance;
}	t_ray_info;

typedef struct s_ray
{
	mlx_texture_t	*texture;
	t_double		ray_angle;
	t_double		wall_hit_x;
	t_double		wall_hit_y;
	t_double		distance;
	int				was_hit_vertical;
	int				ray_facing_up;
	int				ray_facing_down;
	int				ray_facing_left;
	int				ray_facing_right;
}	t_ray;

typedef struct s_cub3d
{
	t_map_data	prs_map;
	char		*tmp_store;
	int			count_txtr_line;
	int			error_parse_nb;
	int			map_fd;
	t_mlx		mlx;
}	t_cub3d;

typedef struct s_line_coordinates
{
	t_double	px;
	t_double	py;
	t_double	dx;
	t_double	dy;
	t_double	slope;
	t_double	y_intercept;
}	t_line_coordinates;

typedef struct s_mlx_txt
{
	mlx_texture_t	*up_north;
	mlx_texture_t	*down_south;
	mlx_texture_t	*right_east;
	mlx_texture_t	*left_west;
}	t_mlx_txt;

typedef struct s_global_conf
{
	int			i;
	int			j;
	t_mlx_txt	txt_load_png;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_ray		rays[NUM_OF_RAYS];
	uint32_t	*color_buffer;
	t_cub3d		*cub;
}	t_global_conf;

typedef struct s_render
{
	int			line_pixel_height;
	int			distance_from_top_floor;
	int			wall_height;
	t_double	distance_to_projection_plane;
	t_double	projected_wall_height;
	int			wall_top;
	int			wall_ceil;
	t_double	correct_distance;	
}	t_render;

/*=============================PARSING======================================*/
t_map3d			*getmap(void);
unsigned int	pixels_rgba(int r, int g, int b, int a);
int				ft_isspace(int c);
int				ft_isline(char c);
int				ft_isstab(int c);
int				ft_extcmp(const char *file, const char *ext);
void			map_error(const char *msgerr);
char			map_get10(int x, int y);
void			is_surrounded_by_spaces(int x, int y);
void			map_check(t_map3d *map);
void			open_cubfile(char *cubfile);
int				ft_copypath(t_map3d *map, char *dst, char *c);
ssize_t			ft_mapreadch(t_map3d *map, char *c);
char			ft_skipcharset(t_map3d *map, char *c, const char *charset);
int				ft_atobyte(t_map3d *map, int n, char *c);
int				ft_copycolor(t_map3d *map, unsigned int *bgr, char *c);
void			fill_map_body(t_map3d *map);
void			read_map_body(t_map3d *map);
void			update_map_width(t_map3d *map, \
						int *first_index, int *last_index);
void			getmapsize(t_map3d *map);
void			map_load_files(char c, t_map3d	*map);
void			map_load(char *cubfile);
t_cub3d			*cub3d_parsing(int ac, char **av);

/*=============================TEXTURE======================================*/
unsigned int	generate_color(t_global_conf *texture, int x, int y, int i);
void			field_texture_path(t_global_conf *data);
void			rendring_texture(t_global_conf *tex_cub, \
					t_render *renderer, int j);
/** RAY CASTING **/
void			calculating_horizontal_distances(t_global_conf *config, \
												t_ray_info *ray_info);
void			horizontal_casting(t_global_conf *config, t_ray_info *ray_info);
void			calculating_vertical_distances(t_global_conf *config, \
											t_ray_info *ray_info);
void			vertical_casting(t_global_conf *config, t_ray_info *ray_info);
void			ray_casting_setup(t_ray_info *ray_info, t_double ray_angle);
void			ray_distance_assignement(t_global_conf *config, \
					t_ray_info *ray_info, int pos);
void			cast_ray(t_global_conf *config, t_double ray_angle, int pos);

/** CASTING UTILS **/
t_double		correct_angle(t_double ray_angle);
t_double		calculating_distance(t_double x1, t_double y1, \
					t_double x2, t_double y2);
void			cast_all_rays(t_global_conf *config);

/** GAME INIT **/
void			setup(t_global_conf *config);
void			player_init(t_global_conf *player);
void			init_ray(t_ray_info *ray_info);
void			player_init(t_global_conf *config);

/* PLAYER MOVEMENTS */
int				wall_collision(t_global_conf *config, float x, float y);
void			player_movements_checker(t_global_conf *config, \
											mlx_key_data_t *key);
void			move_up(t_global_conf *config);
void			move_down(t_global_conf *config);
void			move_left(void);
void			move_right(t_global_conf *config);

/* HOOKS */
void			update(t_global_conf *conf);
void			my_key_hook(mlx_key_data_t keydata, void *param);

/* DRAW MINIMAP */
void			draw_player(t_global_conf *config);
void			draw(t_global_conf *config, int i, int j, uint32_t color);
void			draw_map(t_global_conf *config);

/* DRAWING RAYS */
void			draw_rays(t_global_conf *config, int pos);

/* GAME LAUNCHER */
void			launch(int ac, char **av);
void			get_player(t_global_conf *config);
void			draw_single_line(t_global_conf *config);

/* RENDERING */
void			init_render(t_render *rend);
// void		render_3d(t_global_conf *config, int pos);
void			render_3d(t_global_conf *config, int i);

int				cub3d_exit(t_global_conf *config);
void			cub3d_put_pixel(
					mlx_image_t *img,
					uint32_t x,
					uint32_t y,
					uint32_t color);
#endif