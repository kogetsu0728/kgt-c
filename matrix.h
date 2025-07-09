#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef double MatVal;

typedef struct {
    size_t row, col;
    MatVal** val;
} MatDat;

typedef MatDat* Mat;

Mat mat_new(const size_t, const size_t);
Mat mat_cpy(const Mat);
Mat mat_del(Mat);

size_t mat_get_col(const Mat self);
size_t mat_get_row(const Mat self);

MatVal mat_get_val(const Mat, const size_t, const size_t);
MatVal mat_set_val(Mat, const size_t, const size_t, const MatVal);

void mat_out(FILE*, const Mat self);

Mat mat_add(const Mat, const Mat);
Mat mat_sub(const Mat, const Mat);
Mat mat_mul(const Mat, const Mat);

#endif
