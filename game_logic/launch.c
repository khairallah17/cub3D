/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:38:38 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/04 23:45:35 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_mouse(void	*param)
{
	t_global_conf	*config;
	int				x;
	int				y;
	static	int		old_x;

	x = 0;
	y = 0;
	config = (t_global_conf *)param;
	mlx_get_mouse_pos(config->mlx, &x, &y);
	if (old_x != x)
	{
		config->player->rotation_angle += (old_x * (M_PI / 180.0)) / 20;
	}
	// mlx_get_mouse_pos(config->mlx, (WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2));
	mlx_set_cursor_mode(config->mlx, MLX_MOUSE_DISABLED);
	old_x = x;
	// static int	i;
	// int mouse_x;
	// int mouse_y = 0;
	// t_global_conf	*config;

	// (void)x;
	// (void)y;
	// config = param;
	// mlx_get_mouse_pos(config->mlx, &mouse_x, &mouse_y);
	// if (i++ == 0)
	// 	mouse_x = WINDOW_WIDTH / 2;
	// config->player->rotation_angle += (float)(mouse_x
	// 		- ((float)WINDOW_WIDTH / 2))
	// 	/ ((float)WINDOW_WIDTH / 2);
	// mlx_set_mouse_pos(config->mlx, (WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2));
}

void	launch(int ac, char **av)
{
	t_cub3d			*cub;
	t_global_conf	config;

	cub = parsing(ac, av);
	check_map(cub);
	config.player = (t_player *)malloc(sizeof(t_player));
	config.cub = cub;
	config.player = &cub->player;
	field_texture_path(&config);
	setup(&config);
	// draw_map(&config);
	update(&config);
	// mlx_set_cursor_mode(config.mlx, MLX_MOUSE_DISABLED);
	// mlx_cursor_hook(config.mlx, ft_mouse, &config);
	mlx_key_hook(config.mlx, &my_key_hook, &config);
	mlx_loop(config.mlx);
	mlx_terminate(config.mlx);
}
