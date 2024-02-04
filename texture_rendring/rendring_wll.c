#include "../cub3D.h"

double calcule_offset_x(t_global_conf *mlx, mlx_texture_t *texture)
{
	double texture_offset_x;
	if (mlx->rays->was_hit_vertical)
		texture_offset_x = (int)fmodf(mlx->rays->wall_hit_y * texture->width / TILE, texture->width);
	else
		texture_offset_x = (int)fmodf(mlx->rays->wall_hit_y * (texture->width / TILE), texture->width);
	return (texture_offset_x);
}