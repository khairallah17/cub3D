#include "MLX42/include/MLX42/MLX42.h"
// #include <libc.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define WINDOW_HEIGHT MAP_NUM_ROWS * TILE
#define WINDOW_WIDTH MAP_NUM_COLS * TILE
#define TILE 32
#define PLAYER_TILE 8
#define NUM_OF_RAYS 320
#define FOV (60 * (M_PI / 180))

char map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    "11111111111111111111",
    "10000000000000000001",
    "10000000000000000001",
    "10001010101010101001",
    "10000000000000000001",
    "10000000000000001001",
    "10000000000N00001001",
    "10000000000000001001",
    "10000000000001111001",
    "10000000000000000001",
    "10000000000000000001",
    "10000000000000000001",
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
    int tile = TILE;
    while (i < tile) {
        int j = 0;
        while (j < tile) {
            mlx_put_pixel(config->img, (TILE * x) + i, (TILE * y) + j, color);
            j++;
        }
        i++;
    }

}

void    draw_single_line(t_global_conf *config) {

    double dx;
    double dy;
    double px;
    double py;
    double tmp;

    px = config->player->x * TILE;
    py = config->player->y * TILE;
    dx = (64 * cos(config->player->rotationAngle) + px); // assuming px and py are the (0, 0);
    dy = (64 * sin(config->player->rotationAngle) + py);

    double slope = (py - dy) / (px - dx);
    double y_intercept = py - slope * px; // py = slope * px + t_intercept

    if (px >= dx)
    {
        tmp = px;
        px = dx;
        dx = tmp;
    }
    while (px <= dx)
    {
        mlx_put_pixel(config->img,  px, slope * px + y_intercept, 0x008000FF);
        px +=0.1;
    }

}
void draw_rays(t_global_conf *config, int pos) {

    double dx;
    double dy;
    double px;
    double py;
    double tmp;

    px = floor(config->player->x * TILE);
    py = floor(config->player->y * TILE);
    dx = floor(config->rays[pos].wall_hit_x); // assuming px and py are the (0, 0);
    dy = floor(config->rays[pos].wall_hit_y);

    // puts("");
    // puts("");
    // puts("");

    // printf("RAY ==> (%f;%f)\n", floor(dx), floor(dy));
    // printf("PLAYER ==> (%f;%f)\n", floor(px), floor(py));

    // puts("");
    // puts("");
    // puts("");
    double slope = (py - dy) / (px - dx);
    double y_intercept = py - slope * px; // py = slope * px + t_intercept

    if (px >= dx)
    {
        tmp = px;
        px = dx;
        dx = tmp;
    }
    while (px <= dx)
    {
        mlx_put_pixel(config->img,  px, slope * px + y_intercept, 0x008000FF);
        px +=0.005;
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
    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) {
        return 1;
    }
    int mapGridIndexX = floor(x / TILE);
    int mapGridIndexY = floor(y / TILE);
    // printf("INTERSECTION INDEXES ==> (%f;%f)\n", floor(x/32), floor(y/32));
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

    puts("HORIZONTAL");
    puts("");

    y_inter = floor((config->player->y * TILE) / TILE) * TILE;
    printf("BEFORE ray[%d] ==> %f\n", pos, y_inter);
    printf("BEFORE ray[%d] ==> %f\n", pos, y_inter / 32);
    y_inter += is_ray_facing_down ? TILE : 0;

    printf("AFTER ray[%d] ==> %f\n", pos, y_inter);
    printf("AFTER ray[%d] ==> %f\n", pos, y_inter / 32);
    puts("");
    puts("");

    x_inter = (config->player->x * TILE) + ((y_inter - (config->player->y * TILE)) / tan(ray_angle));
    printf("BEFORE ray[%d] ==> %f\n", pos, x_inter);
    printf("AFTER ray[%d] ==> %f\n", pos, x_inter / 32);
    puts("");
    puts("");

    y_step = TILE;
    y_step *=is_ray_facing_up ? -1 : 1;

    x_step = TILE / tan(ray_angle);
    x_step *= (is_ray_facing_left && x_step > 0) ? -1 : 1;
    x_step *= (is_ray_facing_right && x_step < 0) ? -1 : 1;

    double next_horizontal_hit_x = x_inter;
    double next_horizontal_hit_y = y_inter;


    while ((next_horizontal_hit_x >= 0 && next_horizontal_hit_x <= WINDOW_WIDTH) && (next_horizontal_hit_y >= 0 && next_horizontal_hit_y <= WINDOW_HEIGHT)) {

        double x_check = next_horizontal_hit_x;
        double y_check = next_horizontal_hit_y + (is_ray_facing_up ? -1 : 0);

        if (wall_hit_checker(x_check, y_check)) {

            horizontal_wall_hit = 1;
            // printf("WALL FOUND AT ==> (%f,%f)!!\n", floor(next_horizontal_hit_x / TILE), floor(next_horizontal_hit_y / TILE));
            horizontal_wall_hit_x = next_horizontal_hit_x;
            horizontal_wall_hit_y = next_horizontal_hit_y;
            break;

        } else {
            next_horizontal_hit_x += x_step;
            next_horizontal_hit_y += y_step;
        }

    }

    puts("VERTICAL");
    puts("");

    int vertical_wall_hit = 0;
    double vertical_wall_hit_x;
    double vertical_wall_hit_y;

    x_inter = floor((config->player->x * TILE) / TILE) * TILE;
    printf("BEFORE ray[%d] ==> %f\n", pos, x_inter);
    printf("BEFORE ray[%d] ==> %f\n", pos, x_inter / 32);
    x_inter += is_ray_facing_right ? TILE : 0;

    printf("AFTER ray[%d] ==> %f\n", pos, y_inter);
    printf("AFTER ray[%d] ==> %f\n", pos, y_inter / 32);
    puts("");
    puts("");

    y_inter = (config->player->y * TILE) + (x_inter - (config->player->x * TILE)) * tan(ray_angle);

    printf("BEFORE ray[%d] ==> %f\n", pos, y_inter);
    printf("AFTER ray[%d] ==> %f\n", pos, y_inter / 32);
    puts("");
    puts("");

    x_step = TILE;
    x_step *= is_ray_facing_left ? -1 : 1;

    y_step = TILE * tan(ray_angle);
    y_step *= (is_ray_facing_up && y_step > 0) ? -1 : 1;
    y_step *= (is_ray_facing_down && y_step < 0) ? -1 : 1;

    double next_vertical_hit_x = x_inter;
    double next_vertical_hit_y = y_inter;


    while ((next_vertical_hit_x >= 0 && next_vertical_hit_x <= WINDOW_WIDTH) && (next_vertical_hit_y >= 0 && next_vertical_hit_y <= WINDOW_HEIGHT)) {

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

    double horizontal_distance = horizontal_wall_hit ? calculating_distance((config->player->x * TILE), (config->player->y * TILE), horizontal_wall_hit_x, horizontal_wall_hit_y) : INT_MAX;
    double vertical_distance = vertical_wall_hit ? calculating_distance((config->player->x * TILE), (config->player->y * TILE), vertical_wall_hit_x, vertical_wall_hit_y) : INT_MAX;

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
    double swp;
    int     i;

    ray_angle = config->player->rotationAngle - (FOV / 2);
    i = 0;
    // swp = config->player->x;
    // config->player->x = config->player->y;
    // config->player->y = swp;
    while (i < NUM_OF_RAYS) {
        cast_ray(config, ray_angle, i);
        draw_rays(config, i);
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
            mlx_put_pixel(config->img, (TILE * config->player->x)+i, (TILE * config->player->y)+j, config->player->color);
            mlx_put_pixel(config->img, (TILE * config->player->x)-i, (TILE * config->player->y)-j, config->player->color);
            mlx_put_pixel(config->img, (TILE * config->player->x)+i, (TILE * config->player->y)-j, config->player->color);
            mlx_put_pixel(config->img, (TILE * config->player->x)-i, (TILE * config->player->y)+j, config->player->color);
            j++;
        }
        i++;
    }
    // draw_single_line(config);
    cast_all_rays(config);
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

}

void update(t_global_conf *conf) {

    mlx_delete_image(conf->mlx, conf->img);
    conf->img = mlx_new_image(conf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    mlx_image_to_window(conf->mlx,conf->img,0,0);

    int i = 0;
    while (i < MAP_NUM_ROWS) {
        int j = 0;
        while (j < MAP_NUM_COLS) {
            if (map[i][j] == '1')
                draw(conf, j, i, 0xFFFFFF);
            else if (map[i][j] == '0')
                draw(conf, j, i, 0x000000);
            j++;
        }
        i++;
    }
    draw_player(conf);

}

void key_hook(mlx_key_data_t keydata, void *param)
{
    t_global_conf *conf;

    conf = param;
    if (keydata.key == MLX_KEY_LEFT)
        conf->player->rotationAngle += 0.1;
    else if (keydata.key == MLX_KEY_RIGHT)
        conf->player->rotationAngle -= 0.1;
    else if (keydata.key == MLX_KEY_W && conf->player->x > 0) {
        conf->player->x += 0.05 * cos(conf->player->rotationAngle);
        conf->player->y += 0.05 * sin(conf->player->rotationAngle);
    }
    else if (keydata.key == MLX_KEY_S && conf->player->x < MAP_NUM_ROWS) {
        conf->player->x -= 0.05 * cos(conf->player->rotationAngle);
        conf->player->y -= 0.05 * sin(conf->player->rotationAngle);
    }
    else if (keydata.key == MLX_KEY_A && conf->player->y > 0) {
        conf->player->x += 0.05 * cos(conf->player->rotationAngle + M_PI / 2);
        conf->player->y += 0.05 * sin(conf->player->rotationAngle + M_PI / 2);
    }
    else if (keydata.key == MLX_KEY_D && conf->player->y < MAP_NUM_COLS) {
        conf->player->x -= 0.05 * cos(conf->player->rotationAngle + M_PI / 2);
        conf->player->y -= 0.05 * sin(conf->player->rotationAngle + M_PI / 2);
    }
    update(conf);
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
            }
            j++;
        }
        i++;
    }
    draw_player(&conf);

    free(conf.rays);

    mlx_key_hook(conf.mlx, key_hook, &conf);
    mlx_loop(conf.mlx);
}