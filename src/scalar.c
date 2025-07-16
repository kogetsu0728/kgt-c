#include "scalar.h"

Sca sca_rnd(const Sca min, const Sca max) {
    static bool init;

    if (!init) {
        srand(time(NULL));
        init = true;
    }

    ASSERT_LE(min, max);

    const Sca raw = rand();

    return raw * (max - min) / RAND_MAX + min;
}
