/**
 * CS-102 Project 01: Calculates a row of Pascal's Triangle.
 * @file pascals_triangle.cpp
 * @author darikan26 (Derya Arikan)
 * @collaborators
 * @date 30 Jan 2023
 */

#include <iostream>
#include <cmath>

/**
 * Compute and return n! = n * (n - 1) * ... * 1
 * @param n the value n, for which we want to compute n!
 * @return n!
 */
long factorial(int n) {
    long nfactorial = 1;
    for (int i = 1; i <= n; i++) {
        nfactorial = nfactorial * i;
    }
    return nfactorial;
}

/**
 * Calculate and return (n!) / (k!*(n-k)!), kth number on nth row
 * @param n the value n, the number of the row the entry is on 
 * @param k the value k, the number of the entry
 * @return (n!) / (k!*(n-k)!)
 */
long calculate_entry(int k, int n) {
    long nfactorial = factorial(n);                         // n!
    long kfactorial = factorial(k);                         // k!
    int dif = std::abs(n-k);
    long diffactorial = factorial(dif);                     // (n-k)!
    long entry = nfactorial / (kfactorial * diffactorial);  // (n!) / (k!*(n-k)!)
    return entry;
}

/**
 * Calculate each entry in row and print them
 * @param n the value n, the row number input by the user
 * @return 0
 * prints each number on the row number input by the user
 */
int return_row(int n) {
    for (int k = 0; k <= n; k++) {
        long entry = calculate_entry(k, n);
        if (k != n) {
            std::cout << entry << ' ';
        } else {
            std::cout << entry << '\n';
        }

    }
    return 0;
}

// Controls the operation of the program.
int main() {
    int n = 0;
    std::cout << "Enter n: ";
    std::cin >> n;
    return_row(n);
    return 0;
}