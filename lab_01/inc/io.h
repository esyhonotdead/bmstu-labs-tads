#ifndef IO_H
#define IO_H

#include "calc.h"

#include <stdio.h>

#define INPUT_BUFFER_SIZE 80

/** @brief Выводит описание программы и ограничения на вводимые числа */
void print_intro(void);

/** @brief Запрашивает целое число и разбирает его из стандартного ввода */
int input_big_int(big_int_t *number);

/** @brief Запрашивает действительное число и разбирает его из стандартного ввода */
int input_big_float(big_float_t *number);

/** @brief Выводит результат в нормализованной экспоненциальной форме */
void print_result(const result_t *result);

/** @brief Выводит сообщение, соответствующее коду ошибки */
void print_error(int error);

#endif
