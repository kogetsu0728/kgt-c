#ifndef MATRIX_ARRAY_H
#define MATRIX_ARRAY_H

#include "matrix.h"

typedef struct {
    size_t len;
    Mat* mat;
} MatArrDat;

typedef MatArrDat* MatArr;

MatArr matarr_new(const size_t, const size_t, const size_t);
MatArr matarr_cpy(const MatArr);
MatArr matarr_del(MatArr);

size_t matarr_get_len(const MatArr);

Mat matarr_get_mat(const MatArr, const size_t);

void matarr_out(const MatArr, FILE*);

#endif
