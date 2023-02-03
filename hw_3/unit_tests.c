#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }         

    TEST(DynamicArray, Min) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 2.0;
        }
        x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 3.0;
        }
        x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 4.0;
        }
        ASSERT_EQ(DynamicArray_min(da),1.0);       
    }

    TEST(DynamicArray, Max) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 2.0;
        }
        x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 3.0;
        }
        x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 4.0;
        }
        ASSERT_EQ(DynamicArray_max(da),10.0);       
    }

    TEST(DynamicArray, Mean) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        ASSERT_EQ(DynamicArray_mean(da),5.5);       
    }

    TEST(DynamicArray, Median) {
        DynamicArray * da = DynamicArray_new();
        double x = 10.0;
        while ( x >= 1 ) {
            DynamicArray_push(da, x);  
            x -= 1.0;
        }
        ASSERT_EQ(DynamicArray_median(da),5.5);       
    }

    TEST(DynamicArray, Sum) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 2.0;
        }
        x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 3.0;
        }
        x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 4.0;
        }
        ASSERT_EQ(DynamicArray_sum(da),117.0);       
    }

    TEST(DynamicArray, FirstAndLast) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        ASSERT_EQ(DynamicArray_first(da),1.0);
        ASSERT_EQ(DynamicArray_last(da),10.0);
    }

    TEST(DynamicArray, Copy) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray * da_copy = DynamicArray_new();
        double x = 1.0;
        while ( x <= 10 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        da_copy = DynamicArray_copy(da);
        for(int i=0; i<da->end-da->origin;i++){
            ASSERT_EQ(DynamicArray_get(da,i),DynamicArray_get(da_copy,i));
        }
    }

    TEST(DynamicArray, Range) {
        DynamicArray * da = DynamicArray_new();
        da = DynamicArray_range(1.0,10.0,1.0);
        double x = 1.0;
        for(int i=0; i<da->end-da->origin;i++){
            ASSERT_EQ(DynamicArray_get(da,i),x);
            x += 1.0;
        }
    }

    TEST(DynamicArray, Concat) {
        DynamicArray * a = DynamicArray_range(0, 1, 0.1);
        DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
        DynamicArray * c = DynamicArray_concat(a, b);
        double x = 0.0;
        for(int i=0; i<c->end-c->origin;i++){
            ASSERT_DOUBLE_EQ(DynamicArray_get(c,i),x);
            x += 0.1;
        }
    }

    TEST(DynamicArray, Take) {
        DynamicArray * a = DynamicArray_range(1.0, 5.0, 1.0);

        DynamicArray * b = DynamicArray_take(a, 2);  /* yields [ 1, 2 ] */
        DynamicArray * b_expected = DynamicArray_range(1.0, 3.0, 1.0);
        for(int i=0; i<2;i++){
            ASSERT_EQ(DynamicArray_get(b,i),DynamicArray_get(b_expected,i));
        }

        DynamicArray * d = DynamicArray_take(a, 7);  /* yields [ 1, 2, 3, 4, 5, 0, 0 ] */
        DynamicArray * d_expected = DynamicArray_range(1.0, 5.0, 1.0);
        for(int i=0; i<2;i++){
            DynamicArray_push(d_expected, 0.0);
        }
        for(int i=0; i<7;i++){
            ASSERT_EQ(DynamicArray_get(d,i),DynamicArray_get(d_expected,i));
        }

        DynamicArray * c = DynamicArray_take(a, -2); /* yields [ 4, 5 ] */
        DynamicArray * c_expected = DynamicArray_range(4.0, 5.0, 1.0);
        for(int i=0; i<2;i++){
            ASSERT_EQ(DynamicArray_get(c,i),DynamicArray_get(c_expected,i));
        }

        DynamicArray * e = DynamicArray_take(a, -7); /* yields [ 0, 0, 1, 2, 3, 4, 5 ] */
        DynamicArray * e_exp = DynamicArray_range(1.0, 5.0, 1.0);
        for(int i=0; i<2;i++){
            DynamicArray_push_front(e_exp, 0.0);
        }
        for(int i=0; i<7;i++){
            ASSERT_EQ(DynamicArray_get(e,i),DynamicArray_get(e_exp,i));
        }
    }
}