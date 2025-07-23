#include "matrix.h"

Mat mat_new(const Dim row, const Dim col) {
    ASSERT_LT(row, MAX_DIM);
    ASSERT_LT(col, MAX_DIM);
    ASSERT_LT(row * col, MAX_DIM);

    Mat self = malloc(sizeof(MatDat));
    ASSERT_NE_NULL(self);

    self->row = row;
    self->col = col;

    if (row == 0) {
        self->vec = NULL;
    } else {
        self->vec = malloc(sizeof(Vec) * row);
        ASSERT_NE_NULL(self->vec);

        for (Dim i = 0; i < row; ++i) {
            self->vec[i] = vec_new(col);
        }
    }

    return self;
}

Mat mat_del(Mat self) {
    ASSERT_NE_NULL(self);

    const Dim row = self->row;

    if (row > 0) {
        for (Dim i = 0; i < row; ++i) {
            self->vec[i] = vec_del(self->vec[i]);
        }

        free(self->vec);
    }

    free(self);

    return NULL;
}

Mat mat_cpy(const Mat self) {
    ASSERT_NE_NULL(self);

    const Dim row = self->row;
    const Dim col = self->col;

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec cpy = vec_cpy(self->vec[i]);

        res->vec[i] = vec_asn(res->vec[i], cpy);
    }

    return res;
}

Mat mat_asn(Mat self, const Mat mat) {
    if (self == mat) {
        return mat;
    }

    if (self != NULL) {
        self = mat_del(self);
    }

    return mat;
}

Dim mat_get_row(const Mat self) {
    ASSERT_NE_NULL(self);

    return self->row;
}

Dim mat_get_col(const Mat self) {
    ASSERT_NE_NULL(self);

    return self->col;
}

static Vec mat_get_vec(const Mat self, const Dim row) {
    ASSERT_NE_NULL(self);
    ASSERT_LT(row, mat_get_row(self));

    return self->vec[row];
}

static Vec mat_set_vec(Mat self, const Dim row, const Vec vec) {
    ASSERT_NE_NULL(self);
    ASSERT_NE_NULL(vec);
    ASSERT_LT(row, mat_get_row(self));
    ASSERT_EQ(vec_get_dim(vec), mat_get_col(self));

    return self->vec[row] = vec_asn(self->vec[row], vec);
}

Sca mat_get_val(const Mat self, const Dim row, const Dim col) {
    ASSERT_NE_NULL(self);
    ASSERT_LT(row, mat_get_row(self));
    ASSERT_LT(col, mat_get_col(self));

    return vec_get_val(mat_get_vec(self, row), col);
}

Sca mat_set_val(Mat self, const Dim row, const Dim col, const Sca sca) {
    ASSERT_NE_NULL(self);
    ASSERT_LT(row, mat_get_row(self));
    ASSERT_LT(col, mat_get_col(self));

    return vec_set_val(mat_get_vec(self, row), col, sca);
}

void mat_out(const Mat self, FILE* str) {
    ASSERT_NE_NULL(self);
    ASSERT_NE_NULL(str);

    const Dim row = mat_get_row(self);

    fprintf(str, "[");

    for (Dim i = 0; i < row; ++i) {
        if (i > 0) {
            fprintf(str, ",\n ");
        }

        vec_out(mat_get_vec(self, i), str);
    }

    fprintf(str, "]");

    return;
}

Mat mat_fnc(const Mat self, const ScaFnc fnc) {
    ASSERT_NE_NULL(self);
    ASSERT_NE_NULL(fnc);

    const Dim row = mat_get_row(self);
    const Dim col = mat_get_col(self);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec vec = mat_get_vec(self, i);

        mat_set_vec(res, i, vec_fnc(vec, fnc));
    }

    return res;
}

Mat mat_trp(const Mat self) {
    ASSERT_NE_NULL(self);

    const Dim row = mat_get_col(self);
    const Dim col = mat_get_row(self);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        for (Dim j = 0; j < col; ++j) {
            const Sca val = mat_get_val(self, j, i);

            mat_set_val(res, i, j, val);
        }
    }

    return res;
}

Mat mat_add(const Mat lhs, const Mat rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(mat_get_row(lhs), mat_get_row(rhs));
    ASSERT_EQ(mat_get_col(lhs), mat_get_col(rhs));

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(lhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Vec vr = mat_get_vec(rhs, i);

        mat_set_vec(res, i, vec_add(vl, vr));
    }

    return res;
}

Mat mat_sub(const Mat lhs, const Mat rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(mat_get_row(lhs), mat_get_row(rhs));
    ASSERT_EQ(mat_get_col(lhs), mat_get_col(rhs));

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(lhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Vec vr = mat_get_vec(rhs, i);

        mat_set_vec(res, i, vec_sub(vl, vr));
    }

    return res;
}

Mat mat_mul(const Mat lhs, const Mat rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(mat_get_row(lhs), mat_get_row(rhs));
    ASSERT_EQ(mat_get_col(lhs), mat_get_col(rhs));

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(lhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Vec vr = mat_get_vec(rhs, i);

        mat_set_vec(res, i, vec_mul(vl, vr));
    }

    return res;
}

Mat mat_div(const Mat lhs, const Mat rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(mat_get_row(lhs), mat_get_row(rhs));
    ASSERT_EQ(mat_get_col(lhs), mat_get_col(rhs));

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(lhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Vec vr = mat_get_vec(rhs, i);

        mat_set_vec(res, i, vec_div(vl, vr));
    }

    return res;
}

Mat mat_dot(const Mat lhs, const Mat rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(mat_get_col(lhs), mat_get_row(rhs));

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(rhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        for (Dim j = 0; j < col; ++j) {
            const Dim dim = mat_get_col(lhs);
            const Vec vl = mat_get_vec(lhs, i);

            Vec vr = vec_new(dim);

            for (Dim k = 0; k < dim; ++k) {
                vec_set_val(vr, k, mat_get_val(rhs, k, j));
            }

            mat_set_val(res, i, j, vec_dot(vl, vr));

            vr = vec_del(vr);
        }
    }

    return res;
}

Mat mat_add_vec(const Mat lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(mat_get_row(lhs), vec_get_dim(rhs));

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(lhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Sca vr = vec_get_val(rhs, i);

        mat_set_vec(res, i, vec_add_sca(vl, vr));
    }

    return res;
}

Mat mat_sub_vec(const Mat lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(mat_get_row(lhs), vec_get_dim(rhs));

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(lhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Sca vr = vec_get_val(rhs, i);

        mat_set_vec(res, i, vec_sub_sca(vl, vr));
    }

    return res;
}

Mat mat_mul_vec(const Mat lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(mat_get_row(lhs), vec_get_dim(rhs));

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(lhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Sca vr = vec_get_val(rhs, i);

        mat_set_vec(res, i, vec_mul_sca(vl, vr));
    }

    return res;
}

Mat mat_div_vec(const Mat lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(mat_get_row(lhs), vec_get_dim(rhs));

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(lhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Sca vr = vec_get_val(rhs, i);

        mat_set_vec(res, i, vec_div_sca(vl, vr));
    }

    return res;
}

Vec mat_dot_vec(const Mat lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(mat_get_col(lhs), vec_get_dim(rhs));

    const Dim dim = mat_get_row(lhs);

    Vec res = vec_new(dim);

    for (Dim i = 0; i < dim; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Vec vr = rhs;

        vec_set_val(res, i, vec_dot(vl, vr));
    }

    return res;
}

Mat mat_add_sca(const Mat lhs, const Sca rhs) {
    ASSERT_NE_NULL(lhs);

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(lhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Sca vr = rhs;

        mat_set_vec(res, i, vec_add_sca(vl, vr));
    }

    return res;
}

Mat mat_sub_sca(const Mat lhs, const Sca rhs) {
    ASSERT_NE_NULL(lhs);

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(lhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Sca vr = rhs;

        mat_set_vec(res, i, vec_sub_sca(vl, vr));
    }

    return res;
}

Mat mat_mul_sca(const Mat lhs, const Sca rhs) {
    ASSERT_NE_NULL(lhs);

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(lhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Sca vr = rhs;

        mat_set_vec(res, i, vec_mul_sca(vl, vr));
    }

    return res;
}

Mat mat_div_sca(const Mat lhs, const Sca rhs) {
    ASSERT_NE_NULL(lhs);

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(lhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Sca vr = rhs;

        mat_set_vec(res, i, vec_div_sca(vl, vr));
    }

    return res;
}

bool mat_eq(const Mat lhs, const Mat rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);

    const Dim rl = mat_get_row(lhs);
    const Dim rr = mat_get_row(rhs);

    if (rl != rr) {
        return false;
    }

    for (Dim i = 0; i < rl; ++i) {
        const Vec vl = mat_get_vec(lhs, i);
        const Vec vr = mat_get_vec(rhs, i);

        if (!vec_eq(vl, vr)) {
            return false;
        }
    }

    return true;
}

bool mat_ne(const Mat lhs, const Mat rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);

    const bool eq = mat_eq(lhs, rhs);

    return !eq;
}

bool mat_gt(const Mat lhs, const Mat rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);

    const Dim rl = mat_get_row(lhs);
    const Dim rr = mat_get_row(rhs);

    const Dim rm = GET_MAX(rl, rr);

    for (Dim i = 0; i < rm; ++i) {
        if (i >= rl) {
            return false;
        }

        if (i >= rr) {
            return true;
        }

        const Vec vl = mat_get_vec(lhs, i);
        const Vec vr = mat_get_vec(rhs, i);

        if (vec_lt(vl, vr)) {
            return false;
        }

        if (vec_gt(vl, vr)) {
            return true;
        }
    }

    return false;
}

bool mat_ge(const Mat lhs, const Mat rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);

    const bool gt = mat_ge(lhs, rhs);
    const bool eq = mat_eq(lhs, rhs);

    return (gt || eq);
}

bool mat_lt(const Mat lhs, const Mat rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);

    return mat_gt(rhs, lhs);
}

bool mat_le(const Mat lhs, const Mat rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);

    return mat_ge(rhs, lhs);
}
