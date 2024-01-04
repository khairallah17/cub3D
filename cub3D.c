#include "cub3D.h"
#include <stdlib.h>

void inf()
{
	system("leaks cub3D");
}
void draw(void *parp)
{
    t_cub3d *cub = parp;
	int i = 0;
	while (i < cub->prs_map.map.height)
		printf("%s", cub->prs_map.map.map_grid[i++]);
}

int main(int ac, char **av)
{
    t_cub3d *cub;
	atexit(inf);
    cub = parsing(ac, av);
    //check map
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
    // while(1);
}