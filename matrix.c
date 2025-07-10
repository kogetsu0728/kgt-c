#include "matrix.h"

Mat mat_new(const Dim row, const Dim col) {
    ASSERT_LT(row, MAX_DIM);
    ASSERT_LT(col, MAX_DIM);

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
