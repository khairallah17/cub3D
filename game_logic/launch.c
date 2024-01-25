/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:38:38 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/25 18:49:05 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	launch(int ac, char **av)
{
	t_cub3d			*cub;
	t_global_conf	*config;

	cub = parsing(ac, av);
	config->color_buffer = cub;
}
