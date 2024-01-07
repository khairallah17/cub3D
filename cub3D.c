/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 05:52:01 by eagoumi           #+#    #+#             */
/*   Updated: 2024/01/07 05:53:10 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdlib.h>

void	ft_free(t_cub3d *cub)
{
	int	i;

	i = 0;
	while (cub->prs_map.map.map_grid[i])
		free(cub->prs_map.map.map_grid[i++]);
	free(cub->prs_map.map.map_grid);
	free(cub->path_maps);
	if (cub->prs_map.texture.east != NULL)
		free(cub->prs_map.texture.east);
	if (cub->prs_map.texture.north != NULL)
		free(cub->prs_map.texture.north);
	if (cub->prs_map.texture.south != NULL)
		free(cub->prs_map.texture.south);
	if (cub->prs_map.texture.west != NULL)
		free(cub->prs_map.texture.west);
	free(cub);
}

void	inf(void)
{
	system("leaks cub3D");
}

void	draw(void *parp)
{
	t_cub3d	*cub;
	int		i;

	cub = parp;
	i = 0;
	while (i < cub->prs_map.map.height)
		printf("%s", cub->prs_map.map.map_grid[i++]);
}

int	main(int ac, char **av)
{
	t_cub3d	*cub;

	atexit(inf);
	cub = parsing(ac, av);
	printf("%p\n", cub);
	//check map
	check_map(cub);
	//mlx window
	if (!(cub->mlx.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", true)))
	{
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(cub->mlx.window = mlx_new_image(cub->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT)))
	{
		mlx_close_window(cub->mlx.mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(cub->mlx.mlx, cub->mlx.window, 0, 0) == -1)
	{
		mlx_close_window(cub->mlx.mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(cub->mlx.mlx, draw, cub);
	mlx_loop(cub->mlx.mlx);
	mlx_terminate(cub->mlx.mlx);
	ft_free(cub);
}
