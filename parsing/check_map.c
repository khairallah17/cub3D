/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:42:36 by eagoumi           #+#    #+#             */
/*   Updated: 2024/01/07 05:43:38 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_map_good_or_bad(t_cub3d *cub3d, int *i, int *j, int *nb_player)
{
	if (!ft_strchr("01NSWE ", cub3d->prs_map.map.map_grid[(*i)][(*j)]))
		send_err_free(cub3d, 0, "Error: Unexpected charachter in map");
	if (ft_strchr("NSWE", cub3d->prs_map.map.map_grid[(*i)][(*j)]))
	{
		cub3d->player.x_position = (*i) * TILE_SIZE; //set tile xposition
		cub3d->player.y_position = (*j) * TILE_SIZE; // set tile y position
		cub3d->player.player_compass = cub3d->prs_map.map.map_grid[(*i)][(*j)];
		if (cub3d->prs_map.map.map_grid[(*i)][(*j)] == 'N')
			cub3d->player.rotation = 3 * M_PI_2;
		else if (cub3d->prs_map.map.map_grid[(*i)][(*j)] == 'W')
			cub3d->player.rotation = M_PI;
		else if (cub3d->prs_map.map.map_grid[(*i)][(*j)] == 'S')
			cub3d->player.rotation = M_PI_2;
		else if (cub3d->prs_map.map.map_grid[(*i)][(*j)] == 'E')
			cub3d->player.rotation = 0;
		//count number of player
		(*nb_player)++;
	}
	else if ((((*i) == 0 || (*j) == 0 || (*i) == (cub3d->prs_map.map.height - 1) || (*j) == (cub3d->prs_map.map.width - 1)) 
				&& cub3d->prs_map.map.map_grid[(*i)][(*j)] != '1' && cub3d->prs_map.map.map_grid[(*i)][(*j)] != ' ')
				|| (cub3d->prs_map.map.map_grid[(*i)][(*j)] == '0' && ((cub3d->prs_map.map.map_grid[(*i) + 1][(*j)] && cub3d->prs_map.map.map_grid[(*i) + 1][(*j)] == ' ') 
				|| ((cub3d->prs_map.map.map_grid[(*i) - 1][(*j)] && cub3d->prs_map.map.map_grid[(*i) - 1][(*j)] == ' ') 
				|| (cub3d->prs_map.map.map_grid[(*i)][(*j) + 1] && cub3d->prs_map.map.map_grid[(*i)][(*j) + 1] == ' ') || (cub3d->prs_map.map.map_grid[(*i)][(*j) - 1] && cub3d->prs_map.map.map_grid[(*i)][(*j) - 1] == ' ')))))
		send_err_free(cub3d, 0, "Error: Map should Rounded by wall");
}

void	check_map(t_cub3d *cub)
{
	int	i;
	int	j;
	int	nb_player;

	i = 0;
	nb_player = 0;
	while (i < cub->prs_map.map.height)
	{
		j = 0;
		while (j < cub->prs_map.map.width)
		{
			check_map_good_or_bad(cub, &i, &j, &nb_player);
			j++;
		}
		i++;
	}
	if (nb_player == 0)
		send_err_free(cub, 0, "Error: Re-check please it \
						required the presence of the player");
	else if (nb_player > 1)
		send_err_free(cub, 0, "Error: Re-check please \
						there is too many player on the map");
}
