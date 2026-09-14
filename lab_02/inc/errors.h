#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
  OK,
  IO_ERR,
  RANGE_ERR,
  FILE_ERR,
  OVERFLOW_ERR,
  ALLOCATION_ERR
} errors_e;

#endif