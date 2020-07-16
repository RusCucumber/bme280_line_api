#include <string.h>
#include <stdlib.h>

char *my_strdup(char str[])
{
    char *dest;
    dest = (char *)malloc(sizeof(char) * ((int)strlen(str) + 1));
    strcpy(dest, str);
    
    return dest;
}
