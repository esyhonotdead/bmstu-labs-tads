#include "big_float.h"
#include "errors.h"
#include "str.h"

#define RAW_MANTISSA_SIZE (BIG_FLOAT_MAX_DIGITS + 1)

/** @brief Разбирает порядок со знаком с текущей позиции, проверяя его формат и длину */
static int parse_exponent(const char *str, size_t *pos, int *exponent)
{
    int sign = 1;
    int value = 0;
    size_t digits_count = 0;

    if (str[*pos] == '+' || str[*pos] == '-')
    {
        if (str[*pos] == '-')
            sign = -1;
        (*pos)++;
    }

    while (is_digit(str[*pos]))
    {
        if (digits_count == EXPONENT_MAX_DIGITS)
            return EXPONENT_OVERFLOW_ERR;
        value = value * 10 + str[*pos] - '0';
        digits_count++;
        (*pos)++;
    }

    if (digits_count == 0 || str[*pos] != '\0')
        return INVALID_FORMAT_ERR;

    *exponent = sign * value;
    return OK;
}

int big_float_parse(const char *str, big_float_t *number)
{
    unsigned char raw_digits[RAW_MANTISSA_SIZE];
    size_t pos = 0;
    size_t raw_len = 0;
    size_t integer_digits = 0;
    size_t first_significant = 0;
    int point_found = 0;
    int rc;

    number->sign = 1;
    if (str[pos] == '+' || str[pos] == '-')
    {
        if (str[pos] == '-')
            number->sign = -1;
        pos++;
    }

    while (str[pos] != '\0' && str[pos] != 'E' && str[pos] != 'e')
    {
        if (str[pos] == '.')
        {
            if (point_found)
                return INVALID_FORMAT_ERR;
            point_found = 1;
        }
        else if (is_digit(str[pos]))
        {
            if (raw_len == BIG_FLOAT_MAX_DIGITS)
                return MANTISSA_OVERFLOW_ERR;
            raw_digits[raw_len++] = str[pos] - '0';
            if (!point_found)
                integer_digits++;
        }
        else
            return INVALID_FORMAT_ERR;
        pos++;
    }

    if (raw_len == 0)
        return INVALID_FORMAT_ERR;

    number->exponent = 0;
    if (str[pos] == 'E' || str[pos] == 'e')
    {
        pos++;
        rc = parse_exponent(str, &pos, &number->exponent);
        if (rc != OK)
            return rc;
    }
    else if (str[pos] != '\0')
        return INVALID_FORMAT_ERR;

    while (first_significant < raw_len && raw_digits[first_significant] == 0)
        first_significant++;

    if (first_significant == raw_len)
    {
        number->sign = 1;
        number->len = 1;
        number->digits[0] = 0;
        number->exponent = 0;
        return OK;
    }

    number->exponent += (int)integer_digits - (int)first_significant;
    number->len = raw_len - first_significant;
    while (number->len > 1 && raw_digits[first_significant + number->len - 1] == 0)
        number->len--;

    for (size_t i = 0; i < number->len; i++)
        number->digits[i] = raw_digits[first_significant + i];

    return OK;
}
