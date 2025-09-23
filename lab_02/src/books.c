#include "../inc/books.h"

int read_books(FILE *file, books_t *books)
{
    errors_e rc = OK;
    while (books->count < books->capacity)
    {
        rc = read_book(file, &(books->data[books->count]));
        if (rc != OK)
        {
            if (rc != OK && feof(file))
                return OK;
            return OK;
        }
        books->count++;
    }

    book_t temp_book;
    rc = read_book(file, &temp_book);
    if (rc != OK)
        return OK;

    return OVERFLOW_ERR;
}

int insert_book(books_t *books, book_t book)
{
    if (books->count + 1 > books->capacity)
        return OVERFLOW_ERR;

    books->data[++(books->count)] = book;
    return OK;
}

int remove_book(size_t ind, books_t *books)
{
    if (ind >= books->count)
        return RANGE_ERR;

    for (size_t i = ind; i < books->count - 1; i++)
    {
        books->data[i] = books->data[i + 1];
    }
    --(books->count);
    return OK;
}
