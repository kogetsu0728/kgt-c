#ifndef SCALAR_H
#define SCALAR_H

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "utility.h"

typedef double Sca;
typedef Sca (*ScaFnc)(const Sca);

Sca sca_rnd(const Sca, const Sca);

#endif
