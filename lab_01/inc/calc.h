#ifndef CALC_H
#define CALC_H

#include "big_float.h"
#include "big_int.h"

#define RESULT_MAX_DIGITS 40

typedef struct
{
    int sign;
    size_t len;
    int exponent;
    unsigned char digits[RESULT_MAX_DIGITS];
} result_t;

/** @brief Умножает целое число на действительное, округляя результат и проверяя его порядок */
int multiply(const big_int_t *integer, const big_float_t *real, result_t *result);

#endif
