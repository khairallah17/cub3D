#include "../Cub3D.h"

void    check_arguments(int ac, char **av)
{
    int fd;

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
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Error: Check please for map (Unable to open map file)");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

static void initial_param(t_cub3d *get_parm, char *path_map)
{
    // get_parm->prs_map.map.width = 0;
    // get_parm->prs_map.map.height = 0;
    get_parm->prs_map.f_c_color.floor = -1;
    get_parm->prs_map.f_c_color.ceiling = -1;
    get_parm->prs_map.texture.east = NULL;
    get_parm->prs_map.texture.north = NULL;
    get_parm->prs_map.texture.south = NULL;
    get_parm->prs_map.texture.west = NULL;
    get_parm->path_maps = strdup(path_map);
    get_parm->map_fd = open(get_parm->path_maps, O_RDONLY);
    // printf("%d\n", get_parm->map_fd);
}

int index_first_path(char *str, int i)
{
    while (str[i] && (str[i] = ' '))
        i++;
    return (i);
}

int index_end_path(char *str, int i)
{
    while (i > 0 && str[i] == ' ')
        i--;
    return (i);
}

// char *search_path_texture(t_cub3d *cub)
// {
//     int first_index_path;
//     int end_index_path;
//     char *str;

//     first_index_path = index_first_path(cub->tmp_store, 2);
//     end_index_path = index_end_path(cub->tmp_store, strlen(cub->tmp_store));
//     str = 

// }

static void parse_texture(t_cub3d *cub)
{
    if (!strncmp(cub->tmp_store, "NO ", 3) && cub->prs_map.texture.north == NULL)
        puts("NO here"); //function to check texture path
    else if (!strncmp(cub->tmp_store, "SO ", 3) && cub->prs_map.texture.south == NULL)
        puts("SO here"); //function to check texture path
    else if (!strncmp(cub->tmp_store, "WE ", 3) && cub->prs_map.texture.west == NULL)
        puts("WE here"); //function to check texture path
    else if (!strncmp(cub->tmp_store, "EA ", 3) && cub->prs_map.texture.east == NULL)
        puts("EA here"); //function to check texture path
    else if (!strncmp(cub->tmp_store, "F ", 2) && cub->prs_map.f_c_color.floor == -1)
        puts("F here"); //function to check texture path
    else if (!strncmp(cub->tmp_store, "C ", 2) && cub->prs_map.f_c_color.ceiling == -1)
        puts("C here"); //function to check texture path
}


int parsing_int(t_cub3d *cub)
{
    // int count;

    cub->tmp_store = get_next_line(cub->map_fd);
    while(cub->tmp_store)
    {
        if(!strncmp(cub->tmp_store, "\n", 1))
        {
            free(cub->tmp_store);
            cub->tmp_store = get_next_line(cub->map_fd);
            // cub->tmp_store = NULL;
            continue;
        }
        printf("%s", cub->tmp_store);
        parse_texture(cub);
        cub->tmp_store = get_next_line(cub->map_fd);
        // puts(cub->tmp_store);
    }
    return(0);
}

/*t_cub3d* */void   parsing(int ac, char **av)
{
    t_cub3d *cub;

    check_arguments(ac, av);
    cub = (t_cub3d *)malloc(sizeof(t_cub3d));
    initial_param(cub, av[1]);
    parsing_int(cub);
    
    // return(cub);
}



int main(int ac, char **av)
{
    parsing(ac, av);
}
