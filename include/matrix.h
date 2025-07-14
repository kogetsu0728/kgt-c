#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct {
    Dim row, col;
    Vec* vec;
} MatDat;

typedef MatDat* Mat;

Mat mat_new(const Dim, const Dim);
Mat mat_del(Mat);
Mat mat_cpy(const Mat);
Mat mat_asn(Mat, const Mat);

Dim mat_get_row(const Mat);
Dim mat_get_col(const Mat);

Sca mat_get_val(const Mat, const Dim, const Dim);
Sca mat_set_val(Mat, const Dim, const Dim, const Sca);

void mat_out(const Mat, FILE*);

Mat mat_add(const Mat, const Mat);
Mat mat_sub(const Mat, const Mat);
Mat mat_mul(const Mat, const Mat);
Mat mat_div(const Mat, const Mat);
Mat mat_dot(const Mat, const Mat);

Mat mat_add_vec(const Mat, const Vec);
Mat mat_sub_vec(const Mat, const Vec);
Mat mat_mul_vec(const Mat, const Vec);
Mat mat_div_vec(const Mat, const Vec);
Vec mat_dot_vec(const Mat, const Vec);

Mat mat_add_sca(const Mat, const Sca);
Mat mat_sub_sca(const Mat, const Sca);
Mat mat_mul_sca(const Mat, const Sca);
Mat mat_div_sca(const Mat, const Sca);

bool mat_eq(const Mat, const Mat);
bool mat_ne(const Mat, const Mat);
bool mat_gt(const Mat, const Mat);
bool mat_ge(const Mat, const Mat);
bool mat_lt(const Mat, const Mat);
bool mat_le(const Mat, const Mat);

#endif
