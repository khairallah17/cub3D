/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:38:38 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/29 01:53:10 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	launch(int ac, char **av)
{
	t_cub3d			*cub;
	t_global_conf	config;

	cub = parsing(ac, av);
	check_map(cub);
	config.player = (t_player *)malloc(sizeof(t_player));
	config.cub = cub;
	setup(&config);
	render_3d(&config);
	mlx_key_hook(config.mlx, &my_key_hook, &config);
	mlx_loop(config.mlx);
	mlx_terminate(config.mlx);
}
