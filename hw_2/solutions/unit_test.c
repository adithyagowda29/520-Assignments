#include "solutions.h"
#include "gtest/gtest.h"

namespace {

    // 1. Test the function running_total
    TEST(HW2,RunningTotal) {
        ASSERT_EQ(running_total(1),  1);
        ASSERT_EQ(running_total(1),  2);
        ASSERT_EQ(running_total(5),  7);
        ASSERT_EQ(running_total(-3), 4);
    }

    // 2. Test the function reverse
    TEST(HW2,Reverse) {
        int x[] = {10,20,30,40,50};
        int * y = reverse(x,5);
        ASSERT_EQ(y[0],50);
        ASSERT_EQ(y[1],40);
        ASSERT_EQ(y[2],30);
        ASSERT_EQ(y[3],20);
        ASSERT_EQ(y[4],10);
        free(y);
    }

    // 3. Test the function reverse_in_place
    TEST(HW2,ReverseInPlace) {
        int x[] = {10,20,30,40,50};
        reverse_in_place(x,5);
        ASSERT_EQ(x[0],50);
        ASSERT_EQ(x[1],40);
        ASSERT_EQ(x[2],30);
        ASSERT_EQ(x[3],20);
        ASSERT_EQ(x[4],10);
    }

    // 4. Test the function num_occurences
    TEST(HW2,NumInstances) {
        int a[] = { 1, 1, 2, 3, 1, 4, 5, 2, 20, 5 };
        ASSERT_EQ(num_occurences(a,10,1), 3);
    }
}
