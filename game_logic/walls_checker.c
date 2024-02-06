/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:50:36 by mkhairal          #+#    #+#             */
/*   Updated: 2024/01/28 18:23:47 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	wall_collision(t_global_conf *config, float x, float y)
{
	return ((map_get10(x, y) == '1') || (map_get10(x, y) == ' '));
}
