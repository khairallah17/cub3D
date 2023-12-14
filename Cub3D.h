#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
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
	int	red;
	int	green;
	int	blue;
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
	t_color_rgb	floor;
	t_color_rgb ceiling;
	t_texture	texture;
}	t_map_data;

#endif