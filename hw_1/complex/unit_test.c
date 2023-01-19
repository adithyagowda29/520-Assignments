#include "complex.h"
#include <math.h>
#include "gtest/gtest.h"

namespace {

    TEST(Complexs, BasicsAdd) {
        Complex a = (Complex) { 2.0, 3.0 },
                 b = (Complex) { 4.0, 5.0 };
        EXPECT_DOUBLE_EQ(add(a,b).real,6.0);
        EXPECT_DOUBLE_EQ(add(a,b).im,8.0);
    }

    TEST(Complexs, BasicsNegate) {
        Complex a = (Complex) { 2.0, 3.0 };
        EXPECT_DOUBLE_EQ(negate(a).real,-2.0);
        EXPECT_DOUBLE_EQ(negate(a).im,-3.0);
    }

    TEST(Complexs, BasicsMult) {
        Complex a = (Complex) { 2.0, 3.0 },
                 b = (Complex) { 4.0, 5.0 };
        EXPECT_DOUBLE_EQ(multiply(a,b).real,-7.0);
        EXPECT_DOUBLE_EQ(multiply(a,b).im,22.0);
    }

    TEST(Complexs, BasicsMagnitude) {
        Complex a = (Complex) { 2.5, 3.5 };
        EXPECT_DOUBLE_EQ(magnitude(a), 4.3011626335213133);
    }
}
