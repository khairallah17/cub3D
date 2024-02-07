/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:38:38 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/07 21:47:17 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	ft_mouse(void	*param)
{
	t_global_conf	*config;
	int				x;
	int				y;
	static int		old_x;

	x = 0;
	y = 0;
	config = (t_global_conf *)param;
	mlx_get_mouse_pos(config->mlx, &x, &y);
	if (old_x != x)
	{
		getmap()->player_angle += (old_x * (M_PI / 180.0)) / 20;
	}
	mlx_set_cursor_mode(config->mlx, MLX_MOUSE_DISABLED);
	old_x = x;
}

void	launch(int ac, char **av)
{
	t_cub3d			*cub;
	t_global_conf	config;

	cub = cub3d_parsing(ac, av);
	config.cub = cub;
	field_texture_path(&config);
	setup(&config);
	update(&config);
	mlx_key_hook(config.mlx, &my_key_hook, &config);
	mlx_loop(config.mlx);
	mlx_terminate(config.mlx);
}
