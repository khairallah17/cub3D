#include "../cub3D.h"

void    field_texture_path(t_global_conf *data)
{
    data->txt_load_png.up_north = mlx_load_png(getmap()->north);
    if (!data->txt_load_png.up_north)
        map_error("Error: loading image");
    data->txt_load_png.down_south = mlx_load_png(getmap()->south);
    if (!data->txt_load_png.down_south)
        map_error("Error: loading image");
    data->txt_load_png.right_east = mlx_load_png(getmap()->east);
    if (!data->txt_load_png.right_east)
        map_error("Error: loading image");
    data->txt_load_png.left_west = mlx_load_png(getmap()->west);
    if (!data->txt_load_png.left_west)
        map_error("Error: loading image");
}
