#include <stdio.h>
#include <stddef.h>
#include <string.h>


void str_connect (char * restrict dest,
 const size_t capacity_dest,
 const char * restrict source)
{
    size_t size_dest = strlen(dest);

    size_t i = size_dest;
    for (size_t j = 0; (i < capacity_dest) && (source[j] != '\0'); i++, j++)
        dest[i] = source[j];

    if (i == capacity_dest)
    {
        fprintf(stderr, "Переполнена память");
        i--;
    }

    dest[i] = '\0';
}

void str_divided (char * restrict dest,
 const size_t capacity_dest,
 char * restrict source, int gap_from)
{
    if (gap_from <= 0)
        fprintf(stderr, "Некорректный ввод");

    size_t i = gap_from - 1, j = 0;

    dest[j++] = source[i];
    source[i++] = '\0';

    for (; (j < capacity_dest) && (source[i] != '\0'); i++, j++)
        dest[j] = source[i];

    if (j == capacity_dest)
    {
        fprintf(stderr, "Переполнена память");
        j--;
    }

    dest[j] = '\0';
}
