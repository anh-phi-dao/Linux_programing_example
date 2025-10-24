#include <stdio.h>

/**
 * @param argc: indicates how many command-line arguments there are
 * @param argv: is an array of pointers to the command-line arguments,
 * each of which is a null-terminated character string
 * The first of these strings, in argv[0], is (conventionally) the
 * name of the program itself. The list of pointers in argv is terminated by a NULL
 * pointer (i.e., argv[argc] is NULL)
 */

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
    {
        printf("Argument number %d:%s\n", i, argv[i]);
    }
    return 0;
}