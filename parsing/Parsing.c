#include "../Cub3D.h"

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

static void parse_texture(t_cub3d *cub)
{
    if (!strncmp(cub->tmp_store, "NO ", 3) && cub->prs_map.texture.north == NULL)
    {
        cub->tmp_store = search_path_texture(cub);
        // printf("%s\n", cub->tmp_store);
    }
        // puts("NO here"); //function to check texture path
    else if (!strncmp(cub->tmp_store, "SO ", 3) && cub->prs_map.texture.south == NULL)
    {
        cub->tmp_store = search_path_texture(cub);
    }
        // puts("SO here"); //function to check texture path
    else if (!strncmp(cub->tmp_store, "WE ", 3) && cub->prs_map.texture.west == NULL)
    {
        cub->tmp_store = search_path_texture(cub);
    }
        // puts("WE here"); //function to check texture path
    else if (!strncmp(cub->tmp_store, "EA ", 3) && cub->prs_map.texture.east == NULL)
    {
        cub->tmp_store = search_path_texture(cub);
    }
        // puts("EA here"); //function to check texture path
    else if (!strncmp(cub->tmp_store, "F ", 2) && cub->prs_map.f_c_color.floor == -1)
    {
        cub->tmp_store = check_color(cub);
        // printf("%s", cub->tmp_store);
    }
        // puts("F here"); //function to check texture path
    else if (!strncmp(cub->tmp_store, "C ", 2) && cub->prs_map.f_c_color.ceiling == -1)
    {
        cub->tmp_store = check_color(cub);
        // cub->tmp_store = search_path_texture(cub);
    }
        // puts("C here"); //function to check texture path
}

int parsing_remove_new_line(t_cub3d *cub)
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
        // printf("%s", cub->tmp_store);
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
    parsing_remove_new_line(cub);
    
    // return(cub);
}



int main(int ac, char **av)
{
    parsing(ac, av);
}
