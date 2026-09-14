#include "io.h"
#include "errors.h"
#include "str.h"

void print_intro(void)
{
    printf("Умножение целого числа на действительное число.\n");
    printf("Целое число: до 40 цифр.\n");
    printf("Действительное число: [+-]m.nE[+-]K, до 30 цифр ");
    printf("в мантиссе и до 5 цифр в порядке.\n\n");
}

int input_big_int(big_int_t *number)
{
    char str[INPUT_BUFFER_SIZE];
    int rc;

    printf("Введите целое число:\n");
    printf("1234567890123456789012345678901234567890\n");
    rc = read_line(stdin, str, sizeof(str));
    if (rc != OK)
        return rc;

    return big_int_parse(str, number);
}

int input_big_float(big_float_t *number)
{
    char str[INPUT_BUFFER_SIZE];
    int rc;

    printf("Введите действительное число:\n");
    printf("123456789012345678901234567890 E+12345\n");
    rc = read_line(stdin, str, sizeof(str));
    if (rc != OK)
        return rc;

    return big_float_parse(str, number);
}

void print_result(const result_t *result)
{
    printf("Результат: %c0.", result->sign < 0 ? '-' : '+');
    for (size_t i = 0; i < result->len; i++)
        printf("%u", result->digits[i]);
    printf("E%+d\n", result->exponent);
}

void print_error(int error)
{
    switch (error)
    {
    case IO_ERR:
        printf("Ошибка: не удалось прочитать строку или строка слишком длинная.\n");
        break;
    case EMPTY_INPUT_ERR:
        printf("Ошибка: введена пустая строка.\n");
        break;
    case INVALID_FORMAT_ERR:
        printf("Ошибка: неверный формат числа.\n");
        break;
    case BIG_INT_OVERFLOW_ERR:
        printf("Ошибка: целое число содержит более 40 цифр.\n");
        break;
    case MANTISSA_OVERFLOW_ERR:
        printf("Ошибка: мантисса содержит более 30 цифр.\n");
        break;
    case EXPONENT_OVERFLOW_ERR:
        printf("Ошибка: порядок содержит более 5 цифр.\n");
        break;
    case RESULT_EXPONENT_OVERFLOW_ERR:
        printf("Ошибка: переполнение порядка результата.\n");
        break;
    default:
        printf("Ошибка: неизвестная ошибка.\n");
    }
}
