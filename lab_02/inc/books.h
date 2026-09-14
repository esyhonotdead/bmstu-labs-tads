#ifndef BOOKS_H
#define BOOKS_H

#include "book.h"
#include "errors.h"

#include <stddef.h>
#include <stdlib.h>

#define MAX_BOOKS 30

typedef struct books {
  book_t data[MAX_BOOKS];
  size_t count;
  size_t capacity;
} books_t;

#endif
