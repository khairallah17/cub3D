#include "MLX42/include/MLX42/MLX42.h"
// #include <libc.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define WINDOW_HEIGHT 768 
#define WINDOW_WIDTH 1024
#define TILE 8
#define PLAYER_TILE 8
#define NUM_OF_RAYS WINDOW_WIDTH
#define RAYS 60
#define FOV (60 * (M_PI / 180))
#define MINIMAP_SCALE 10
#define MINIMAP_HEIGHT MAP_NUM_ROWS * MINIMAP_SCALE
#define MINIMAP_WIDTH MAP_NUM_COLS * MINIMAP_SCALE

char map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    "11111111111111111111",
    "10000000000000000001",
    "10000000000000000001",
    "10001010101010101001",
    "10000000000000000001",
    "10000000000000001001",
    "10000000000000010001",
    "10000000000000001001",
    "10000000000001111001",
    "10000000000000000001",
    "10000000000000000001",
    "1000000000N000000001",
    "11111111111111111111"
};

typedef struct s_player {
    double  x;
    double  y;
    int     speed;
    int     direction;
    double  rotationAngle;
    double  rotationSpeed;
    int     color;
}   t_player;

typedef struct s_ray {
    double  ray_angle;
    double  wall_hit_x;
    double  wall_hit_y;
    double  distance;
    int     was_hit_vertical;
    int     ray_facing_up;
    int     ray_facing_down;
    int     ray_facing_left;
    int     ray_facing_right;
} t_ray;

typedef struct s_global_conf {
    mlx_t           *mlx;
    mlx_image_t     *img;
    t_player        *player;
    t_ray           *rays;
    uint32_t        *colorBuffer;
} t_global_conf;

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

        for (int y = 0; y < wall_top; y++)
            config->colorBuffer[(WINDOW_WIDTH * y) + i] = 0xFF333333;

        j = wall_top;
        while (j < wall_ceil) {
            config->colorBuffer[(WINDOW_WIDTH * j) + i] = 0xFF0000FF;
            j++;
        }

        // set the color of the floor
        for (int y = wall_ceil; y < WINDOW_HEIGHT; y++)
            config->colorBuffer[(WINDOW_WIDTH * y) + i] = 0xFF777777;
        
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
    if (x < 0 || x > MINIMAP_WIDTH || y < 0 || y > MINIMAP_HEIGHT) {
        return 1;
    }
    int mapGridIndexX = floor(x / MINIMAP_SCALE);
    int mapGridIndexY = floor(y / MINIMAP_SCALE);
    // printf("MAPGRID [%d][%d]\n", mapGridIndexX, mapGridIndexY);
    return map[mapGridIndexY][mapGridIndexX] == '1';
}

void    cast_ray(t_global_conf *config, double ray_angle, int pos) {

    ray_angle = correct_angle(ray_angle);

    int is_ray_facing_down = ray_angle > 0  && ray_angle < M_PI;
    int is_ray_facing_up = !is_ray_facing_down;
    int is_ray_facing_right = ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI;
    int is_ray_facing_left = !is_ray_facing_right;

    double x_inter;
    double y_inter;
    double x_step;
    double y_step;

    int horizontal_wall_hit = 0;
    double horizontal_wall_hit_x;
    double horizontal_wall_hit_y;

    // puts("HORIZONTAL");
    // puts("");

    y_inter = floor((config->player->y * MINIMAP_SCALE) / MINIMAP_SCALE) * MINIMAP_SCALE;
    // printf("BEFORE ray[%d] ==> %f\n", pos, y_inter);
    // printf("BEFORE ray[%d] ==> %f\n", pos, y_inter / 32);
    y_inter += is_ray_facing_down ? MINIMAP_SCALE : 0;

    // printf("AFTER ray[%d] ==> %f\n", pos, y_inter);
    // printf("AFTER ray[%d] ==> %f\n", pos, y_inter / 32);
    // puts("");
    // puts("");

    x_inter = (config->player->x * MINIMAP_SCALE) + ((y_inter - (config->player->y * MINIMAP_SCALE)) / tan(ray_angle));
    // printf("BEFORE ray[%d] ==> %f\n", pos, x_inter);
    // printf("AFTER ray[%d] ==> %f\n", pos, x_inter / 32);
    // puts("");
    // puts("");

    y_step = MINIMAP_SCALE;
    y_step *=is_ray_facing_up ? -1 : 1;

    x_step = MINIMAP_SCALE / tan(ray_angle);
    x_step *= (is_ray_facing_left && x_step > 0) ? -1 : 1;
    x_step *= (is_ray_facing_right && x_step < 0) ? -1 : 1;

    double next_horizontal_hit_x = x_inter;
    double next_horizontal_hit_y = y_inter;


    while ((next_horizontal_hit_x >= 0 && next_horizontal_hit_x <= MINIMAP_WIDTH) && (next_horizontal_hit_y >= 0 && next_horizontal_hit_y <= MINIMAP_HEIGHT)) {

        double x_check = next_horizontal_hit_x;
        double y_check = next_horizontal_hit_y + (is_ray_facing_up ? -1 : 0);

        if (wall_hit_checker(x_check, y_check)) {

            horizontal_wall_hit = 1;
            // printf("WALL FOUND AT ==> (%f,%f)!!\n", floor(next_horizontal_hit_x / MINIMAP_SCALE), floor(next_horizontal_hit_y / MINIMAP_SCALE));
            horizontal_wall_hit_x = next_horizontal_hit_x;
            horizontal_wall_hit_y = next_horizontal_hit_y;
            break;

        } else {
            next_horizontal_hit_x += x_step;
            next_horizontal_hit_y += y_step;
        }

    }

    // puts("VERTICAL");
    // puts("");

    int vertical_wall_hit = 0;
    double vertical_wall_hit_x;
    double vertical_wall_hit_y;

    x_inter = floor((config->player->x * MINIMAP_SCALE) / MINIMAP_SCALE) * MINIMAP_SCALE;
    // printf("BEFORE ray[%d] ==> %f\n", pos, x_inter);
    // printf("BEFORE ray[%d] ==> %f\n", pos, x_inter / 32);
    x_inter += is_ray_facing_right ? MINIMAP_SCALE : 0;

    // printf("AFTER ray[%d] ==> %f\n", pos, y_inter);
    // printf("AFTER ray[%d] ==> %f\n", pos, y_inter / 32);
    // puts("");
    // puts("");

    y_inter = (config->player->y * MINIMAP_SCALE) + (x_inter - (config->player->x * MINIMAP_SCALE)) * tan(ray_angle);

    // printf("BEFORE ray[%d] ==> %f\n", pos, y_inter);
    // printf("AFTER ray[%d] ==> %f\n", pos, y_inter / 32);
    // puts("");
    // puts("");

    x_step = MINIMAP_SCALE;
    x_step *= is_ray_facing_left ? -1 : 1;

    y_step = MINIMAP_SCALE * tan(ray_angle);
    y_step *= (is_ray_facing_up && y_step > 0) ? -1 : 1;
    y_step *= (is_ray_facing_down && y_step < 0) ? -1 : 1;

    double next_vertical_hit_x = x_inter;
    double next_vertical_hit_y = y_inter;


    while ((next_vertical_hit_x >= 0 && next_vertical_hit_x <= (MINIMAP_WIDTH)) && (next_vertical_hit_y >= 0 && next_vertical_hit_y <= MINIMAP_HEIGHT)) {

        double x_check = next_vertical_hit_x + (is_ray_facing_left ? -1 : 0);
        double y_check = next_vertical_hit_y;

        if (wall_hit_checker(x_check, y_check)) {

            vertical_wall_hit = 1;
            vertical_wall_hit_x = next_vertical_hit_x;
            vertical_wall_hit_y = next_vertical_hit_y;
            break;

        } else {
            next_vertical_hit_x += x_step;
            next_vertical_hit_y += y_step;
        }

    }

    double horizontal_distance = horizontal_wall_hit ? calculating_distance((config->player->x * MINIMAP_SCALE), (config->player->y * MINIMAP_SCALE), horizontal_wall_hit_x, horizontal_wall_hit_y) : INT_MAX;
    double vertical_distance = vertical_wall_hit ? calculating_distance((config->player->x * MINIMAP_SCALE), (config->player->y * MINIMAP_SCALE), vertical_wall_hit_x, vertical_wall_hit_y) : INT_MAX;

    if (vertical_distance < horizontal_distance) {
        config->rays[pos].distance = vertical_distance;
        config->rays[pos].wall_hit_x = vertical_wall_hit_x;
        config->rays[pos].wall_hit_y = vertical_wall_hit_y;
        config->rays[pos].was_hit_vertical = 1;
    } else {
        config->rays[pos].distance = horizontal_distance;
        config->rays[pos].wall_hit_x = horizontal_wall_hit_x;
        config->rays[pos].wall_hit_y = horizontal_wall_hit_y;
        config->rays[pos].was_hit_vertical = 0;
    }
    config->rays[pos].ray_angle = ray_angle;
    config->rays[pos].ray_facing_down = is_ray_facing_down;
    config->rays[pos].ray_facing_up = is_ray_facing_up;
    config->rays[pos].ray_facing_left = is_ray_facing_left;
    config->rays[pos].ray_facing_right = is_ray_facing_right;
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

    // printf("WALL COLLISTION AT ==> [%d][%d]\n", (int)(y/MINIMAP_SCALE),(int)(x/MINIMAP_SCALE));
    // printf("AT ==> %c\n", map[(int)(y/MINIMAP_SCALE)][(int)(x/MINIMAP_SCALE)]);
    if (map[(int)(x/MINIMAP_SCALE)][(int)(y/MINIMAP_SCALE)] == '1')
        return (0);
    return (1);
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
        // if (wall_collision((conf->player->x + 0.1 * cos(conf->player->rotationAngle)), (conf->player->y + 0.1 * sin(conf->player->rotationAngle)))) {
            conf->player->x += 0.1 * cos(conf->player->rotationAngle);
            conf->player->y += 0.1 * sin(conf->player->rotationAngle);
        // }
    }
    else if (keydata.key == MLX_KEY_S && conf->player->x < MAP_NUM_ROWS) {
        conf->player->x -= 0.1 * cos(conf->player->rotationAngle);
        conf->player->y -= 0.1 * sin(conf->player->rotationAngle);
    }
    else if (keydata.key == MLX_KEY_A && conf->player->y > 0) {
        conf->player->x -= 0.05 * cos(conf->player->rotationAngle + M_PI / 2);
        conf->player->y -= 0.05 * sin(conf->player->rotationAngle + M_PI / 2);
    }
    else if (keydata.key == MLX_KEY_D && conf->player->y < MAP_NUM_COLS) {
        conf->player->x += 0.05 * cos(conf->player->rotationAngle + M_PI / 2);
        conf->player->y += 0.05 * sin(conf->player->rotationAngle + M_PI / 2);
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