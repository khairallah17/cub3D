#include "../cub3D.h"

// void    coloring_floor_ceilling(t_global_conf *f_c_text, t_render *renderer, int j)//, int rays, int top_pixel, int bottom_pixel)
// {
//     int i;
//     unsigned int store_color_floor;
// 	unsigned int store_color_ceiling;

//     store_color_floor = tex_cub->cub->prs_map.f_c_color.floor;
//     store_color_ceiling = tex_cub->cub->prs_map.f_c_color.ceiling;
// 	i = renderer->wall_ceil;
// 	//rendring Floor
// 	while (i < WINDOW_HEIGHT)
// 		mlx_put_pixel(f_c_text->img, j, i++, store_color_floor);
// 	//rendring Ceilling
// 	i = 0;
// 	while (i < renderer->wall_ceil)
// 		mlx_put_pixel(f_c_text->img, j, i++, store_color_ceiling);
// }