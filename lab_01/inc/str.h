#ifndef STR_H
#define STR_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** @brief Читает строку, удаляет символы конца строки и отклоняет пустой или слишком длинный ввод */
int read_line(FILE *file, char str[], size_t size);

/** @brief Проверяет, является ли символ десятичной цифрой */
int is_digit(char ch);

#endif
