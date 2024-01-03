#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <libc.h>
#include "./gnl/get_next_line.h"
#include "libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"
// # include "./MLX42/include/MLX42/MLX42_Int.h"


# define WINDOW_HEIGHT 1000
# define WINDOW_WIDTH  700

typedef struct s_texture
{
	char 	*north;
	char 	*south;
	char 	*west;
	char 	*east;
}   t_texture;

typedef struct s_color_rgb
{
	int			floor;
	int			ceiling;
	int			*tab_color;
} t_color_rgb;

typedef struct s_map
{
	char **map_grid;
	int	width;
	int height;
} t_map;

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
	// void	*master;
	// int		*master_data;
	void	*wall_north;
	int		*wall_no_data;
	int		wall_no_side;

	void	*wall_south;
	int		*wall_so_data;
	int		wall_so_side;

	void	*wall_east;
	int		*wall_ea_data;
	int		wall_ea_side;

	void	*wall_west;
	int		*wall_we_data;
	int		wall_we_side;
}	t_mlx;

typedef struct s_cub3d
{
	t_map_data prs_map;
	char *path_maps;
	char *tmp_store;
	int	count_txtr_line;
	int error_parse_nb;
	int	map_fd;
	t_mlx	mlx;
}	t_cub3d;


void    check_arguments(int ac, char **av);
// static void initial_param(t_cub3d *get_parm, char *path_map);
// static void parse_texture(t_cub3d *cub);
int parsing_remove_new_line(t_cub3d *cub);
int index_first_path(char *str, int i);
int index_end_path(char *str, int i);
char *search_path_texture(t_cub3d *cub);
int check_color(t_cub3d *cub);
// void   parsing(int ac, char **av);
t_cub3d *parsing(int ac, char **av);
#endif