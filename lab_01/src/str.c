#define _POSIX_C_SOURCE 200809L

#include "str.h"
#include "errors.h"

int read_line(FILE *file, char str[], size_t size)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t len = getline(&line, &capacity, file);
    int rc = OK;

    if (len < 0)
        rc = IO_ERR;
    else
    {
        if (len > 0 && line[len - 1] == '\n')
            line[--len] = '\0';
        if (len > 0 && line[len - 1] == '\r')
            line[--len] = '\0';

        if (len == 0)
            rc = EMPTY_INPUT_ERR;
        else if ((size_t)len >= size)
            rc = IO_ERR;
        else
            memcpy(str, line, (size_t)len + 1);
    }

    free(line);
    return rc;
}

int is_digit(char ch)
{
    return ch >= '0' && ch <= '9';
}
