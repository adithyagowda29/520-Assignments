#include <fstream>
#include <sstream>
#include "utilities.h"
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

//Function to sort a vector by its magnitude in ascending order
void sort_by_magnitude(vector<double>& v) {
  //lambda function is used here
  sort(v.begin(), v.end(), [](double x, double y) {
    return abs(x) < abs(y);
  });
}

//Function to read a CSV file and written it into a 2D TypedArray
TypedArray<TypedArray<double>> read_matrix_csv(const string path) {
    ifstream infile(path);
    TypedArray<TypedArray<double>> matrix;
    string line;
    //Read the CSV file cell by cell
    while (getline(infile, line)) {
        TypedArray<double> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            if (cell.empty()) { // if any cell is empty -> throw error
                throw invalid_argument("CSV file has an incomplete matrix.");
            }
            row.set(row.size(), stod(cell));
        }
        if (matrix.size() > 0 && row.size() != matrix.safe_get(0).size()) { // if current row size and the matrix first row size is not equal -> throw error
            throw invalid_argument("CSV file has a jagged matrix.");
        }
        matrix.set(matrix.size(), row);
    }
    if (matrix.size() == 0) { // if matrix is empty -> throw error
        throw invalid_argument("CSV file represents an empty matrix.");
    }
    return matrix;
}

//Function to write a a 2D TypedArray into a CSV file
void write_matrix_csv(const TypedArray<TypedArray<double>> &matrix, const string path) {
    ofstream outfile(path);
    for (int i = 0; i < matrix.size(); i++) {
        TypedArray<double> row = matrix.safe_get(i);
        for (int j = 0; j < row.size(); j++) {
            outfile << row.safe_get(j);
            if (j < row.size() - 1) {
                outfile << ",";
            }
        }
        outfile << endl;
    }
}

// Function to generate a map of strings with its number of occurences from a text file
map<string, int> occurrence_map(const string path) {
    ifstream infile(path);
    map<string, int> occ_map;
    string line;
    while (getline(infile, line)) {
        // Adding a whitespace to handle the last word in the line
        line += ' '; 
        cout<<line<<endl;
        string word = "";
        for (int i = 0; i < line.length(); i++) {
            bool is_word = true;
            if(line[i]!=' '){
                // Convert to lowercase
                word += tolower(line[i]); 
            }
            else if (word.length() > 0 && line[i] == ' ') {
                // Check if last character of the word is '.' and ':' and remove them
                if(word[word.length()-1]=='.' || word[word.length()-1]==':'){ 
                    word.erase(word.length()-1,1);
                }
                for (int i = 0; i < word.length(); i++) {
                    // Check if invalid word and dont count them
                    if(!(isalnum(word[i]) || word[i] == '\'' || word[i] == '"')){ 
                        is_word = false;
                        break;
                    }
                }
                if(is_word == true){
                    // Check if first character of word is ' or " and remove them
                    if(word[0]=='\'' || word[0] == '"'){ 
                            word.erase(0,1);
                    }
                    // Check if first character of word is ' or "  and remove them
                    if(word[word.length()-1]=='\'' || word[word.length()-1]=='"'){ 
                        word.erase(word.length()-1,1);
                    }
                    // Check if word is empty after removing all quotes and dont count empty words
                    if(word==""){ 
                        continue;
                    }
                    // Add word to map
                    occ_map[word]++;
                }
                // Initialise to empty for next word.
                word = "";
            }
        }
    }
    return occ_map;
}