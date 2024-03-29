#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    da->origin++;
    return value;    
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_new();
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(da, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

  assert(da->buffer != NULL);
  assert(b >= a);

  DynamicArray * result = DynamicArray_new();

  for (int i=a; i<b; i++) {
      DynamicArray_push(result,DynamicArray_get(da, i));
  }

  return result;

}

//Function to return the minimum element in the Dynamic Array
double DynamicArray_min ( const DynamicArray * da ){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    double min = DynamicArray_get(da,0);
    for(int i=0; i<da->end-da->origin;i++){
        if(min>DynamicArray_get(da,i)) {
            min = DynamicArray_get(da,i);
        }
    }
    return min;
}

//Function to return the maximum element in the Dynamic Array
double DynamicArray_max ( const DynamicArray * da ){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    double max = DynamicArray_get(da,0);
    for(int i=0; i<da->end-da->origin;i++){
        if(max<DynamicArray_get(da,i)) {
            max = DynamicArray_get(da,i);
        }
    }
    return max;
}

//Function to return the mean of all elements in the Dynamic Array
double DynamicArray_mean ( const DynamicArray * da ){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    double sum = 0.0;
    double mean;
    for(int i=0; i<da->end-da->origin;i++){
        sum += DynamicArray_get(da,i);
    }
    mean = sum / (da->end-da->origin);
    return mean;
}

//Function to return the median of all elements in the Dynamic Array
double DynamicArray_median ( const DynamicArray * da ){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    DynamicArray * result = DynamicArray_new();
    double temp = 0.0;
    for (int i = 0 ; i < da->end-da->origin; i++){
        DynamicArray_push(result,DynamicArray_get(da, i));
    }
    for (int i = 0; i < result->end-result->origin; i++){
        for (int j = i + 1 ; j < result->end-result->origin ; j++){
            if (DynamicArray_get(result, i) > DynamicArray_get(result, j)){
                temp = DynamicArray_get(result, i);
                DynamicArray_set(result, i, DynamicArray_get(result, j));
                DynamicArray_set(result, j, temp);
            }
        }
    }
    if ((result->end-result->origin) % 2 == 0)
        return (DynamicArray_get(result, (result->end-result->origin)/2-1) + DynamicArray_get(result, (result->end-result->origin)/2))/2.0;
    else
        return DynamicArray_get(result, (result->end-result->origin)/2);
}

//Function to return the sum of all elements in the Dynamic Array
double DynamicArray_sum ( const DynamicArray * da ){
    double sum = 0.0;
    for(int i=0; i<da->end-da->origin;i++){
        sum += DynamicArray_get(da,i);
    }
    return sum;
}

//Function to return the first of all elements in the Dynamic Array
double DynamicArray_first ( const DynamicArray * da ){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    return DynamicArray_get(da,0);
}

//Function to return the last of all elements in the Dynamic Array
double DynamicArray_last ( const DynamicArray * da ){
    assert(da->buffer != NULL);
    assert(DynamicArray_size(da) > 0);
    return DynamicArray_get(da,da->end-da->origin-1);
}

//Function to return the duplicate copy of the given Dynamic Array
DynamicArray * DynamicArray_copy ( const DynamicArray * da ){
    DynamicArray * result = DynamicArray_new();
    for(int i=0; i<da->end-da->origin;i++){
        DynamicArray_push(result,DynamicArray_get(da, i));
    }
    return result;
}

//Function to return the copy of the Dynamic Array in the given range 
DynamicArray * DynamicArray_range ( double a, double b, double step){
    DynamicArray * result = DynamicArray_new();
    for( double i=a; i<=b; i+=step){
        DynamicArray_push(result,i);
    }
    return result;
}

//Function to return the result of concatenation of two given Dynamic Arrays
DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b ){
    DynamicArray * result = DynamicArray_new();
    for(int i=0; i<a->end-a->origin;i++){
        DynamicArray_push(result,DynamicArray_get(a, i));
    }
    for(int j=0; j<b->end-b->origin;j++){
        DynamicArray_push(result,DynamicArray_get(b, j));
    }
    return result;
}

//Function to take first/last number of elements from given Dynamic Array and make it another Dynamic Array.
DynamicArray * DynamicArray_take(const DynamicArray * a, int n){
    DynamicArray * result = DynamicArray_new();
    if(n>0){
        if(n>=a->end-a->origin){
            for(int i=0; i<a->end-a->origin;i++){
                DynamicArray_push(result,DynamicArray_get(a, i));
            }
            for(int i=0; i<n-(a->end-a->origin);i++){
                DynamicArray_push(result,0.0);
            }
        }
        else{
            for(int i=0; i<n;i++){
                DynamicArray_push(result,DynamicArray_get(a, i));
            }
        } 
    }
    else{
        n=-n;
        if(n<a->end-a->origin){
            for(int i=(a->end-a->origin)-n; i<a->end-a->origin;i++){
                DynamicArray_push(result,DynamicArray_get(a, i));
            }
        }
        else{
            for(int i=0; i<n-(a->end-a->origin);i++){
                DynamicArray_push(result,0.0);
            }
            for(int i=0; i<a->end-a->origin;i++){
                DynamicArray_push(result,DynamicArray_get(a, i));
            }
        }
    }
    return result;
}