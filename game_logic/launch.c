/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:38:38 by mkhairal          #+#    #+#             */
/*   Updated: 2024/02/07 22:51:52 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
