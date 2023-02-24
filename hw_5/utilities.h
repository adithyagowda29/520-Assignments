#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include "typed_array.h"

using namespace std;

//Function to sort a vector by its magnitude in ascending order
void sort_by_magnitude(std::vector<double>& v);
//Function to read a CSV file and written it into a 2D TypedArray
TypedArray<TypedArray<double>> read_matrix_csv(const string path);
//Function to write a a 2D TypedArray into a CSV file
void write_matrix_csv(const TypedArray<TypedArray<double>> &matrix, const string path);
// Function to generate a map of strings with its number of occurences from a text file
map<string, int> occurrence_map(const string path);

#endif