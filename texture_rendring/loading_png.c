#include "../cub3D.h"

// typedef struct s_mlx_txt
// {
//     mlx_texture_t   *up;
//     mlx_texture_t   *down;
//     mlx_texture_t   *left;
//     mlx_texture_t   *right;

// } t_mlx_txt;

void    initial_texture_loading(mlx_texture_t *texture, const char *path)
{
    texture = mlx_load_png(path);
    if (!texture)
    {
        // print error
        return ;
    }

}

void    intial_image_loading(t_global_conf *data_png)
{
    data_png->img = mlx_new_image(data_png->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!data_png->img || mlx_image_to_window(data_png->mlx, data_png->img, 0, 0))
    {
        // print error
        return ;
    }
}

void    field_texture_path(t_global_conf *data)
{
    // data->rays->texture = mlx_load_png("./texture/wall1.png");

    // if (!data->txt_load_png.up_north)
    //     printf("EROOOOOR");
    data->txt_load_png.up_north = mlx_load_png(data->cub->prs_map.texture.north);
    data->txt_load_png.down_south = mlx_load_png(data->cub->prs_map.texture.south);
    data->txt_load_png.right_east = mlx_load_png(data->cub->prs_map.texture.east);
    data->txt_load_png.left_west = mlx_load_png(data->cub->prs_map.texture.west);
    // initial_texture_loading(data->img, data->cub->prs_map.texture.east);
    // initial_texture_loading(data->img, data->cub->prs_map.texture.north);
    // initial_texture_loading(data->img, data->cub->prs_map.texture.south);
    // initial_texture_loading(data->img, data->cub->prs_map.texture.west);
}