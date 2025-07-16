#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <string.h>

#include "scalar.h"

typedef size_t Dim;

typedef struct {
    Dim dim;
    Sca* val;
} VecDat;

typedef VecDat* Vec;

extern const Dim MAX_DIM;

Vec vec_new(const Dim);
Vec vec_del(Vec);
Vec vec_cpy(const Vec);
Vec vec_asn(Vec, const Vec);

Dim vec_get_dim(const Vec);

Sca vec_get_val(const Vec, const Dim);
Sca vec_set_val(Vec, const Dim, const Sca);

void vec_out(const Vec, FILE*);

Vec vec_fnc(const Vec, const ScaFnc);

Vec vec_add(const Vec, const Vec);
Vec vec_sub(const Vec, const Vec);
Vec vec_mul(const Vec, const Vec);
Vec vec_div(const Vec, const Vec);
Sca vec_dot(const Vec, const Vec);

Vec vec_add_sca(const Vec, const Sca);
Vec vec_sub_sca(const Vec, const Sca);
Vec vec_mul_sca(const Vec, const Sca);
Vec vec_div_sca(const Vec, const Sca);

bool vec_eq(const Vec, const Vec);
bool vec_ne(const Vec, const Vec);
bool vec_gt(const Vec, const Vec);
bool vec_ge(const Vec, const Vec);
bool vec_lt(const Vec, const Vec);
bool vec_le(const Vec, const Vec);

#endif
