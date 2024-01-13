#include "MLX42/include/MLX42/MLX42.h"
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
// #include "Cub3D.h"
#define TILE 32
#define PLAYER_TILE 8
#define PI   3.14159f
#define TWO_PI 2*PI
#define FOV (60 * (PI / 180))
#define NUM_OF_RAYS 320
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define WINDOW_WIDTH (MAP_NUM_COLS * TILE)
#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE)
#define NUM_RAYS WINDOW_WIDTH
#define W 13
#define A 0
#define S 1
#define D 2
#define ARROW_RIGHT 124
#define ARROW_LEFT 123

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

typedef struct s_line {
    double  dx;
    double  dy;
    double  x;
    double  y;
} t_line;

typedef struct s_mlx_config {
    void    *mlx;
    void    *window;
} t_mlx_config;

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
    int     is_ray_facing_up;
    int     is_ray_facing_down;
    int     is_ray_facing_left;
    int     is_ray_facing_right;
} t_rays;

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

typedef struct s_global_conf {
    mlx_t           *mlx;
    mlx_image_t     *img;
    t_player        *player;
} t_global_conf;

t_rays rays[NUM_OF_RAYS];

void    draw_rays(t_global_conf *config, int i) {


    double slope = (config->player->y - rays[i].wall_hit_y) / (config->player->x - rays[i].wall_hit_x);
    double y_intercept = config->player->y - slope * config->player->x;
    double d = config->player->x  * TILE;
    while (++d < rays[i].wall_hit_x)
        mlx_put_pixel(config->img, ((slope * (d / TILE) + y_intercept) * TILE), d, 0x008000FF);


    // double dx, dy, xinc, yinc, steps, x, y;

    // dx = fabs((rays[i].wall_hit_x * TILE) - (config->player->x * TILE));
    // dy = fabs((rays[i].wall_hit_y * TILE) - (config->player->y * TILE));

    // steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    // xinc = dx / (double) steps;
    // yinc = dy / (double) steps;

    // x = config->player->x * TILE;
    // y = config->player->y * TILE;

    // for (int i = 0 ; i <= steps ; i++) {
    //     mlx_put_pixel(config->img, round(y), round(x), 0x008000FF);
    //     x += xinc;
    //     y += yinc;
    // }

}

double  correct_angle(double angle) {
    angle = remainder(angle, M_2_PI);
    if (angle < 0) {
        angle += M_2_PI;
    }
    return angle;
}

int     wall_checker(float pos_x, float pos_y) {
    if (pos_x < 0 || pos_x > WINDOW_WIDTH || pos_y < 0 || pos_y > WINDOW_HEIGHT) {
        return 1;
    }
    int mapGridIndexX = floor(pos_x / TILE);
    int mapGridIndexY = floor(pos_y / TILE);
    return map[mapGridIndexY][mapGridIndexX] != '0';
}

double calculating_distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 -x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void    cast_ray(double ray_angle, int pos, t_player *player) {

    int     ray_facing_down;
    int     ray_facing_up;
    int     ray_facing_right;
    int     ray_facing_left;
    double  x_inter;
    double  y_inter;
    double  x_step;
    double  y_step;
    int     horizontal_wall_hit;
    double  horizontal_wall_hit_x;
    double  horizontal_wall_hit_y;
    double  next_horizontal_wall_x;
    double  next_horizontal_wall_y;
    char    horizontal_wall_content;
    double  x_to_check;
    double  y_to_check;

    // CORRECT THE ANGLE 
    ray_angle = correct_angle(ray_angle);

    // GET THE PLAYER DIRECTION
    ray_facing_down = ray_angle > 0 && ray_angle < M_PI;
    ray_facing_up = !ray_facing_down;
    ray_facing_right = ray_angle < M_PI_2 || ray_angle > 1.5 * M_PI;
    ray_facing_left = !ray_facing_right;


    // TRACKING WALL HIT
    horizontal_wall_hit = 0;
    horizontal_wall_hit_x = 0;
    horizontal_wall_hit_y = 0;
    horizontal_wall_content = 0;

    // GET THE Y POSTIION OF THE FIRST HORIZONTAL GRID INTERSECTION
    y_inter = floor(player->y / TILE) * TILE;
    y_inter += ray_facing_down ? TILE : 0;

    // GET THE X POSITION OF THE FIRST HORIZONTAL GRID INTERSECTION
    x_inter = player->x + (y_inter - player->y) / tan(ray_angle);

    // CALCULATE Y STEP
    y_step = TILE;
    y_step *= ray_facing_up ? -1 : 1;

    // CALCULATE X  STEP
    x_step = TILE / tan(ray_angle);
    x_step *= (ray_facing_left && x_step > 0) ? -1 : 1;
    x_step *= (ray_facing_right && x_step < 0) ? -1 : 1;

    // NEXT HORIZONTAL INTERSECTIONS
    next_horizontal_wall_x = x_inter;
    next_horizontal_wall_y = y_inter;

    // CHECKING FOR WALL HIT HORIZONTAL X AND Y
    while ((next_horizontal_wall_x >= 0 && next_horizontal_wall_x <= WINDOW_WIDTH) && (next_horizontal_wall_y >= 0 && next_horizontal_wall_y <= WINDOW_HEIGHT)) {
        x_to_check = next_horizontal_wall_x;
        y_to_check = next_horizontal_wall_y + (ray_facing_up ? -1 : 0) ;

        // CHECK I THE RAY HITS A WALL
        if (wall_checker(x_to_check, y_to_check)) {
            horizontal_wall_hit = 1;
            horizontal_wall_content = '1';
            horizontal_wall_hit_x = next_horizontal_wall_x;
            horizontal_wall_hit_y = next_horizontal_wall_y;
            break;
        } else {
            next_horizontal_wall_x += x_step;
            next_horizontal_wall_y += y_step;
        }
    }

    // int     ray_facing_down;
    // int     ray_facing_up;
    // int     ray_facing_right;
    // int     ray_facing_left;
    // double  x_inter;
    // double  y_inter;
    // double  x_step;
    // double  y_step;
    int     vertical_wall_hit;
    double  vertical_wall_hit_x;
    double  vertical_wall_hit_y;
    double  next_vertical_wall_x;
    double  next_vertical_wall_y;
    char    vertical_wall_content;
    // double  x_to_check;
    // double  y_to_check;

    // GET THE PLAYER DIRECTION
    // ray_facing_down = ray_angle > 0 && ray_angle < PI;
    // ray_facing_up = !ray_facing_down;
    // ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
    // ray_facing_left = !ray_facing_right;

    // // CORRECT THE ANGLE 
    // ray_angle = correct_angle(ray_angle);

    // TRACKING WALL HIT
    vertical_wall_hit = 0;
    vertical_wall_hit_x = 0;
    vertical_wall_hit_y = 0;
    vertical_wall_content = 0;

    // GET THE X POSTIION OF THE FIRST vertical GRID INTERSECTION
    x_inter = floor(player->x / TILE) * TILE;
    x_inter = ray_facing_right ? TILE : 0;

    // GET THE Y POSITION OF THE FIRST vertical GRID INTERSECTION
    y_inter = player->y + (x_inter - player->x) * tan(ray_angle);

    // INCREMENTING Y AND X
    x_step = TILE;
    x_step *= ray_facing_left ? -1 : 1;
    
    y_step = TILE * tan(ray_angle);
    y_step *= (ray_facing_up && y_step > 0) ? -1 : 1;
    y_step *= (ray_facing_down && y_step < 0) ? -1 : 1;

    // NEXT vertical INTERSECTIONS
    next_vertical_wall_x = x_inter;
    next_vertical_wall_y = y_inter;

    // CHECKING FOR WALL HIT vertical X AND Y
    while ((next_vertical_wall_x >= 0 && next_vertical_wall_x <= WINDOW_WIDTH) && (next_vertical_wall_y >= 0 && next_vertical_wall_y <= WINDOW_HEIGHT)) {
        x_to_check = next_vertical_wall_x + (ray_facing_left ? -1 : 0);
        y_to_check = next_vertical_wall_y;

        // CHECK I THE RAY HITS A WALL
        if (wall_checker(x_to_check, y_to_check)) {
            vertical_wall_hit = 1;
            vertical_wall_content = '1';
            vertical_wall_hit_x = next_vertical_wall_x;
            vertical_wall_hit_y = next_vertical_wall_y;
            break;
        } else {
            next_vertical_wall_x += x_step;
            next_vertical_wall_y += y_step;
        }
    }

    //CALCULATE THE HORIZONTAL AND VERTICAL WALL HIT AND GET THE SMALLEST ONE
    double horizontal_distance = horizontal_wall_hit ? calculating_distance(player->x, player->y, horizontal_wall_hit_x, horizontal_wall_hit_y) : INT_MAX;
    double vertical_distance = vertical_wall_hit ? calculating_distance(player->x, player->y, vertical_wall_hit_x, vertical_wall_hit_y) : INT_MAX;

    if (vertical_distance < horizontal_distance) {
        rays[pos].distance = vertical_distance;
        rays[pos].wall_hit_x = vertical_wall_hit_x;
        rays[pos].wall_hit_y = vertical_wall_hit_y;
        rays[pos].was_hit_vertical = 1;
    } else {
        rays[pos].distance = horizontal_distance;
        rays[pos].wall_hit_x = horizontal_wall_hit_x;
        rays[pos].wall_hit_y = horizontal_wall_hit_y;
        rays[pos].was_hit_vertical = 0;
    }
    rays[pos].ray_angle = ray_angle;
    rays[pos].is_ray_facing_down = ray_facing_down;
    rays[pos].is_ray_facing_up = ray_facing_up;
    rays[pos].is_ray_facing_left = ray_facing_left;
    rays[pos].is_ray_facing_right = ray_facing_right;

}

void cast_rays(t_global_conf *config) {
    double ray_angle =  config->player->rotationAngle - (FOV / 2);

    printf("TAY CASTING\n");

    for( int i = 0 ; i < NUM_OF_RAYS ; i++) {
        cast_ray(ray_angle, i, config->player);
        draw_rays(config, i);
        ray_angle += FOV / NUM_OF_RAYS;
    }
}

void    draw(t_global_conf *config, int x, int y, int color) {

    if (!config->img) {
        printf("NO IMAGE!!\n");
        exit(0);
    }

    int i = 0;
    int tile = TILE;
    // printf("(%d;%d)\n",x,y);
    while (i < tile) {
        int j = 0;
        while (j < tile) {
            // printf("(i;j) ==> (%d;%d)\n",i,j);
            mlx_put_pixel(config->img, (TILE * x) + i, (TILE * y) + j, color);
            j++;
        }
        i++;
    }

}


void    draw_player(t_global_conf *config) {

    int i = 0;
    int tile = PLAYER_TILE;
    while (i < tile) {
        int j = 0;
        while (j < tile) {
            mlx_put_pixel(config->img, (TILE * config->player->y)+j, (TILE * config->player->x)+i, config->player->color);
            j++;
        }
        i++;
    }
    cast_rays(config);
    
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

void *key_hook(mlx_key_data_t keydata, void *param)
{
    t_global_conf *conf;

    conf = param;
    if (keydata.key == MLX_KEY_LEFT)
        conf->player->rotationAngle -= 0.1;
    else if (keydata.key == MLX_KEY_RIGHT)
        conf->player->rotationAngle += 0.1;
    else if (keydata.key == MLX_KEY_W && conf->player->x > 0)
        conf->player->x -= 0.05;
    else if (keydata.key == MLX_KEY_S && conf->player->x < MAP_NUM_ROWS)
        conf->player->x += 0.05;
    else if (keydata.key == MLX_KEY_A && conf->player->y > 0)
        conf->player->y -= 0.05;
    else if (keydata.key == MLX_KEY_D && conf->player->y < MAP_NUM_COLS)
        conf->player->y += 0.05;
    update(conf);
    return (NULL);
}

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}



int main (int ac, char *av[]) {
    // MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(800, 600, "san andreas", true);
	if (!mlx)
		ft_error();

	/* Do stuff */

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 800, 600);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();
    t_player player = {0};
    player.rotationAngle = PI;
    player.color = 0xFF0000FF;


    t_global_conf conf;
    conf.mlx = mlx;
    conf.player = &player;
    conf.img = img;

    int i = 0;
    while (i < MAP_NUM_ROWS) {
        int j = 0;
        while (j < MAP_NUM_COLS) {
            if (map[i][j] == '1')
                draw(&conf, j, i, 0xFFFFFF);
            else if (map[i][j] == '0')
                draw(&conf, j, i, 0x000000);
            else if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S') {
                printf("DRAWING PLAYER\n");
                player.x = i;
                player.y = j;
                draw_player(&conf);
            }
            j++;
        }
        i++;
    }
    // mlx_loop_hook(mlx, ft_hook, mlx);
    mlx_key_hook(conf.mlx, key_hook, &conf);
    mlx_loop(conf.mlx);
}