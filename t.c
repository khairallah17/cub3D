#include <mlx.h>
#include <limits.h>
#include <math.h>
#include "Cub3D.h"
#define TILE 32
#define PLAYER_TILE 8
#define PI   3.14159f
#define TWO_PI PI*PI
#define FOV (60 * (PI / 180))
#define NUM_OF_RAYS 160
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20
#define WINDOW_WIDTH (MAP_NUM_COLS * TILE)
#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE)
#define NUM_RAYS WINDOW_WIDTH

char map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    "11111111111111111111",
    "10000000000000000001",
    "10000000000000000001",
    "10001010101010101001",
    "10000000000000000001",
    "10000000000000001001",
    "10000000000000001001",
    "10000000000000001001",
    "10000000000001111001",
    "100000N0000000000001",
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

t_rays rays[NUM_OF_RAYS];

void    draw_rays(t_mlx_config *config, t_player *player) {

    for (int i = 0 ; i < NUM_OF_RAYS ; i++) {
        //printf("(%f;%f)\n", (rays[i].wall_hit_x + player->x * TILE) , (rays[i].wall_hit_y + player->y * TILE)  );
        double slope = (player->x - rays[i].wall_hit_x) / (player->y - rays[i].wall_hit_y);
        double y_intercept = player->y - slope * player->x;
        double d = -1;
        while (++d < player->x * TILE)
            mlx_pixel_put(config->mlx, config->window, d, ((slope * (d / TILE) + y_intercept) * TILE)  , 0x008000);
    }

}

double  correct_angle(double angle) {
    if (angle < 0) {
        angle = remainder(angle, TWO_PI);
    }
    return angle;
}

int     wall_checker(float pos_x, float pos_y) {
    if (pos_x < 0 || pos_x > WINDOW_WIDTH || pos_y < 0 || pos_y > WINDOW_HEIGHT) {
        return TRUE;
    }
    int mapGridIndexX = floor(pos_x / TILE);
    int mapGridIndexY = floor(pos_y / TILE);
    return map[mapGridIndexY][mapGridIndexX] != 0;
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

    // GET THE PLAYER DIRECTION
    ray_facing_down = ray_angle > 0 && ray_angle < PI;
    ray_facing_up = !ray_facing_down;
    ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
    ray_facing_left = !ray_facing_right;

    // CORRECT THE ANGLE 
    ray_angle = correct_angle(ray_angle);

    // TRACKING WALL HIT
    horizontal_wall_hit = 0;
    horizontal_wall_hit_x = 0;
    horizontal_wall_hit_y = 0;
    horizontal_wall_content = 0;

    // GET THE Y POSTIION OF THE FIRST HORIZONTAL GRID INTERSECTION
    y_inter = floor(player->y / TILE) * TILE;
    y_inter = ray_facing_down ? TILE : 0;

    // GET THE X POSITION OF THE FIRST HORIZONTAL GRID INTERSECTION
    x_inter = player->x + (y_inter - player->y) / tan(ray_angle);

    // INCREMENTING Y AND X
    x_step = TILE;
    x_step = ray_facing_down ? TILE * -1 : TILE;
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

void cast_rays(t_player *player, t_mlx_config *config) {
    double ray_angle =  player->rotationAngle - (FOV / 2);

    printf("TAY CASTING\n");

    for( int i = 0 ; i < NUM_OF_RAYS ; i++) {
        cast_ray(ray_angle, i, player);
        draw_rays(config, player);
        ray_angle += FOV / NUM_OF_RAYS;
    }
}

void    draw(t_mlx_config *config, int x, int y, int color) {

    if (!config->mlx || !config->window)
        return ;
    
    int i = 0;
    int tile = TILE;
    while (i < tile) {
        int j = 0;
        while (j < tile) {
            mlx_pixel_put(config->mlx, config->window, (TILE * x)+i, (TILE * y)+j, color);
            j++;
        }
        i++;
    }
}

void    draw_player(t_mlx_config *config, t_player *player) {
    if (!config->mlx || !config->window)
        return ;
    
    int i = 0;
    int tile = PLAYER_TILE;
    while (i < tile) {
        int j = 0;
        while (j < tile) {
            mlx_pixel_put(config->mlx, config->window, (TILE * player->x)+i, (TILE * player->y)+j, player->color);
            j++;
        }
        i++;
    }
    cast_rays(player, config);
}

int main (int ac, char *av[]) {
    t_mlx_config config;

    config.mlx = mlx_init();
    t_player player = {0};
    player.rotationAngle = PI / 2;
    player.color = 0xFF0000;

    // map.map_grid = m;
    config.window = mlx_new_window(config.mlx, WINDOW_HEIGHT, WINDOW_WIDTH, "san andreas");

    int i = 0;
    while (i < MAP_NUM_ROWS) {
        int j = 0;
        while (j < MAP_NUM_COLS) {
            if (map[i][j] == '1')
                draw(&config, i, j, 0xFFFFFF);
            else if (map[i][j] == '0')
                draw(&config, i, j, 0x000000);
            else if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S') {
                printf("DRAWING PLAYER\n");
                player.x = i;
                player.y = j;
                draw_player(&config, &player);
            }
            j++;
        }
        i++;
    }

    mlx_loop(config.mlx);
}