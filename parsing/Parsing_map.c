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

int main(int ac, char **av)
{
    check_arguments(ac, av);
}
