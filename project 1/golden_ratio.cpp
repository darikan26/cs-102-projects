/**
 * CS-102 Project 01: Calculates the golden ratio to a given precision.
 * @file golden_ratio.cpp
 * @author(s) Derya Arikan
 * @date Monday, January 30th
 */

# include <iostream>
#include <cmath>

const double GOLDEN_RATIO = 1.618033988749895;

/**
    * Returns the first ratio of two numbers in the fibonacci sequence 
    * that is less than the tolerance.
    * Prints the two numbers.
    * @param tolerance: tolerance as input by user.
    * @return fib_ratio.
    */
double return_fib_seq(double tolerance){
    int value1 = 1;
    int value2 = 1;
    double fib_ratio = (double)value2 / (double)value1;
    // Thanks to Hank E. for suggesting that I should use std:: before abs().
    while(std::abs(fib_ratio - GOLDEN_RATIO) > tolerance) {

        // PRINT STATEMENTS FOR TESTING. UNCOMMENT IF NEEDED.
        /*
        std::cout << "NOT WITHIN TOLERANCE." << '\n';
        std::cout << value1 << ' ' << value2 << '\n';
        std::cout << "fib_ratio = " << fib_ratio << '\n';
        std::cout << std::abs(fib_ratio - GOLDEN_RATIO) << " < " << tolerance << '\n';
        std::cout << '\n';
        */

        int new_value = value1 + value2;
        value1 = value2;
        value2 = new_value;

        // Thanks to Hank E. for suggesting that I should add (float) in front of the values
        // To prevent them from being rounded during division.
        fib_ratio = (double)value2 / (double)value1;
    }

    // UNCOMMENT PRINT STATEMENTS FOR TESTING IF NEEDED.
    //std::cout << "WITHIN TOLERANCE." << '\n';
    std::cout << value2 << " " << value1 << '\n';
    //std::cout << "fib_ratio = " << fib_ratio << '\n';
    //std::cout << std::abs(fib_ratio - GOLDEN_RATIO) << " < " << tolerance << '\n';
    return fib_ratio;
}

// Controls the operation of the program.
int main() {
    double tolerance = 0;
    // ask user for tolerance
    std::cout << "Enter a tolerance: ";
    std::cin >> tolerance;
    // feed tolerance into function that will print the two values, and return the ratio between them.
    return_fib_seq(tolerance);
    
}