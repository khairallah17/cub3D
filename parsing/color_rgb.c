#include "../Cub3D.h"

void error_rgb_proba(char *temp, int i, int count_cama)
{
    while (temp[i])
    {
        if (temp[i] == ',')
            count_cama++;
        if ((temp[i] < '0' || temp[i] > '9') && temp[i] != ',')
        {
            printf("ERROR: Please re-Check if RGB are Digits\n");
            exit(EXIT_FAILURE);
        }
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

int send_rgb_color(char *temp, char **rgb_color)
{
    int i;
    // int color;
    int tb_color[3];

    i = 0;
    int j = 0;
    rgb_color = ft_split(temp, ',');
    while (rgb_color[j])
        printf("rgb_color = %s\n", rgb_color[j++]);
    // puts("d");
    while (i < 3)
    {
        tb_color[i] = ft_atoi(rgb_color[i]);
        // puts("d3");
        if (tb_color[i] < 0 || tb_color[i] > 255)
        {
            printf("ERROR: Please re-change range of RGB the limit [0-255]\n");
            exit(EXIT_FAILURE);
        }
        // puts("d4");
        printf("tb_color = %d\n", tb_color[i]);
        i++;
    }
    int color = ((255 << 24) | (tb_color[0] << 16) | (tb_color[1] << 8) | tb_color[2]);
    // printf("color == %d\n", color);
    // printf("color1111 == %d\n", tb_color[0]);
    // return (((tb_color[0] << 24) | (tb_color[1] << 16) | (tb_color[2] << 8) | 0));
    return (color);
}

int check_color(t_cub3d *cub)
{
    int first_index_color;
    int second_index_color;
    int color;
    char *temp;
    char **rgb_color = NULL;

    cub->count_txtr_line++;
    first_index_color = index_first_path(cub->tmp_store, 1);
    // printf("index first => %d\n", first_index_color);
    second_index_color = index_end_path(cub->tmp_store, (strlen(cub->tmp_store) - 2)); //skipping "/0" + also first character and secend character space "F "
    // printf("index sec => %d\n", second_index_color);
    // printf("index sec => %d\n", (int)strlen(cub->tmp_store) - 1);
    temp = ft_substr(cub->tmp_store, first_index_color, second_index_color - first_index_color + 1);
    error_rgb_proba(temp, 0, 0);
    color  = send_rgb_color(temp, rgb_color);
    if (!temp)
    {
        free(temp);
        temp = NULL;
        printf("ERROR: Please re-check if RGB color are not empty\n");
        exit(EXIT_FAILURE);
    }
    // printf("index last => %d\n", second_index_color - first_index_color + 1);
    printf("%d\n", color);
    return(color);
}