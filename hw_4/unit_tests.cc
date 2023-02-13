#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "complex.h"
#include "gtest/gtest.h"

namespace {

    //Test functions for Typed Arrays

    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,3*i+j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
            }
        }

    }

    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,0);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                               // then we would expect m[0][0]
                                               // to be x[0], which we changed 
                                               // to -1.
    }

    TEST(TypedArray,Push) {
        TypedArray<int> a;
        a.set(0,1);
        a.set(1,2);
        a.set(2,3);
        a.push(4);
        EXPECT_EQ(a.safe_get(0), 1);
        EXPECT_EQ(a.safe_get(1), 2);
        EXPECT_EQ(a.safe_get(2), 3);
        EXPECT_EQ(a.safe_get(3), 4);
    }

    TEST(TypedArray,Pop) {
        TypedArray<int> a;
        a.set(0,1);
        a.set(1,2);
        a.set(2,3);
        EXPECT_EQ(a.pop(),3);
        EXPECT_EQ(a.safe_get(0), 1);
        EXPECT_EQ(a.safe_get(1), 2);
    }

    TEST(TypedArray,PushFront) {
        TypedArray<int> a;
        a.set(0,1);
        a.set(1,2);
        a.set(2,3);
        a.push_front(4);
        EXPECT_EQ(a.safe_get(0), 4);
        EXPECT_EQ(a.safe_get(1), 1);
        EXPECT_EQ(a.safe_get(2), 2);
        EXPECT_EQ(a.safe_get(3), 3);
    }

    TEST(TypedArray,PopFront) {
        TypedArray<int> a;
        a.set(0,1);
        a.set(1,2);
        a.set(2,3);
        EXPECT_EQ(a.pop_front(),1);
        EXPECT_EQ(a.safe_get(0), 2);
        EXPECT_EQ(a.safe_get(1), 3);
    }

    TEST(TypedArray,Concat) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b = a.concat(a).concat(a);
        EXPECT_EQ(b.size(), 6);
        EXPECT_EQ(b.safe_get(0), 0);
        EXPECT_EQ(b.safe_get(1), 1);
        EXPECT_EQ(b.safe_get(2), 0);
        EXPECT_EQ(b.safe_get(3), 1);
        EXPECT_EQ(b.safe_get(4), 0);
        EXPECT_EQ(b.safe_get(5), 1);
    }

    TEST(TypedArray,Reverse) {
        TypedArray<int> a;
        a.set(0,1);
        a.set(1,2);
        a.set(2,3);
        a = a.reverse();
        EXPECT_EQ(a.safe_get(0), 3);
        EXPECT_EQ(a.safe_get(1), 2);
        EXPECT_EQ(a.safe_get(2), 1);
    }

    TEST(TypedArray,ConcatOverload) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b = a + a + a;
        EXPECT_EQ(b.size(), 6);
        EXPECT_EQ(b.safe_get(0), 0);
        EXPECT_EQ(b.safe_get(1), 1);
        EXPECT_EQ(b.safe_get(2), 0);
        EXPECT_EQ(b.safe_get(3), 1);
        EXPECT_EQ(b.safe_get(4), 0);
        EXPECT_EQ(b.safe_get(5), 1);
    }

    //Test functions for Complex numbers
    TEST(Examples,Complex) {
        Complex x(1,2), y(3);
    }

    template<typename T>
    int compare(const T& x, const T& y) {
        if ( x < y ) {
            return -1;
        } else if ( y < x ) {
            return 1;
        } else {
            return 0;
        }
    }    

    TEST(Examples,Templates) {
        EXPECT_EQ(compare(1.0, 2.0), -1);
        EXPECT_EQ(compare(Complex(5,4), Complex(-3,4)), 1);
    }

    TEST(ComplexTest, Conjugate) {
        Complex c1(5, 10);
        Complex c2 = c1.conjugate();
        EXPECT_EQ(c2.real(), 5);
        EXPECT_EQ(c2.imag(), -10);
    }

    TEST(ComplexTest, Addition) {
        Complex c1(1, 2);
        Complex c2(3, 4);
        Complex c3 = c1 + c2;
        EXPECT_EQ(c3.real(), 4);
        EXPECT_EQ(c3.imag(), 6);
    }

    TEST(ComplexTest, Multiplication) {
        Complex c1(1, 2);
        Complex c2(3, 4);
        Complex c3 = c1 * c2;
        EXPECT_EQ(c3.real(), -5);
        EXPECT_EQ(c3.imag(), 10);
    }

    TEST(ComplexTest, Equality) {
        Complex c1(1, 2);
        Complex c2(1, 2);
        Complex c3(1, 3);
        EXPECT_TRUE(c1 == c2);
        EXPECT_FALSE(c1 == c3);
    }
}