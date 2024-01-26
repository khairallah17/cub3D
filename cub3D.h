/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:55:02 by eagoumi           #+#    #+#             */
/*   Updated: 2024/01/26 19:00:28 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>
// # include <libc.h>
# include <math.h>
# include "./gnl/get_next_line.h"
# include "libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
// # include "./MLX42/include/MLX42/MLX42_Int.h"

# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20
# define WINDOW_HEIGHT 768 
# define WINDOW_WIDTH 1024
# define TILE 8
# define PLAYER_TILE 8
# define NUM_OF_RAYS WINDOW_WIDTH
# define RAYS 60
# define FOV (60 * (3.14159265358979323846264338327950288 / 180))
# define MINIMAP_SCALE 10

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_texture;

typedef struct s_color_rgb
{
	int			floor;
	int			ceiling;
	int			*tab_color;
}	t_color_rgb;

typedef struct s_map
{
	char	**map_grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_map_data
{
	t_map		map;
	t_color_rgb	f_c_color;
	t_texture	texture;
}	t_map_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
}	t_mlx;

typedef struct s_player
{
	double	x;
	double	y;
	double	rotation_angle;
	double	rotation_speed;
	int		speed;
	int		direction;
	int		color;
}	t_player;

typedef struct s_ray_info
{
	double	ray_angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	int		was_hit_vertical;
	int		ray_facing_up;
	int		ray_facing_down;
	int		ray_facing_left;
	int		ray_facing_right;
	double	next_horizontal_hit_x;
	double	next_horizontal_hit_y;
	double	x_step;
	double	y_step;
	double	x_inter;
	double	y_inter;
	double	x_check;
	double	y_check;
	double	next_vertical_hit_x;
	double	next_vertical_hit_y;
	int		horizontal_wall_hit;
	double	horizontal_wall_hit_x;
	double	horizontal_wall_hit_y;
	int		vertical_wall_hit;
	double	vertical_wall_hit_x;
	double	vertical_wall_hit_y;
	double	horizontal_distance;
	double	vertical_distance;
}	t_ray_info;

typedef struct s_ray
{
	double	ray_angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	int		was_hit_vertical;
	int		ray_facing_up;
	int		ray_facing_down;
	int		ray_facing_left;
	int		ray_facing_right;
}	t_ray;

typedef struct s_cub3d
{
	t_map_data	prs_map;
	char		*path_maps;
	char		*tmp_store;
	int			count_txtr_line;
	int			error_parse_nb;
	int			map_fd;
	t_player	player;
	t_mlx		mlx;
}	t_cub3d;

typedef struct s_line_coordinates
{
	double	px;
	double	py;
	double	dx;
	double	dy;
	double	slope;
	double	y_intercept;
}	t_line_coordinates;

typedef struct s_global_conf
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	*player;
	t_ray		*rays;
	uint32_t	*color_buffer;
	t_cub3d		*cub;
}	t_global_conf;

void		check_arguments(int ac, char **av);
// static void initial_param(t_cub3d *get_parm, char *path_map);
// static void parse_texture(t_cub3d *cub);
int			parsing_remove_new_line(t_cub3d *cub);
int			index_first_path(char *str, int i);
int			index_end_path(char *str, int i);
char		*search_path_texture(t_cub3d *cub);
int			check_color(t_cub3d *cub);
// void 	  parsing(int ac, char **av);
t_cub3d		*parsing(int ac, char **av);
void		send_err_free(t_cub3d *cub, int err_nbr, char *error_msg);
void		check_map(t_cub3d *cub);

/** RAY CASTING **/
void		calculating_horizontal_distances(t_global_conf *config, \
											t_ray_info *ray_info);
void		horizontal_casting(t_global_conf *config, t_ray_info *ray_info);
void		calculating_vertical_distances(t_global_conf *config, \
										t_ray_info *ray_info);
void		vertical_casting(t_global_conf *config, t_ray_info *ray_info);
void		ray_casting_setup(t_ray_info *ray_info, double ray_angle);
void		ray_distance_assignement(t_global_conf *config, \
				t_ray_info *ray_info, int pos);
void		cast_ray(t_global_conf *config, double ray_angle, int pos);

/** CASTING UTILS **/
double		correct_angle(double ray_angle);
double		calculating_distance(double x1, double y1, double x2, double y2);
int			wall_hit_checker(t_global_conf *config, double x, double y);
void		cast_all_rays(t_global_conf *config);

/** GAME INIT **/
void		setup(t_global_conf *config);
void		player_init(t_global_conf *player);
void		init_ray(t_ray_info *ray_info);
void		player_init(t_global_conf *config);

/* PLAYER MOVEMENTS */
int			wall_collision(t_global_conf *config, double x, double y);
void		player_movements_checker(t_global_conf *config, \
										mlx_key_data_t *key);
void		move_up(t_global_conf *config);
void		move_down(t_global_conf *config);
void		move_left(t_global_conf *config);
void		move_right(t_global_conf *config);

/* HOOKS */
void		close_key_hook(void *param);
void		update(t_global_conf *conf);
void		key_hook(mlx_key_data_t keydata, void *param);

/* DRAW MINIMAP */
void		draw_player(t_global_conf *config);
void		draw(t_global_conf *config, int i, int j, uint32_t color);
void		draw_map(t_global_conf *config);

/* DRAWING RAYS */
void		draw_rays(t_global_conf *config, int pos);

/* GAME LAUNCHER */
void		launch(int ac, char **av);
void		get_player(t_global_conf *config);

#endif