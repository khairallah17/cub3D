#include "../Cub3D.h"

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