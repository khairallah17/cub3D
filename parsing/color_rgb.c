#include "../Cub3D.h"

void parsing_rgb_proba(char *temp, int i, int count_cama)
{
    while (temp[i])
    {
        if (temp[i] == ',')
            count_cama++;
        if (temp[i] == ',' && (temp[i+1] == ',' || temp[i+1] == ' ' || temp[i-1] == ' '))
        {
            printf("ERROR: There an error on parsing color RGB\n");
            exit(EXIT_FAILURE);
        }
        else if (count_cama >= 3 || temp[0] == ',' || temp[strlen(temp) - 1] == ',')
        {
            printf("ERROR: There an error on parsing There is Problem with ','\n");
            exit(EXIT_FAILURE);
        }
        else if (temp[i] == ' ')
        {
            printf("ERROR: There an espace on the RGB color\n");
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

char *check_color(t_cub3d *cub)//, int color)
{
    int first_index_color;
    int second_index_color;
    char *temp;
    char **rgb_color;

    first_index_color = index_first_path(cub->tmp_store, 1);
    // printf("index first => %d\n", first_index_color);
    second_index_color = index_end_path(cub->tmp_store, (strlen(cub->tmp_store) - 2)); //skipping "/0" + also first character and secend character space "F "
    // printf("index sec => %d\n", second_index_color);
    // printf("index sec => %d\n", (int)strlen(cub->tmp_store) - 1);
    temp = ft_substr(cub->tmp_store, first_index_color, second_index_color - first_index_color + 1);
    parsing_rgb_proba(temp, 0, 0);
    rgb_color = ft_split(temp, ',');
    int i = 0;
    while (rgb_color[i])
    {
        puts(rgb_color[i]);
        i++;
    }
    //"255,255,255"
    // printf("index last => %d\n", second_index_color - first_index_color + 1);
    printf("%s\n", temp);
    return(temp);
}