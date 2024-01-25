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

void    draw(t_global_conf *config, int x, int y, int color) {

    if (!config->img) {
        printf("NO IMAGE!!\n");
        exit(0);
    }

    int i = 0;
    int tile = MINIMAP_SCALE;
    while (i < tile) {
        int j = 0;
        while (j < tile) {
            mlx_put_pixel(config->img, (MINIMAP_SCALE * x) + i, (MINIMAP_SCALE * y) + j, color);
            j++;
        }
        i++;
    }

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
//         correct_distance = config->rays[i].distance * cos(config->rays[i].ray_angle - config->player->rotationAngle);
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
//         //     config->colorBuffer[(WINDOW_WIDTH * y) + i] = 0xFF333333;
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
//         //     config->colorBuffer[(WINDOW_WIDTH * j) + i] = texturecolor;//0xFF0000FF;
//         //     j++;
//         // }
//         j = wall_top;
//         while (j < wall_ceil) {
//             config->colorBuffer[(WINDOW_WIDTH * j) + i] = 0xFF0000FF;
//             j++;
//         }

//         // set the color of the floor
//         for (int y = wall_ceil; y < WINDOW_HEIGHT; y++)
//             config->colorBuffer[(WINDOW_WIDTH * y) + i] = 0xFF777777;
        
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
        correct_distance = config->rays[i].distance * cos(config->rays[i].ray_angle - config->player->rotationAngle);
        distance_to_projection_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
        projected_wall_height = (TILE / correct_distance) * distance_to_projection_plane;
        wall_height = (int)projected_wall_height;
        
        wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
        wall_top = wall_top < 0 ? 0 : wall_top;
        
        wall_ceil = (WINDOW_HEIGHT / 2) + (wall_height / 2);
        wall_ceil = wall_ceil > WINDOW_HEIGHT ? WINDOW_HEIGHT : wall_ceil;

        j = wall_top;
        while (j < wall_ceil) {
            config->colorBuffer[(WINDOW_WIDTH * j) + i] = 0xFF6495ED;
            j++;
        }
        
        i++;
    }
}

double  correct_angle(double ray_angle) {
    ray_angle = remainder(ray_angle, M_PI * 2);
    if (ray_angle < 0) {
        ray_angle += M_PI * 2;
    }
    return (ray_angle);
}

double  calculating_distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int wall_hit_checker(double x, double y) {
    if (x < 0 || (int)x >= MINIMAP_WIDTH || y < 0 || (int)y >= MINIMAP_HEIGHT) {
        return 1;
    }
    int mapGridIndexX = x / MINIMAP_SCALE;
    int mapGridIndexY = y / MINIMAP_SCALE;
    return map[mapGridIndexY][mapGridIndexX] == '1';
}


void    cast_all_rays(t_global_conf *config) {

    double ray_angle;
    int     i;

    ray_angle = config->player->rotationAngle - (FOV / 2);
    i = 0;
    // swp = config->player->x;
    // config->player->x = config->player->y;
    // config->player->y = swp;
    while (i < NUM_OF_RAYS) {
        cast_ray(config, ray_angle, i);
        // draw_rays(config, i);
        ray_angle += FOV / NUM_OF_RAYS;
        i++;
    }
}

void    draw_player(t_global_conf *config) {

    int i = 0;
    int tile = PLAYER_TILE / 2;
    while (i < tile) {
        int j = 0;
        while (j < tile) {
            mlx_put_pixel(config->img, (MINIMAP_SCALE * config->player->x)+i, (MINIMAP_SCALE * config->player->y)+j, config->player->color);
            mlx_put_pixel(config->img, (MINIMAP_SCALE * config->player->x)-i, (MINIMAP_SCALE * config->player->y)-j, config->player->color);
            mlx_put_pixel(config->img, (MINIMAP_SCALE * config->player->x)+i, (MINIMAP_SCALE * config->player->y)-j, config->player->color);
            mlx_put_pixel(config->img, (MINIMAP_SCALE * config->player->x)-i, (MINIMAP_SCALE * config->player->y)+j, config->player->color);
            j++;
        }
        i++;
    }
    // draw_single_line(config);
    cast_all_rays(config);
}


void    init_color_buffer(t_global_conf *config) {

    int i;
    int j;

    i = 0;
    while (i < WINDOW_WIDTH) {
        j = 0;
        while (j < WINDOW_HEIGHT) {
            config->colorBuffer[(WINDOW_WIDTH * j) + i] = 0xFFFFFFFF;
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
    // image->pixels = config->colorBuffer;
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
            mlx_put_pixel(config->img, i, j, config->colorBuffer[(WINDOW_WIDTH * j) + i]);
            j++;
        }
        i++;
    }

}

void setup(t_global_conf *config) {

    mlx_set_setting(MLX_MAXIMIZED, true);
	config->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "san andreas", false);
	if (!config->mlx)
		ft_error();

	config->img = mlx_new_image(config->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!config->img || (mlx_image_to_window(config->mlx, config->img, 0, 0) < 0))
		ft_error();

    config->player->rotationAngle = 0;
    config->player->color = 0xFF0000FF;
    config->rays = (t_ray *)malloc(sizeof(t_ray) * NUM_OF_RAYS);
    config->colorBuffer = (uint32_t *)malloc(sizeof(uint32_t) * (uint32_t)WINDOW_HEIGHT * (uint32_t)WINDOW_WIDTH);
    init_color_buffer(config);
}


void update(t_global_conf *conf) {

    mlx_delete_image(conf->mlx, conf->img);
    conf->img = mlx_new_image(conf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    mlx_image_to_window(conf->mlx,conf->img,0,0);

    int i = 0;
    render_3d(conf);
    render_color_buffer(conf);
    while (i < MAP_NUM_ROWS) {
        int j = 0;
        while (j < MAP_NUM_COLS) {
            if (map[i][j] == '1')
                draw(conf, j, i, 0xFFFFFF);
            else
                draw(conf, j, i, 0x000000);
            j++;
        }
        i++;
    }
    draw_player(conf);

}

int wall_collision(double x, double y) {
    if (x < 0 || (int)x >= MINIMAP_WIDTH || y < 0 || (int)y >= MINIMAP_HEIGHT) {
        return (0);
    }
    return (map[(int)(y)][(int)(x)] == '1');
}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_global_conf *conf;
    double  old_x;
    double  old_y;

    conf = param;
    old_x = conf->player->x;
    old_y = conf->player->y;
    if (keydata.key == MLX_KEY_LEFT)
        conf->player->rotationAngle -= 0.1;
    else if (keydata.key == MLX_KEY_RIGHT)
        conf->player->rotationAngle += 0.1;
    else if (keydata.key == MLX_KEY_W && conf->player->x > 0) {
        if (!wall_collision((conf->player->x + (0.1 * cos(conf->player->rotationAngle))), (conf->player->y + (0.1 * sin(conf->player->rotationAngle))))) {
            conf->player->x += 0.1 * cos(conf->player->rotationAngle);
            conf->player->y += 0.1 * sin(conf->player->rotationAngle);
        }
    }
    else if (keydata.key == MLX_KEY_S && conf->player->x < MAP_NUM_ROWS) {
        if (!wall_collision(conf->player->x - (0.1 * cos(conf->player->rotationAngle)), conf->player->y - (0.1 * sin(conf->player->rotationAngle)))) {
            conf->player->x -= 0.1 * cos(conf->player->rotationAngle);
            conf->player->y -= 0.1 * sin(conf->player->rotationAngle);
        }
    }
    else if (keydata.key == MLX_KEY_A && conf->player->y > 0) {
        if (!wall_collision(conf->player->x - (0.05 * cos(conf->player->rotationAngle + M_PI / 2)), conf->player->y - (0.05 * sin(conf->player->rotationAngle + M_PI / 2)))) {
            conf->player->x -= 0.05 * cos(conf->player->rotationAngle + M_PI / 2);
            conf->player->y -= 0.05 * sin(conf->player->rotationAngle + M_PI / 2);
        }
    }
    else if (keydata.key == MLX_KEY_D && conf->player->y < MAP_NUM_COLS) {
        if (!wall_collision(conf->player->x + (0.05 * cos(conf->player->rotationAngle + M_PI / 2)), conf->player->y + (0.05 * sin(conf->player->rotationAngle + M_PI / 2)))) {
            conf->player->x += 0.05 * cos(conf->player->rotationAngle + M_PI / 2);
            conf->player->y += 0.05 * sin(conf->player->rotationAngle + M_PI / 2);
        }
    }
    else if (keydata.key == MLX_KEY_ESCAPE) {
        mlx_delete_image(conf->mlx, conf->img);
        mlx_close_window(conf->mlx);
        free(conf->rays);
        free(conf->colorBuffer);
        return ;
    }
    update(conf);
}

void close_key_hook(void *param) {
    t_global_conf *conf;

    conf = param;
    mlx_delete_image(conf->mlx, conf->img);
    mlx_close_window(conf->mlx);
    free(conf->rays);
    free(conf->colorBuffer);
    return ;
}

int main () {

    t_global_conf   conf;
    t_player        player;
    mlx_t           *mlx;
    mlx_image_t     *img;

    img = NULL;
    mlx = NULL;

    conf.img = img;
    conf.mlx = mlx;
    conf.player = &player;

    setup(&conf);
    int i = 0;
    while (i < MAP_NUM_ROWS) {
        int j = 0;
        while (j < MAP_NUM_COLS) {
            if (map[i][j] == '1')
                draw(&conf, j, i, 0xFFFFFF);
            else if (map[i][j] == '0')
                draw(&conf, j, i, 0x000000);
            else if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S') {
                conf.player->x = j;
                conf.player->y = i;
                draw(&conf, j, i, 0x000000);
            }
            j++;
        }
        i++;
    }
    draw_player(&conf);
    render_3d(&conf);
    render_color_buffer(&conf);

    // free(conf.rays);

    mlx_key_hook(conf.mlx, key_hook, &conf);
    mlx_loop(conf.mlx);
    mlx_close_hook(conf.mlx, close_key_hook, &conf);
}