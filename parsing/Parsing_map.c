#include "../Cub3D.h"

void    check_arguments(int ac, char **av)
{
    if (ac == 1)
    {
        write(2, "Error: Check please should be exact <EXECUTABLE> + <MAP_NAME.CUB>\n", 67);
        exit (EXIT_FAILURE);
    }
    else if (ac > 2)
    {
        write(2, "Error: There is too many arguments please re-check with <EXECUTABLE> + <MAP_NAME.CUB>\n", 87);
        exit (EXIT_FAILURE);
    }
    else if (ac == 2 && (!strnstr(av[1], ".cub", strlen(av[1])) || strncmp(strnstr(av[1], ".cub", strlen(av[1])), ".cub", 5)))
    {
        write(2, "Error: In Map Reading it should be <MAP_NAME.CUB>\n", 52);
        exit (EXIT_FAILURE);
    }
}

static void initial_param(t_cub *get_parm) // char *path_map)
{
    get_parm->prs_map.map.width = 0;
    get_parm->prs_map.map.height = 0;
    // get_parm->prs_map.f_c_color.floor = -1;
    // get_parm->prs_map.f_c_color.ceiling = -1;
    // get_parm->path_maps = strdup();
    // get_parm->map_fd = open(get_parm->path_maps, O_RDONLY);
}

int main(int ac, char **av)
{
    check_arguments(ac, av);
}
