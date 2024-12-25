#include <stdio.h>

int main( int argc, char* argv[])
{
    if (argc == NULL)
    {
        fprintf(stderr, "Error: No file informed.\n");
    }

    FILE* file = fopen(argv, "r");
    if(file == NULL)
    {
       puts("Number of characters, lines, words and bytes equal zero");
       fclose(file);
    }

    return 0;
}