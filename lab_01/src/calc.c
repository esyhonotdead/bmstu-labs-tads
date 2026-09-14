#include "calc.h"
#include "errors.h"

#define RAW_RESULT_MAX_DIGITS (BIG_INT_MAX_DIGITS + BIG_FLOAT_MAX_DIGITS)
#define MAX_RESULT_EXPONENT 99999

/** @brief Проверяет, равен ли нулю хотя бы один из множителей */
static int is_zero(const big_int_t *integer, const big_float_t *real)
{
    return (integer->len == 1 && integer->digits[0] == 0) || (real->len == 1 && real->digits[0] == 0);
}

/** @brief Перемножает массивы цифр и возвращает длину произведения без ведущих нулей */
static size_t multiply_digits(const big_int_t *integer, const big_float_t *real, unsigned int product[])
{
    size_t capacity = integer->len + real->len;
    size_t first = 0;

    for (size_t i = 0; i < capacity; i++)
        product[i] = 0;

    for (size_t i = integer->len; i > 0; i--)
    {
        for (size_t j = real->len; j > 0; j--)
        {
            size_t pos = i + j - 1;
            unsigned int value = product[pos] + integer->digits[i - 1] * real->digits[j - 1];
            product[pos] = value % 10;
            product[pos - 1] += value / 10;
        }
    }

    while (first + 1 < capacity && product[first] == 0)
        first++;

    if (first > 0)
    {
        for (size_t i = first; i < capacity; i++)
            product[i - first] = product[i];
    }

    return capacity - first;
}

/** @brief Округляет произведение до допустимого числа цифр, при необходимости изменяя порядок */
static void round_result(result_t *result, const unsigned int product[], size_t product_len)
{
    result->len = product_len < RESULT_MAX_DIGITS ? product_len : RESULT_MAX_DIGITS;
    for (size_t i = 0; i < result->len; i++)
        result->digits[i] = product[i];

    if (product_len > RESULT_MAX_DIGITS && product[RESULT_MAX_DIGITS] >= 5)
    {
        size_t pos = RESULT_MAX_DIGITS;
        while (pos > 0 && result->digits[pos - 1] == 9)
        {
            result->digits[pos - 1] = 0;
            pos--;
        }

        if (pos == 0)
        {
            result->digits[0] = 1;
            for (size_t i = 1; i < RESULT_MAX_DIGITS; i++)
                result->digits[i] = 0;
            result->exponent++;
        }
        else
            result->digits[pos - 1]++;
    }

    while (result->len > 1 && result->digits[result->len - 1] == 0)
        result->len--;
}

int multiply(const big_int_t *integer, const big_float_t *real, result_t *result)
{
    unsigned int product[RAW_RESULT_MAX_DIGITS];
    size_t product_len;

    if (is_zero(integer, real))
    {
        result->sign = 1;
        result->len = 1;
        result->digits[0] = 0;
        result->exponent = 0;
        return OK;
    }

    product_len = multiply_digits(integer, real, product);
    result->sign = integer->sign * real->sign;
    result->exponent = real->exponent - (int)real->len + (int)product_len;
    round_result(result, product, product_len);

    if (result->exponent > MAX_RESULT_EXPONENT || result->exponent < -MAX_RESULT_EXPONENT)
        return RESULT_EXPONENT_OVERFLOW_ERR;

    return OK;
}
