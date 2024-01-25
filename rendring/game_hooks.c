/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:24:05 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/25 17:52:28 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
    t_global_conf *conf;

    conf = param;
    if (keydata.key == MLX_KEY_LEFT)
        conf->player->rotation_angle -= 0.1;
    else if (keydata.key == MLX_KEY_RIGHT)
        conf->player->rotation_angle += 0.1;
    else if (keydata.key == MLX_KEY_W && conf->player->x > 0) {
        if (!wall_collision((conf->player->x + (0.1 * cos(conf->player->rotation_angle))), (conf->player->y + (0.1 * sin(conf->player->rotation_angle))))) {
            conf->player->x += 0.1 * cos(conf->player->rotation_angle);
            conf->player->y += 0.1 * sin(conf->player->rotation_angle);
        }
    }
    else if (keydata.key == MLX_KEY_S && conf->player->x < MAP_NUM_ROWS) {
        if (!wall_collision(conf->player->x - (0.1 * cos(conf->player->rotation_angle)), conf->player->y - (0.1 * sin(conf->player->rotation_angle)))) {
            conf->player->x -= 0.1 * cos(conf->player->rotation_angle);
            conf->player->y -= 0.1 * sin(conf->player->rotation_angle);
        }
    }
    else if (keydata.key == MLX_KEY_A && conf->player->y > 0) {
        if (!wall_collision(conf->player->x - (0.05 * cos(conf->player->rotation_angle + M_PI / 2)), conf->player->y - (0.05 * sin(conf->player->rotation_angle + M_PI / 2)))) {
            conf->player->x -= 0.05 * cos(conf->player->rotation_angle + M_PI / 2);
            conf->player->y -= 0.05 * sin(conf->player->rotation_angle + M_PI / 2);
        }
    }
    else if (keydata.key == MLX_KEY_D && conf->player->y < MAP_NUM_COLS) {
        if (!wall_collision(conf->player->x + (0.05 * cos(conf->player->rotation_angle + M_PI / 2)), conf->player->y + (0.05 * sin(conf->player->rotation_angle + M_PI / 2)))) {
            conf->player->x += 0.05 * cos(conf->player->rotation_angle + M_PI / 2);
            conf->player->y += 0.05 * sin(conf->player->rotation_angle + M_PI / 2);
        }
    }
    else if (keydata.key == MLX_KEY_ESCAPE) {
        mlx_delete_image(conf->mlx, conf->img);
        mlx_close_window(conf->mlx);
        free(conf->rays);
        free(conf->color_buffer);
        return ;
    }
    update(conf);
}