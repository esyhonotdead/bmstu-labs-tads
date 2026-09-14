#ifndef BOOK_H
#define BOOK_H

#include "errors.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define SURNAME_LEN 30 + 1
#define BOOK_LEN 30 + 1
#define PUBLISHSER_LEN 30 + 1
#define INDUSTRY_LEN 30 + 1

#define BTECH_NAME "Техническая"
#define BFICT_NAME "Художественная"
#define BCHILD_NAME "Детска"

#define TFICT_NOVEL "Роман"
#define TFICT_PLAY "Пьеса"
#define TFICT_POESY "Поэзия"

#define TCHILD_POETRY "Стихи"
#define TCHILD_TALES "Сказки"

typedef enum { TECH = 1, FICT, CHILD } btype_e;

typedef enum { NOVEL = 1, PLAY, POESY } tfict_e;

typedef enum { POETRY = 1, TALES } tchild_e;

typedef struct {
  char industry[INDUSTRY_LEN];
  bool native;
  size_t year_public;
} btech_t;

typedef struct {
  tfict_e type;
} bfict_t;

typedef struct {
  size_t min_age;
  tchild_e type;
} bchild_t;

typedef struct {
  char author[SURNAME_LEN];
  char name[BOOK_LEN];
  char publisher[PUBLISHSER_LEN];
  size_t pages;
  union btype_u {
    btech_t tech;
    bfict_t fict;
    bchild_t child;
  } type;
  btype_e etype;
} book_t;

int read_book(FILE *file, book_t *book);

#endif
