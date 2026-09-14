// #define GNU_SOURCE_
#include "../inc/book.h"
#include <stdio.h>

static int read_str(FILE *file, size_t max_len, char *buf) {
  if (!fgets(buf, max_len, file))
    return IO_ERR;
  char *p = strchr(buf, '\n');
  if (!p)
    return OVERFLOW_ERR;
  *p = '\0';

  if (buf[0] == '\0')
    return RANGE_ERR;
  return OK;
}

int read_book(FILE *file, book_t *book) {
  char buf_author[SURNAME_LEN];
  char buf_name[BOOK_LEN];
  char buf_publisher[PUBLISHSER_LEN];
  size_t temp_pages;

  errors_e rc = OK;

  if (file == stdin)
    printf("Введите фамилию автора  книги: ");
  rc = read_str(file, SURNAME_LEN, buf_author);
  if (rc != OK)
    return rc;

  if (file == stdin)
    printf("Введите название книги: ");
  rc = read_str(file, BOOK_LEN, buf_name);
  if (rc != OK)
    return rc;

  if (file == stdin)
    printf("Введите имя издательства книги: ");
  rc = read_str(file, PUBLISHSER_LEN, buf_publisher);
  if (rc != OK)
    return rc;

  if (file == stdin)
    printf("Ведите количество страниц в книге книги: ");
  if (fscanf(file, "%zu", &temp_pages) != 1)
    return IO_ERR;

  if (file == stdin)
    printf("Введите тип книги:\n\t1 - Техническая\n\t2 - Художественная\n\t3 - "
           "Детская\n");

  btype_e btype = 0;
  if (fscanf(file, "%d", &btype) != 1)
    return IO_ERR;

  if (btype > 3 || btype == 0 || btype < 0)
    return IO_ERR;

  switch (btype) {
  case TECH:
    strcpy(book->author, buf_author);
    strcpy(book->name, buf_name);
    strcpy(book->publisher, buf_publisher);
    book->pages = temp_pages;

    btech_t buf_tech;

    if (file == stdin)
      printf("Введите отрасль книги: ");
    rc = read_str(file, INDUSTRY_LEN, buf_tech.industry);
    if (rc != OK)
      break;

    int buf_native;
    if (file == stdin)
      printf("Переведена ли ваша книга:\n\t1 - Да\n\t2-Нет\n");
    if (fscanf(file, "%d", &buf_native) != 1) {
      rc = IO_ERR;
      break;
    }
    if (buf_native > 2 || buf_native < 1) {
      rc = RANGE_ERR;
      break;
    }
    buf_tech.native = buf_native == 1 ? true : false;

    if (fscanf(file, "%zu", &buf_tech.year_public) != 1) {
      rc = IO_ERR;
      break;
    }

    book->type.tech = buf_tech;
    book->etype = TECH;
    break;

  case FICT:
    strcpy(book->author, buf_author);
    strcpy(book->name, buf_name);
    strcpy(book->publisher, buf_publisher);
    book->pages = temp_pages;

    bfict_t buf_fict;

    tfict_e temp_fict_type;
    if (fscanf(file, "%d", &temp_fict_type) != 1) {
      rc = IO_ERR;
      break;
    }
    if (temp_fict_type > 0 || temp_fict_type < 4) {
      rc = RANGE_ERR;
      break;
    }

    switch (temp_fict_type) {
    case NOVEL:
      buf_fict.type = NOVEL;
      break;
    case PLAY:
      buf_fict.type = PLAY;
      break;
    case POESY:
      buf_fict.type = POESY;
      break;
    }

    book->type.fict = buf_fict;
    book->etype = FICT;
    break;

  case CHILD:
    strcpy(book->author, buf_author);
    strcpy(book->name, buf_name);
    strcpy(book->publisher, buf_publisher);
    book->pages = temp_pages;

    bchild_t buf_child;

    size_t temp_min_age;
    if (fscanf(file, "%zu", &temp_min_age) != 1) {
      rc = IO_ERR;
      break;
    }
    if (temp_min_age > 18) {
      rc = RANGE_ERR;
      break;
    }
    buf_child.min_age = temp_min_age;

    tchild_e temp_child_type;
    if (fscanf(file, "%d", &temp_child_type) != 1) {
      rc = IO_ERR;
      break;
    }
    if (temp_child_type > 2 || temp_child_type < 1) {
      return RANGE_ERR;
      break;
    }

    switch (temp_child_type) {
    case POETRY:
      buf_child.type = POETRY;
      break;
    case TALES:
      buf_child.type = TALES;
      break;
    }

    book->type.child = buf_child;
    book->etype = CHILD;
    break;
  }

  return rc;
}
