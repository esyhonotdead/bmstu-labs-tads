#ifndef BIG_INT_H
#define BIG_INT_H

#include <stddef.h>

#define BIG_INT_MAX_DIGITS 40

typedef struct
{
    int sign;
    size_t len;
    unsigned char digits[BIG_INT_MAX_DIGITS];
} big_int_t;

/** @brief Разбирает десятичное целое число со знаком, проверяя его длину и удаляя ведущие нули */
int big_int_parse(const char *str, big_int_t *number);

#endif
