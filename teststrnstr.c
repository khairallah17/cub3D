#include <libc.h>

int main (void)
{
    char * tmp;
    // tmp = strnstr("Agoumi El Mehdi", "Mehdi", 3);
    printf("%s\n", strnstr("Agoumi El Mehdi", "E", strlen("Agoumi El Mehdi")));
}