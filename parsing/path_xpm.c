#include "../Cub3D.h"


int index_first_path(char *str, int i)
{
    while (str[i] && str[i] == ' ')
        i++;
    return (i);
}

int index_end_path(char *str, int i)
{
    while(i >= 0 && str[i] == ' ')
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
    cub->count_txtr_line++;
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