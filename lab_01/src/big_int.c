#include "big_int.h"

#include "errors.h"
#include "str.h"

int big_int_parse(const char *str, big_int_t *number)
{
    size_t pos = 0;
    size_t first_digit;
    size_t digits_count = 0;

    number->sign = 1;
    if (str[pos] == '+' || str[pos] == '-')
    {
        if (str[pos] == '-')
            number->sign = -1;
        pos++;
    }

    first_digit = pos;
    while (is_digit(str[pos]))
    {
        digits_count++;
        pos++;
    }

    if (digits_count == 0 || str[pos] != '\0')
        return INVALID_FORMAT_ERR;
    if (digits_count > BIG_INT_MAX_DIGITS)
        return BIG_INT_OVERFLOW_ERR;

    while (str[first_digit] == '0' && first_digit + 1 < pos)
        first_digit++;

    number->len = pos - first_digit;
    for (size_t i = 0; i < number->len; i++)
        number->digits[i] = str[first_digit + i] - '0';

    if (number->len == 1 && number->digits[0] == 0)
        number->sign = 1;

    return OK;
}
