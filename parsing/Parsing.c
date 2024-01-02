#include "../Cub3D.h"

static void initial_param(t_cub3d *get_parm, char *path_map)
{
    // get_parm->prs_map.map.width = 0;
    // get_parm->prs_map.map.height = 0;
    get_parm->count_txtr_line = 0;
    get_parm->prs_map.f_c_color.floor = -1;
    get_parm->prs_map.f_c_color.ceiling = -1;
    get_parm->prs_map.texture.east = NULL;
    get_parm->prs_map.texture.north = NULL;
    get_parm->prs_map.texture.south = NULL;
    get_parm->prs_map.texture.west = NULL;
    get_parm->path_maps = strdup(path_map);
    get_parm->prs_map.f_c_color.tab_color = (int *)malloc(sizeof(int) * 3);
    get_parm->map_fd = open(get_parm->path_maps, O_RDONLY);
    // printf("%d\n", get_parm->map_fd);
}


static void    print_check_err(t_cub3d *cub, char *str)
{
    free(cub);
    cub = NULL;
    printf("%s\n", str);
    exit(EXIT_FAILURE);
}

void    send_err_free(t_cub3d *cub, int err_nbr, char *error_msg)
{
    if (err_nbr == -1)
        free(cub->tmp_store);
    free(cub->path_maps);
    if (cub->prs_map.texture.east != NULL)
        free(cub->prs_map.texture.east);
    if (cub->prs_map.texture.north != NULL)
        free(cub->prs_map.texture.north);
    if (cub->prs_map.texture.south != NULL)
        free(cub->prs_map.texture.south);
    if (cub->prs_map.texture.west != NULL)
        free(cub->prs_map.texture.west);
    print_check_err(cub, error_msg);
}

static void parse_texture(t_cub3d *cub)
{
    if (!strncmp(cub->tmp_store, "NO ", 3) && cub->prs_map.texture.north == NULL)
        cub->prs_map.texture.north = search_path_texture(cub);
    else if (!strncmp(cub->tmp_store, "SO ", 3) && cub->prs_map.texture.south == NULL)
        cub->prs_map.texture.south = search_path_texture(cub);
    else if (!strncmp(cub->tmp_store, "WE ", 3) && cub->prs_map.texture.west == NULL)
        cub->prs_map.texture.west = search_path_texture(cub);
    else if (!strncmp(cub->tmp_store, "EA ", 3) && cub->prs_map.texture.east == NULL)
        cub->prs_map.texture.east = search_path_texture(cub);
    else if (!strncmp(cub->tmp_store, "F ", 2) && cub->prs_map.f_c_color.floor == -1)
        cub->prs_map.f_c_color.floor = check_color(cub);
    else if (!strncmp(cub->tmp_store, "C ", 2) && cub->prs_map.f_c_color.ceiling == -1)
        cub->prs_map.f_c_color.ceiling = check_color(cub);
    else if ((!strncmp(cub->tmp_store, "NO ", 3) && cub->prs_map.texture.north != NULL)
            || (!strncmp(cub->tmp_store, "SO ", 3) && cub->prs_map.texture.south != NULL)
            || (!strncmp(cub->tmp_store, "WE ", 3) && cub->prs_map.texture.west != NULL)
            || (!strncmp(cub->tmp_store, "EA ", 3) && cub->prs_map.texture.east != NULL)
            || (!strncmp(cub->tmp_store, "F ", 2) && cub->prs_map.f_c_color.floor != -1)
            || (!strncmp(cub->tmp_store, "C ", 2) && cub->prs_map.f_c_color.ceiling != -1))
    {
        cub->error_parse_nb = 1;

    }
    else if (ft_strchr("01NSWE ", cub->tmp_store[0]))
        cub->error_parse_nb = -1;
    else
        cub->error_parse_nb = 2;
}

static void check_for_errors(int idx_line, int count_txtr, int err_nbr, t_cub3d *cub)
{
    printf("line idx = %d\n", idx_line);
    printf("numb_err = %d\n", err_nbr);
    if (idx_line == 0 || (cub->tmp_store == NULL && count_txtr == 0))
        send_err_free(cub, err_nbr, "ERROR: Empty Map file");
    else if (err_nbr == 1)
        send_err_free(cub, err_nbr, "ERROR: There is Diplicated Parameters Please Re-check");
    else if (err_nbr == 2)
        send_err_free(cub, err_nbr, "ERROR: Undifined");
    else if (count_txtr != 6)
        send_err_free(cub, err_nbr, "ERROR: Missing One or Multiples line parameter (NO,SO,WE,EA,F,C)");

}

int parsing_remove_new_line(t_cub3d *cub)
{
    // int count;
    int count_line;

    count_line = 0;
    cub->tmp_store = get_next_line(cub->map_fd);
    while(cub->tmp_store)
    {
        count_line++;
        if(!strncmp(cub->tmp_store, "\n", 1))
        {
            free(cub->tmp_store);
            cub->tmp_store = get_next_line(cub->map_fd);
            continue;
        }
        printf("%s", cub->tmp_store);
        parse_texture(cub);
        if(cub->error_parse_nb)
            break ;
        cub->tmp_store = get_next_line(cub->map_fd);
        // printf("%s", cub->tmp_store);
        // puts(cub->tmp_store);
    }
    printf("\ncouuunt = %d\n", cub->count_txtr_line);
    printf("\nerr_nb = %d\n", cub->error_parse_nb);
    check_for_errors(count_line, cub->count_txtr_line, cub->error_parse_nb, cub);
    return(count_line);
}

/*t_cub3d* */void   parsing(int ac, char **av)
{
    t_cub3d *cub;
    int count_line;

    check_arguments(ac, av);
    cub = (t_cub3d *)malloc(sizeof(t_cub3d));
    initial_param(cub, av[1]);
    count_line = parsing_remove_new_line(cub);
    
    // return(cub);
}



int main(int ac, char **av)
{
    parsing(ac, av);
// // int check_color(t_cub3d *cub, int color)
//     int t = heck_color(t_cub3d *cub, int color);
}
