#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <libc.h>

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

typedef struct s_cub
{
	char *path_maps;
	int	map_fd;
	t_map_data prs_map;
}	t_cub;

#endif