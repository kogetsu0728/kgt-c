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
        res->vec[i] = vec_del(res->vec[i]);
        res->vec[i] = vec_cpy(self->vec[i]);
    }

    return res;
}

Dim mat_get_row(const Mat self) {
    ASSERT_NE_NULL(self);

    return self->row;
}

Dim mat_get_col(const Mat self) {
    ASSERT_NE_NULL(self);

    return self->col;
}

Sca mat_get_val(const Mat self, const Dim row, const Dim col) {
    ASSERT_NE_NULL(self);
    ASSERT_LT(row, mat_get_row(self));
    ASSERT_LT(col, mat_get_col(self));

    return vec_get_val(self->vec[row], col);
}

Sca mat_set_val(Mat self, const Dim row, const Dim col, const Sca sca) {
    ASSERT_NE_NULL(self);
    ASSERT_LT(row, mat_get_row(self));
    ASSERT_LT(col, mat_get_col(self));

    return vec_set_val(self->vec[row], col, sca);
}

Mat sca_to_mat(const Sca sca) {
    Mat res = mat_new(1, 1);

    mat_set_val(res, 0, 0, sca);

    return res;
}

Mat vec_to_mat(const Vec vec) {
    ASSERT_NE_NULL(vec);

    const Dim row = vec_get_dim(vec);

    Mat res = mat_new(row, 1);

    for (Dim i = 0; i < row; ++i) {
        const Sca val = vec_get_val(vec, i);

        mat_set_val(res, i, 0, val);
    }

    return res;
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

        vec_out(self->vec[i], str);
    }

    fprintf(str, "]");

    return;
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
        for (Dim j = 0; j < col; ++j) {
            const Sca vl = mat_get_val(lhs, i, j);
            const Sca vr = mat_get_val(rhs, i, j);

            mat_set_val(res, i, j, vl + vr);
        }
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
        for (Dim j = 0; j < col; ++j) {
            const Sca vl = mat_get_val(lhs, i, j);
            const Sca vr = mat_get_val(rhs, i, j);

            mat_set_val(res, i, j, vl - vr);
        }
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
        for (Dim j = 0; j < col; ++j) {
            const Sca vl = mat_get_val(lhs, i, j);
            const Sca vr = mat_get_val(rhs, i, j);

            mat_set_val(res, i, j, vl * vr);
        }
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
        for (Dim j = 0; j < col; ++j) {
            const Sca vl = mat_get_val(lhs, i, j);
            const Sca vr = mat_get_val(rhs, i, j);

            mat_set_val(res, i, j, vl / vr);
        }
    }

    return res;
}

Mat mat_dot(const Mat lhs, const Mat rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(mat_get_col(lhs), mat_get_row(rhs));

    const Dim row = mat_get_row(lhs);
    const Dim col = mat_get_col(rhs);
    const Dim inner = mat_get_col(lhs);

    Mat res = mat_new(row, col);

    for (Dim i = 0; i < row; ++i) {
        for (Dim j = 0; j < col; ++j) {
            Sca sum = 0.0;

            for (Dim k = 0; k < inner; ++k) {
                const Sca vl = mat_get_val(lhs, i, k);
                const Sca vr = mat_get_val(rhs, k, j);

                sum += vl * vr;
            }

            mat_set_val(res, i, j, sum);
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
        for (Dim j = 0; j < col; ++j) {
            const Sca vl = mat_get_val(lhs, i, j);
            const Sca vr = vec_get_val(rhs, i);

            mat_set_val(res, i, j, vl + vr);
        }
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
        for (Dim j = 0; j < col; ++j) {
            const Sca vl = mat_get_val(lhs, i, j);
            const Sca vr = vec_get_val(rhs, i);

            mat_set_val(res, i, j, vl - vr);
        }
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
        for (Dim j = 0; j < col; ++j) {
            const Sca vl = mat_get_val(lhs, i, j);
            const Sca vr = vec_get_val(rhs, i);

            mat_set_val(res, i, j, vl * vr);
        }
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
        for (Dim j = 0; j < col; ++j) {
            const Sca vl = mat_get_val(lhs, i, j);
            const Sca vr = vec_get_val(rhs, i);

            mat_set_val(res, i, j, vl / vr);
        }
    }

    return res;
}
