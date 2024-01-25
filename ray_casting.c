#include "MLX42/include/MLX42/MLX42.h"
// #include <libc.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>


char map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    "11111111111111111111",
    "10000000000000000001",
    "10000000000000000001",
    "10001010101010101001",
    "10000000000000000001",
    "1000000N000000001001",
    "10000000000000010001",
    "10000000000000001001",
    "10000000000001111001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
    "11111111111111111111"
};

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void draw_rays(t_global_conf *config, int pos) {

    double dx;
    double dy;
    double px;
    double py;
    double tmp;

    px = floor(config->player->x * MINIMAP_SCALE);
    py = floor(config->player->y * MINIMAP_SCALE);
    dx = floor(config->rays[pos].wall_hit_x);
    dy = floor(config->rays[pos].wall_hit_y);

    double slope = (py - dy) / (px - dx);
    double y_intercept = py - slope * px;

    if (px >= dx)
    {
        tmp = px;
        px = dx;
        dx = tmp;
    }
    while (px <= dx)
    {
        mlx_put_pixel(config->img,  px, slope * px + y_intercept, 0x008000FF);
        px += 0.01;
    }

}


// //---------------------------------------- Texture Eagoumi ----------------------------------------//
// #define TEXTURE_WIDTH 32
// #define TEXTURE_HEIGHT 32

// uint32_t *wall_texture = NULL;
// void    texture_walls(uint32_t *wall_texture)
// {
//     wall_texture = (uint32_t *)malloc(sizeof(uint32_t) * (uint32_t)TEXTURE_WIDTH * (uint32_t)TEXTURE_HEIGHT);
//     //=-----------------------------------------------=//
//     for (int x = 0; x < TEXTURE_WIDTH; x++)
//     {
//         for (int yt = 0; yt < TEXTURE_HEIGHT; yt++)
//             if (x % 8 == 0 && yt % 8 == 0)
//             {
//                 // puts("s");
//                 wall_texture[(TEXTURE_WIDTH * yt) + x] = 0xFF0000FF;
//             }
//             else
//                 wall_texture[(TEXTURE_WIDTH * yt) + x] = 0xFF000000;
//     }
// }
// //-----------------------------------------------------------------------------------------------//

// void    render_3d(t_global_conf *config) {
//     int     i;
//     int     j;
//     int     wall_height;
//     double  distance_to_projection_plane;
//     double  projected_wall_height;
//     int     wall_top;
//     int     wall_ceil;
//     double  correct_distance;

//     i = 0;
//     for (int x = 0 ; x < WINDOW_HEIGHT ; x++) {
//     }
//     // wall_texture = (uint32_t *)malloc(sizeof(uint32_t) * (uint32_t)TEXTURE_WIDTH * (uint32_t)TEXTURE_HEIGHT);
//     // //=-----------------------------------------------=//
//     // for (int x = 0; x < TEXTURE_WIDTH; x++)
//     // {
//     //     for (int yt = 0; yt < TEXTURE_HEIGHT; yt++)
//     //             wall_texture[(TEXTURE_WIDTH * yt) + x] = 0xFF0000FF;
//     //         // if (x % 8 == 0 && yt % 8 == 0)
//     //         // {
//     //         //     // puts("s");
//     //         //     wall_texture[(TEXTURE_WIDTH * yt) + x] = 0xFF0000FF;
//     //         // }
//     //         // else
//     //         //     wall_texture[(TEXTURE_WIDTH * yt) + x] = 0xFF000000;
//     // }
//     while (i < NUM_OF_RAYS) {
//         correct_distance = config->rays[i].distance * cos(config->rays[i].ray_angle - config->player->rotation_angle);
//         distance_to_projection_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
//         projected_wall_height = (TILE / correct_distance) * distance_to_projection_plane;
//         wall_height = (int)projected_wall_height;
        
//         wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
//         wall_top = wall_top < 0 ? 0 : wall_top;
        
//         wall_ceil = (WINDOW_HEIGHT / 2) + (wall_height / 2);
//         wall_ceil = wall_ceil > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_ceil;

//         // Texture top ciel
//         // set the color of the floor
//         // for (int y = 0; y < wall_top; y++)
//         //     config->color_buffer[(WINDOW_WIDTH * y) + i] = 0xFF333333;
//         // //------------------------------//
//         // j = wall_top;
//         // // textureoffsetx = ;
//         // int textureoffsetx;
//         // if (config->rays[i].was_hit_vertical)
//         //     textureoffsetx = (int)config->rays[i].wall_hit_y % TILE;
//         // else 
//         //     textureoffsetx = (int)config->rays[i].wall_hit_x % TILE;
//         // while (j < wall_ceil) {
//         //     int top_distance = (j + (wall_height / 2) - (WINDOW_HEIGHT / 2)); 
//         //     int textureoffsety = top_distance * ((float)TEXTURE_HEIGHT / wall_height);
//         //     uint32_t texturecolor = wall_texture[(TEXTURE_WIDTH * textureoffsety) * textureoffsetx];
//         //     config->color_buffer[(WINDOW_WIDTH * j) + i] = texturecolor;//0xFF0000FF;
//         //     j++;
//         // }
//         j = wall_top;
//         while (j < wall_ceil) {
//             config->color_buffer[(WINDOW_WIDTH * j) + i] = 0xFF0000FF;
//             j++;
//         }

//         // set the color of the floor
//         for (int y = wall_ceil; y < WINDOW_HEIGHT; y++)
//             config->color_buffer[(WINDOW_WIDTH * y) + i] = 0xFF777777;
        
//         i++;
//     }
// }

void    render_3d(t_global_conf *config) {
    int     i;
    int     j;
    int     wall_height;
    double  distance_to_projection_plane;
    double  projected_wall_height;
    int     wall_top;
    int     wall_ceil;
    double  correct_distance;

    i = 0;
    for (int x = 0 ; x < WINDOW_HEIGHT ; x++) {
    }
    while (i < NUM_OF_RAYS) {
        correct_distance = config->rays[i].distance * cos(config->rays[i].ray_angle - config->player->rotation_angle);
        distance_to_projection_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
        projected_wall_height = (TILE / correct_distance) * distance_to_projection_plane;
        wall_height = (int)projected_wall_height;
        
        wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
        wall_top = wall_top < 0 ? 0 : wall_top;
        
        wall_ceil = (WINDOW_HEIGHT / 2) + (wall_height / 2);
        wall_ceil = wall_ceil > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_ceil;

        j = wall_top;
        while (j < wall_ceil) {
            config->color_buffer[(WINDOW_WIDTH * j) + i] = 0xFF6495ED;
            j++;
        }
        
        i++;
    }
}





void    init_color_buffer(t_global_conf *config) {

    int i;
    int j;

    i = 0;
    while (i < WINDOW_WIDTH) {
        j = 0;
        while (j < WINDOW_HEIGHT) {
            config->color_buffer[(WINDOW_WIDTH * j) + i] = 0xFFFFFFFF;
            j++;
        }
        i++;
    }

}

void    render_color_buffer(t_global_conf *config) {

    int i;
    int j;
    mlx_image_t *image;

    i = 0;
    image = mlx_new_image(config->mlx, WINDOW_WIDTH ,WINDOW_HEIGHT);
    // image->pixels = config->color_buffer;
    // for (int x = 0; x < WINDOW_WIDTH ; x++) {
    //     for (int u = 0 ; u < WINDOW_HEIGHT ; u++) {
    //         image->pixels[(WINDOW_WIDTH * x) + u] = 255;
    //     }
    // }
    // j = mlx_image_to_window(config->mlx, image, 0, 0);
    // if (j < 0) {
    //     printf("ERROR\n");
    //     exit(0);
    // }
    while (i < WINDOW_WIDTH) {
        j = 0;
        while (j < WINDOW_HEIGHT) {
            mlx_put_pixel(config->img, i, j, config->color_buffer[(WINDOW_WIDTH * j) + i]);
            j++;
        }
        i++;
    }

}




