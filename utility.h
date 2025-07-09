#ifndef UTILITY_H
#define UTILITY_H

#include <assert.h>

#define ASSERT_EQ(a, b) assert((a) == (b))
#define ASSERT_NE(a, b) assert((a) != (b))

#define ASSERT_LT(a, b) assert((a) < (b))
#define ASSERT_LE(a, b) assert((a) <= (b))

#define ASSERT_GT(a, b) assert((a) > (b))
#define ASSERT_GE(a, b) assert((a) >= (b))

#define ASSERT_BT(a, b, c) assert((a) >= (b) && (a) < (c))

#define ASSERT_NE_NULL(a) ASSERT_NE((a), NULL)

#define GET_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define GET_MAX(a, b) (((a) > (b)) ? (a) : (b))

#endif
