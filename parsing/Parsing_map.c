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
    while (str[i] && str[i] == 32)
        i++;
    return (i);
}

int index_end_path(char *str, int i)
{
    while(i >= 0 && str[i] == 32)
    {
        // puts("sss");
        i--;
    }
    // printf("i = %d\n", i);
    return (i);
}

char *search_path_texture(t_cub3d *cub)
{
    int first_index_path;
    int end_index_path;
    int fd;
    char *str;
    // int i = 0;

    first_index_path = index_first_path(cub->tmp_store, 2);
    end_index_path = index_end_path(cub->tmp_store, strlen(cub->tmp_store) - 2);
    // printf("first %d\n", first_index_path);
    // printf("end %d\n", end_index_path);
    // int i = (end_index_path - (first_index_path + 1));
    // printf("limit %d\n", i);
    str = ft_substr(cub->tmp_store, first_index_path, end_index_path - first_index_path + 1);
    if(!strnstr(str, ".xpm", strlen(str)) || strncmp(strnstr(str, ".xpm", strlen(str)), ".xpm", strlen(".xpm")))
    {
        printf("Error: Path missed .xpm at the end\n");
        exit(EXIT_FAILURE);
    }
    // else
    // {
    //     // puts(str);
    //     fd = open(str, O_RDWR);
    //     // printf("fd = %d\n", fd);
    //     if (fd == -1)
    //     {
    //         printf("Error: can't Open and read path Texture\n");
    //         exit(EXIT_FAILURE);
    //     }
    // }
    return (str);
}

char *check_color(t_cub3d *cub)//, int color)
{
    int first_index_color;
    int second_index_color;
    char *temp;

    first_index_color = index_first_path(cub->tmp_store, 1);
    // printf("index first => %d\n", first_index_color);
    second_index_color = index_end_path(cub->tmp_store, (strlen(cub->tmp_store) - 2)); //skipping "/0" + also first character and secend character space "F "
    // printf("index sec => %d\n", second_index_color);
    // printf("index sec => %d\n", (int)strlen(cub->tmp_store) - 1);
    temp = ft_substr(cub->tmp_store, first_index_color, second_index_color - first_index_color + 1);
    // printf("index last => %d\n", second_index_color - first_index_color + 1);
    printf("%s\n", temp);
    return(temp);
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
    parsing_int(cub);
    
    // return(cub);
}



int main(int ac, char **av)
{
    parsing(ac, av);
}
