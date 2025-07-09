#include "matrix.h"

Mat mat_new(const size_t row, const size_t col) {
    Mat self = malloc(sizeof(MatDat));
    assert(self != NULL);

    self->row = row;
    self->col = col;

    self->val = malloc(sizeof(MatVal*) * row);
    assert(self->val != NULL);

    for (size_t i = 0; i < row; ++i) {
        self->val[i] = malloc(sizeof(MatVal) * col);
        assert(self->val[i] != NULL);

        memset(self->val[i], 0, sizeof(MatVal) * col);
    }

    return self;
}

Mat mat_cpy(const Mat self) {
    assert(self != NULL);

    const size_t col = mat_get_col(self);
    const size_t row = mat_get_row(self);

    Mat res = mat_new(row, col);

    for (size_t i = 0; i < row; ++i) {
        memcpy(res->val[i], self->val[i], sizeof(MatVal) * col);
    }

    return res;
}

Mat mat_del(Mat self) {
    assert(self != NULL);

    for (size_t i = 0; i < self->row; ++i) {
        free(self->val[i]);
    }

    free(self->val);

    free(self);

    return NULL;
}

size_t mat_get_col(const Mat self) {
    assert(self != NULL);

    return self->col;
}

size_t mat_get_row(const Mat self) {
    assert(self != NULL);

    return self->row;
}

MatVal mat_get_val(const Mat self, const size_t i, const size_t j) {
    assert(self != NULL);
    assert(i < mat_get_row(self));
    assert(j < mat_get_col(self));

    return self->val[i][j];
}

MatVal mat_set_val(Mat self, const size_t i, const size_t j, const MatVal v) {
    assert(self != NULL);
    assert(i < mat_get_row(self));
    assert(j < mat_get_col(self));

    self->val[i][j] = v;

    return v;
}

void mat_out(FILE* out, const Mat self) {
    assert(out != NULL);
    assert(self != NULL);

    fprintf(out, "[");

    const size_t col = mat_get_col(self);
    const size_t row = mat_get_row(self);

    for (size_t i = 0; i < row; ++i) {
        if (0 < i) {
            fprintf(out, ",\n ");
        }

        fprintf(out, "[");

        for (size_t j = 0; j < col; ++j) {
            if (0 < j) {
                fprintf(out, ",");
            }

            fprintf(out, "%8.5lf", mat_get_val(self, i, j));
        }

        fprintf(out, "]");
    }

    fprintf(out, "]\n");

    return;
}

Mat mat_add(const Mat a, const Mat b) {
    assert(a != NULL);
    assert(b != NULL);
    assert(mat_get_row(a) == mat_get_row(b));
    assert(mat_get_col(a) == mat_get_col(b));

    const size_t row = mat_get_row(a);
    const size_t col = mat_get_col(a);

    Mat res = mat_new(row, col);

    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            const MatVal av = mat_get_val(a, i, j);
            const MatVal bv = mat_get_val(b, i, j);

            mat_set_val(res, i, j, av + bv);
        }
    }

    return res;
}

Mat mat_sub(const Mat a, const Mat b) {
    assert(a != NULL);
    assert(b != NULL);
    assert(mat_get_row(a) == mat_get_row(b));
    assert(mat_get_col(a) == mat_get_col(b));

    const size_t row = mat_get_row(a);
    const size_t col = mat_get_col(a);

    Mat res = mat_new(row, col);

    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            const MatVal av = mat_get_val(a, i, j);
            const MatVal bv = mat_get_val(b, i, j);

            mat_set_val(res, i, j, av - bv);
        }
    }

    return res;
}

Mat mat_mul(const Mat a, const Mat b) {
    assert(a != NULL);
    assert(b != NULL);
    assert(mat_get_col(a) == mat_get_row(b));

    const size_t cnt = mat_get_col(a);
    const size_t row = mat_get_row(a);
    const size_t col = mat_get_col(b);

    Mat res = mat_new(row, col);

    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            for (size_t k = 0; k < cnt; ++k) {
                const MatVal v = mat_get_val(res, i, j);
                const MatVal d = mat_get_val(a, i, k) * mat_get_val(b, k, j);

                mat_set_val(res, i, j, v + d);
            }
        }
    }

    return res;
}
