#include "../cub3D.h"

void    check_map(t_cub3d *cub)
{
    int i;
    int j;
    int nb_player;

    i = 0;
    while (i < cub->prs_map.map.height)
    {
        j = 0;
        while (j < cub->prs_map.map.width)
        {
            if (!ft_strchr("01NSWE ", cub->prs_map.map.map_grid[i][j]))
                send_err_free(cub, 0, "Error: Unexpected charachter in map");
            if (ft_strchr("NSWE", cub->prs_map.map.map_grid[i][j]))
            {
                //set player position
                
            }
            else if (((i == 0 || j == 0 || i == (cub->prs_map.map.height - 1) || j == (cub->prs_map.map.width - 1)) 
                        && cub->prs_map.map.map_grid[i][j] != '1' && cub->prs_map.map.map_grid[i][j] != ' ')
                        || (cub->prs_map.map.map_grid[i][j] == '0' && ((cub->prs_map.map.map_grid[i + 1][j] && cub->prs_map.map.map_grid[i + 1][j] == ' ') 
                        || ((cub->prs_map.map.map_grid[i - 1][j] && cub->prs_map.map.map_grid[i - 1][j] == ' ') 
                        || (cub->prs_map.map.map_grid[i][j + 1] && cub->prs_map.map.map_grid[i][j + 1] == ' ') || (cub->prs_map.map.map_grid[i][j - 1] && cub->prs_map.map.map_grid[i][j - 1] == ' ')))))
                send_err_free(cub, 0, "Error: Map should Rounded by wall");
            j++;
        }
        i++;
    }
}