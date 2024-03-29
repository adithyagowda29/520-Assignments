#ifndef TYPED_ARRAY
#define TYPED_ARRAY

#include <assert.h>
#include <iostream>
#include <stdexcept>

template <typename ElementType>
class TypedArray {

public:

    TypedArray();
    TypedArray(const TypedArray& other);

    // Copy constructor
    TypedArray& operator=(const TypedArray& other);

    // Destructor
    ~TypedArray();

    // Getters
    ElementType &get(int index);
    ElementType &safe_get(int index) const;
    int size() const;

    // Setters
    void set(int index, ElementType value);
    
    // Push Function
    void push(ElementType value);
    // Pop Function
    ElementType pop();
    // Push Front Function
    void push_front(ElementType value);
    // Pop Front Function
    ElementType pop_front();

    // Concatenation Function
    TypedArray concat(const TypedArray& other);
    // Function to Reverse Array
    TypedArray reverse();

    // Function to Concatenate Arrays with Overload
    TypedArray operator+(const TypedArray& other);

private:

    int capacity,
        origin,
        end;

    ElementType * buffer;   

    const int INITIAL_CAPACITY = 10;

    int index_to_offset(int index) const;
    int offset_to_index(int offset) const;
    bool out_of_buffer(int offset) const;
    void extend_buffer(void);    

};

template <typename ElementType>
TypedArray<ElementType>::TypedArray() {
    buffer = new ElementType[INITIAL_CAPACITY]();
    capacity = INITIAL_CAPACITY;    
    origin = capacity / 2;
    end = origin;    
}

// Copy constructor: i.e TypedArray b(a) where a is a TypedArray
template <typename ElementType>
TypedArray<ElementType>::TypedArray(const TypedArray& other) : TypedArray() {
    *this = other;
}

// Assignment operator: i.e TypedArray b = a 
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::operator=(const TypedArray<ElementType>& other) {
    if ( this != &other) {
        delete[] buffer; // don't forget this or you'll get a memory leak!
        buffer = new ElementType[other.capacity]();
        capacity = other.capacity;
        origin = other.origin;
        end = origin;
        for ( int i=0; i<other.size(); i++) {
            set(i,other.safe_get(i));
        }
    }
    return *this;
}

// Destructor
template <typename ElementType>
TypedArray<ElementType>::~TypedArray() {
    delete[] buffer;
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::get(int index) {
    if (index < 0) {
        throw std::range_error("Out of range index in array");
    }
    if ( index >= size() ) {
        ElementType x;
        set(index, x);
    } 
    return buffer[index_to_offset(index)];
}

// Getters
template <typename ElementType>
ElementType &TypedArray<ElementType>::safe_get(int index) const {
    if (index < 0 || index >= size() ) {
        throw std::range_error("Out of range index in array");
    }
    return buffer[index_to_offset(index)];
}

template <typename ElementType>
int TypedArray<ElementType>::size() const {
    return end - origin;
}

// Setters
template <typename ElementType>
void TypedArray<ElementType>::set(int index, ElementType value) {
    if (index < 0) {
        throw std::range_error("Negative index in array");
    }
    while ( out_of_buffer(index_to_offset(index) ) ) {
        extend_buffer();
    }
    buffer[index_to_offset(index)] = value; // Should call the copy constructor
                                            // of ElementType.
    if ( index >= size() ) {
        end = index_to_offset(index+1);
    }
}

template <typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedArray<ElementType> &array)
{
    os << '[';
    for (int i=0; i<array.size(); i++ ) {
        os << array.get(i);
        if ( i < array.size() - 1 ) {
            os << ",";
        }
    }
    os << ']';
    return os;
}

// Private methods

template <typename ElementType>
int TypedArray<ElementType>::index_to_offset ( int index ) const {
    return index + origin;
}

/* Position of the element at buffer position 'offset' */
template <typename ElementType>
int TypedArray<ElementType>::offset_to_index ( int offset ) const  {
    return offset - origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
template <typename ElementType>
bool TypedArray<ElementType>::out_of_buffer ( int offset ) const {
    return offset < 0 || offset >= capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
template <typename ElementType>
void TypedArray<ElementType>::extend_buffer() {

    auto temp = new ElementType[2 * capacity]();
    int new_origin = capacity - (end - origin)/2,
           new_end = new_origin + (end - origin);

    for ( int i=0; i<size(); i++ ) {
        temp[new_origin+i] = get(i);
    }

    delete[] buffer;
    buffer = temp;

    capacity = 2 * capacity;
    origin = new_origin;
    end = new_end;

    return;

}

// Solutions:

// Function to Push a value at the end of the Array
template <typename ElementType>
void TypedArray<ElementType>::push(ElementType value){
    set(size(),value);
}

// Function to Pop/Remove the value at the end of the Array
template <typename ElementType>
ElementType TypedArray<ElementType>::pop(){
    if (size() <= 0) {
        throw std::range_error("Negative index in array");
    }
    ElementType value = safe_get(size()-1);
    end = index_to_offset(size()-1);
    return value;
}

// Function to Push a value at the start of the Array
template <typename ElementType>
void TypedArray<ElementType>::push_front(ElementType value){
    for(int i=size()-1; i>=0; i--) {
        set(i+1,safe_get(i));
    }
    set(0, value);
    end = index_to_offset(size()+1);
}

// Function to Pop/Remove the value at the start of the Array
template <typename ElementType>
ElementType TypedArray<ElementType>::pop_front(){
    if (size() <= 0) {
        throw std::range_error("Negative index in array");
    }
    ElementType value = safe_get(0);
    for(int i=0; i<size()-1; i++) {
        set(i,safe_get(i+1));
    }
    end = index_to_offset(size()-1);
    return value;
}

// Function to concatenate two Arrays
template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::concat(const TypedArray& other){
    TypedArray<ElementType> result;
    result.buffer = new ElementType[size() + other.size()]();
    result.capacity = size() + other.size();
    result.origin = origin;
    result.end = size() + other.size();
    for (int i=0; i<size(); i++) {
        result.set(i,safe_get(i));
    }
    for (int i=size(); i<size()+other.size(); i++) {
        result.set(i,other.safe_get(i-size()));
    }
    return result;
}

// Function to Reverse an Array
template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::reverse(){
    for (int i=0; i<size()/2; i++) {
        ElementType value = safe_get(i);
        set(i,safe_get(size()-i-1));
        set(size()-i-1,value);
    }
    return *this;
}

// Function to concatenate two Arrays
// Assignment operator: i.e TypedArray a + b
template <typename ElementType>
TypedArray<ElementType> TypedArray<ElementType>::operator+(const TypedArray<ElementType>& other) {
    TypedArray<ElementType> result;
    result.buffer = new ElementType[size() + other.size()]();
    result.capacity = size() + other.size();
    result.origin = origin;
    result.end = size() + other.size();
    for (int i=0; i<size(); i++) {
        result.set(i,safe_get(i));
    }
    for (int i=size(); i<size()+other.size(); i++) {
        result.set(i,other.safe_get(i-size()));
    }
    return result;
}

#endif