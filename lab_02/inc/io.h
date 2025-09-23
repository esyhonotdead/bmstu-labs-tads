#ifndef IO_H
#define IO_H

#include "books.h"

#include <stdio.h>

void print_theader();
void print_tgenral(book_t book);
void print_ttechb(book_t book);
void print_tfictb(book_t book);
void print_tchildb(book_t book);
void print_table(books_t *books);

#endif
