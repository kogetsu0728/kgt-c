#include "vector.h"

const Dim MAX_DIM = (1 << 20);

Vec vec_new(const Dim dim) {
    ASSERT_LT(dim, MAX_DIM);

    Vec self = malloc(sizeof(VecDat));
    ASSERT_NE_NULL(self);

    self->dim = dim;

    if (dim == 0) {
        self->val = NULL;
    } else {
        self->val = malloc(sizeof(Sca) * dim);
        ASSERT_NE_NULL(self->val);

        memset(self->val, 0, sizeof(Sca) * dim);
    }

    return self;
}

Vec vec_del(Vec self) {
    ASSERT_NE_NULL(self);

    if (self->dim > 0) {
        free(self->val);
    }

    free(self);

    return NULL;
}

Vec vec_cpy(const Vec self) {
    ASSERT_NE_NULL(self);

    Vec res = vec_new(self->dim);

    if (self->dim > 0) {
        memcpy(res->val, self->val, sizeof(Sca) * self->dim);
    }

    return res;
}

Dim vec_get_dim(const Vec self) {
    ASSERT_NE_NULL(self);

    return self->dim;
}

Sca vec_get_val(const Vec self, const Dim dim) {
    ASSERT_NE_NULL(self);
    ASSERT_LT(dim, vec_get_dim(self));

    return self->val[dim];
}

Sca vec_set_val(Vec self, const Dim dim, const Sca sca) {
    ASSERT_NE_NULL(self);
    ASSERT_LT(dim, vec_get_dim(self));

    return self->val[dim] = sca;
}

void vec_out(const Vec self, FILE* str) {
    ASSERT_NE_NULL(self);

    const Dim dim = vec_get_dim(self);

    fprintf(str, "[");

    for (Dim i = 0; i < dim; ++i) {
        if (0 < i) {
            fprintf(str, ",");
        }

        const Sca v = vec_get_val(self, i);

        fprintf(str, "%8.5lf", v);
    }

    fprintf(str, "]");

    return;
}

Vec vec_add(const Vec lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(vec_get_dim(lhs), vec_get_dim(rhs));

    const Dim dim = vec_get_dim(lhs);

    Vec res = vec_new(dim);

    for (Dim i = 0; i < dim; ++i) {
        const Sca vl = vec_get_val(lhs, i);
        const Sca vr = vec_get_val(rhs, i);

        vec_set_val(res, i, vl + vr);
    }

    return res;
}

Vec vec_sub(const Vec lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(vec_get_dim(lhs), vec_get_dim(rhs));

    const Dim dim = vec_get_dim(lhs);

    Vec res = vec_new(dim);

    for (Dim i = 0; i < dim; ++i) {
        const Sca vl = vec_get_val(lhs, i);
        const Sca vr = vec_get_val(rhs, i);

        vec_set_val(res, i, vl - vr);
    }

    return res;
}

Vec vec_mul(const Vec lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(vec_get_dim(lhs), vec_get_dim(rhs));

    const Dim dim = vec_get_dim(lhs);

    Vec res = vec_new(dim);

    for (Dim i = 0; i < dim; ++i) {
        const Sca vl = vec_get_val(lhs, i);
        const Sca vr = vec_get_val(rhs, i);

        vec_set_val(res, i, vl * vr);
    }

    return res;
}

Vec vec_div(const Vec lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(vec_get_dim(lhs), vec_get_dim(rhs));

    const Dim dim = vec_get_dim(lhs);

    Vec res = vec_new(dim);

    for (Dim i = 0; i < dim; ++i) {
        const Sca vl = vec_get_val(lhs, i);
        const Sca vr = vec_get_val(rhs, i);

        vec_set_val(res, i, vl / vr);
    }

    return res;
}

Sca vec_dot(const Vec lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);
    ASSERT_EQ(vec_get_dim(lhs), vec_get_dim(rhs));

    const Dim dim = vec_get_dim(lhs);

    Sca res = 0;

    for (Dim i = 0; i < dim; ++i) {
        const Sca vl = vec_get_val(lhs, i);
        const Sca vr = vec_get_val(rhs, i);

        res += vl * vr;
    }

    return res;
}

Vec vec_add_sca(const Vec lhs, const Sca rhs) {
    ASSERT_NE_NULL(lhs);

    const Dim dim = vec_get_dim(lhs);

    Vec res = vec_new(dim);

    for (Dim i = 0; i < dim; ++i) {
        const Sca vl = vec_get_val(lhs, i);
        const Sca vr = rhs;

        vec_set_val(res, i, vl + vr);
    }

    return res;
}

Vec vec_sub_sca(const Vec lhs, const Sca rhs) {
    ASSERT_NE_NULL(lhs);

    const Dim dim = vec_get_dim(lhs);

    Vec res = vec_new(dim);

    for (Dim i = 0; i < dim; ++i) {
        const Sca vl = vec_get_val(lhs, i);
        const Sca vr = rhs;

        vec_set_val(res, i, vl - vr);
    }

    return res;
}

Vec vec_mul_sca(const Vec lhs, const Sca rhs) {
    ASSERT_NE_NULL(lhs);

    const Dim dim = vec_get_dim(lhs);

    Vec res = vec_new(dim);

    for (Dim i = 0; i < dim; ++i) {
        const Sca vl = vec_get_val(lhs, i);
        const Sca vr = rhs;

        vec_set_val(res, i, vl * vr);
    }

    return res;
}

Vec vec_div_sca(const Vec lhs, const Sca rhs) {
    ASSERT_NE_NULL(lhs);

    const Dim dim = vec_get_dim(lhs);

    Vec res = vec_new(dim);

    for (Dim i = 0; i < dim; ++i) {
        const Sca vl = vec_get_val(lhs, i);
        const Sca vr = rhs;

        vec_set_val(res, i, vl / vr);
    }

    return res;
}

bool vec_eq(const Vec lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);

    const Dim dl = vec_get_dim(lhs);
    const Dim dr = vec_get_dim(rhs);

    if (dl != dr) {
        return false;
    }

    for (Dim i = 0; i < dl; ++i) {
        const Sca vl = vec_get_val(lhs, i);
        const Sca vr = vec_get_val(rhs, i);

        if (vl != vr) {
            return false;
        }
    }

    return true;
}

bool vec_ne(const Vec lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);

    const bool eq = vec_eq(lhs, rhs);

    return !eq;
}

bool vec_gt(const Vec lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);

    const Dim dl = vec_get_dim(lhs);
    const Dim dr = vec_get_dim(rhs);

    const Dim dm = GET_MAX(dl, dr);

    for (Dim i = 0; i < dm; ++i) {
        if (i >= dl) {
            return false;
        }

        if (i >= dr) {
            return true;
        }

        const Sca vl = vec_get_val(lhs, i);
        const Sca vr = vec_get_val(rhs, i);

        if (vl < vr) {
            return false;
        }

        if (vl > vr) {
            return true;
        }
    }

    return false;
}

bool vec_ge(const Vec lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);

    const bool eq = vec_eq(lhs, rhs);
    const bool gt = vec_gt(lhs, rhs);

    return (gt || eq);
}

bool vec_lt(const Vec lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);

    return vec_gt(rhs, lhs);
}

bool vec_le(const Vec lhs, const Vec rhs) {
    ASSERT_NE_NULL(lhs);
    ASSERT_NE_NULL(rhs);

    return vec_ge(rhs, lhs);
}
