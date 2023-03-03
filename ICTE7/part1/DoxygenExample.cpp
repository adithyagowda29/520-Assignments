/**
 * @file main.cpp
 * @brief A sample C++ program optimized for Doxygen documentation.
 */

#include <iostream>

/**
 * @class Calculator
 * @brief A simple calculator class.
 * 
 * This class can add, subtract, multiply, and divide two numbers.
 */
class Calculator {
public:
    /**
     * @brief Adds two numbers.
     * 
     * @param a The first number.
     * @param b The second number.
     * @return The sum of the two numbers.
     */
    double add(double a, double b) {
        return a + b;
    }
    
    /**
     * @brief Subtracts two numbers.
     * 
     * @param a The first number.
     * @param b The second number.
     * @return The difference between the two numbers.
     */
    double subtract(double a, double b) {
        return a - b;
    }
    
    /**
     * @brief Multiplies two numbers.
     * 
     * @param a The first number.
     * @param b The second number.
     * @return The product of the two numbers.
     */
    double multiply(double a, double b) {
        return a * b;
    }
    
    /**
     * @brief Divides two numbers.
     * 
     * @param a The first number.
     * @param b The second number.
     * @return The quotient of the two numbers.
     * 
     * @throw std::invalid_argument if b is zero.
     */
    double divide(double a, double b) {
        if (b == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return a / b;
    }
};

/**
 * @brief Main function.
 * 
 * @return Exit code.
 */
int main() {
    Calculator calc;
    double a = 10;
    double b = 5;
    double sum = calc.add(a, b);
    double diff = calc.subtract(a, b);
    double prod = calc.multiply(a, b);
    double quot = calc.divide(a, b);
    
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "a + b = " << sum << std::endl;
    std::cout << "a - b = " << diff << std::endl;
    std::cout << "a * b = " << prod << std::endl;
    std::cout << "a / b = " << quot << std::endl;
    
    return 0;
}
