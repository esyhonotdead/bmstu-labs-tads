#include "calc.h"
#include "errors.h"
#include "io.h"

/** @brief Читает множители, перемножает их и выводит результат или сообщение об ошибке */
int main(void)
{
    big_int_t integer;
    big_float_t real;
    result_t result;
    int rc;

    print_intro();

    rc = input_big_int(&integer);
    if (rc == OK)
        rc = input_big_float(&real);
    if (rc == OK)
        rc = multiply(&integer, &real, &result);

    if (rc == OK)
        print_result(&result);
    else
        print_error(rc);

    return rc;
}
