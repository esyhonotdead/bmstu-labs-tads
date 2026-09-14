#ifndef BIG_FLOAT_H
#define BIG_FLOAT_H

#include <stddef.h>

#define BIG_FLOAT_MAX_DIGITS 30
#define EXPONENT_MAX_DIGITS 5

typedef struct
{
    int sign;
    size_t len;
    int exponent;
    unsigned char digits[BIG_FLOAT_MAX_DIGITS];
} big_float_t;

/** @brief Разбирает и нормализует десятичное действительное число, проверяя длину мантиссы и порядка */
int big_float_parse(const char *str, big_float_t *number);

#endif
