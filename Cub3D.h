#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <libc.h>
#include "./gnl/get_next_line.h"

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

typedef struct s_cub3d
{
	char *path_maps;
	char *tmp_store;
	int	map_fd;
	t_map_data prs_map;
}	t_cub3d;


void    check_arguments(int ac, char **av);
// static void initial_param(t_cub3d *get_parm, char *path_map);
// static void parse_texture(t_cub3d *cub);
int parsing_remove_new_line(t_cub3d *cub);
int index_first_path(char *str, int i);
int index_end_path(char *str, int i);
char *search_path_texture(t_cub3d *cub);
char *check_color(t_cub3d *cub);//, int color);
#endif