/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:38:38 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/26 19:00:54 by mkhairal         ###   ########.fr       */
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
}
