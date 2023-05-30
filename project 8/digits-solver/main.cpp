/*
* CS-102 Project 8: Digits Solver: Solves the game Digits. 
*                                  Digits is a daily numbers puzzle from the New York Times.
*                                  It can be found at https://www.nytimes.com/games/digits.
* @file main.cpp
* @authors Derya Arikan
           Peter Ryan
* @collaborators rathbhupendra (GeeksForGeeks.org)
* @date May 3, 2023 
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "stack.h"
#include "node.h"

using namespace std;

/// @brief Operator overload for printing vectors.
/// @param output The output.
/// @param vec The vector that is to be printed.
/// @return Output.
ostream &operator<<(ostream &output, vector<int> vec) {
    for (int number : vec) {
        output << number << ' ';
    }
    return output;
}

/// @brief Converts an integer from base 10 to base 4. 
/// @param b10 An integer in base 10.
/// @return A number in base 4 as string. 
string base10_to_base4(int b10) {
    string b4;
    while (b10 != 0) {
        b4 = to_string(b10 % 4) + b4;
        b10 = (b10 - (b10 % 4)) / 4;
    }
    return b4;
}

/// @brief Generates all possible operation orderings as stacks of integers, with 
/// numbers from 0 to 3 representing one of four operations.    
/// @param all_operations Vector that contains stacks of operation orders. 
void permute_operations(vector<Stack> &all_operations) {
    vector<string> str_operations;          // Create a vector<string> that is
    for (int i = 0; i < 1024; i++) {        // a base4 number with five zeros,
        string base4 = base10_to_base4(i);  // adding as many leading zeros
        int len = base4.length();           // as necessary.
        for (int j = 0; j < 5 - len; j++) {
            base4 = "0" + base4;
        }
        str_operations.push_back(base4);
    }

    for (size_t i = 0; i < str_operations.size(); i++) {            // Convert the vector<string> 
        Stack operation_stack;                                      // into vector<stack>
        for (size_t j = 0; j < str_operations[i].length(); j++) {
            operation_stack.push(int(str_operations[i][j] - '0'));
        }
        all_operations.push_back(operation_stack);
    }
}

/// @brief Recursively generates all possible orderings of the contents of digits, and
/// pushes the stacks onto all_digits by reference.  
/// @param digits The vector of digits read from the input file. 
/// @param l Left bound of the vector that is being shuffled.
/// @param r Right bound of the vector that is being shuffled. 
/// @param all_digits Vector that contains stacks of digit orders.
/// @cite This code is adapted from 
/// https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
void permute( vector<int> &digits, int l, int r, vector<Stack> &all_digits ) { 
    if (l == r) { // Base case
        Stack digits_stack;                     
        for (size_t i = 0; i < digits.size(); i++) {    // Convert vector<int> into stack
            digits_stack.push(digits[i]);
        }
        all_digits.push_back(digits_stack);             // push_back the stack onto vector<stack>
    } else {
        
        for (int i = l; i <= r; i++) {              // Permutations made
            swap(digits[l], digits[i]);             // Swapping done
            permute(digits, l + 1, r, all_digits);  // Recursion called
            swap(digits[l], digits[i]);             // Swap back
        }
    }
}

/// @brief Given an integer that represents an operation, performs that operation
/// on integers x and y. 
/// @param x The left entry of the operation. 
/// @param y The right entry of the operation. 
/// @param operation An integer that represents an operation. 0 for addition, 1 for
/// subtraction, 2 for division, and 3 for multiplication. 
/// @param verbose Prints the operations if true. 
/// @return Non-negative integer result of the operation. If performing the operation
/// yields a negative integer or a fraction, returns -1 to indicate the operation result
/// is invalid. 
int operate(int x, int y, int operation, bool verbose) {
    if (operation == 0) { // Addition
        if (verbose) {
            cout << x << " + " << y << " = " << x + y << endl;
        }
        return x + y;
    }

    if (operation == 1) { // Subtraction
        if (y > x) {
        if (verbose) { 
            cout << y << '>' << x << "invalid subtraction output" << endl;
        }
        return -1;
        }
        if (verbose) { 
            cout << x << " - " << y << " = " << x - y << endl;
        }
        return x - y;
    }

    if (operation == 2) { // Division
        if (x % y != 0) {
        if (verbose) {
            cout << x << '%' << y << "!= 0 invalid division output" << endl;
        }
        return -1;
        }
        if (verbose) { 
            cout << x << " / " << y << " = " << x / y << endl;
        }
        return x / y;
    }
    
    if (operation == 3) { // Multiplication
        if (verbose) { 
            cout << x << " * " << y << " = " << x * y << endl;
        }
        return x * y;
    }
    return -1;
}

/// @brief Calculates the result of the operation given an order of digits and operations. 
/// @param digits A stack of ordered digits. 
/// @param operations A stack of ordered operations. 
/// @param target The target number.
/// @param verbose If true, operations will be printed. 
/// @return Target, if it is found. If not, returns the result of the operations. 
/// Returns -1 if the operations yield a fraction, or a negative integer. 
int calculate_result(Stack digits, Stack operations, int target, bool verbose) {
    int len = operations.get_size();
    for (int k = 0; k < len; k++) {

        int x = digits.pop();
        int y = digits.pop();

        int operation = operations.pop();

        int operation_result = operate(x, y, operation, verbose);

        if (operation_result == -1) {
          return -1;
        }

        digits.push(operation_result);
        if (operation_result == target) {
            return target;
        }
    }
    return digits.pop();
}

/// @brief Function that checks if the target integer is found in a given digit and operation order.
/// @param digits A stack of ordered digits.  
/// @param operations A stack of ordered operations. 
/// @param target The target number. 
/// @return True if the target is found.
bool target_is_found(Stack digits, Stack operations, int target) {
    if (calculate_result(digits, operations, target, false) == target) {
        return true;
    } 
    return false;
}

/// @brief Solves digits.
/// @param o Vector that contains stacks of operation orders. 
/// @param d Vector that contains stacks of digit orders.
/// @param target The target number. 
void solve_digits(vector<Stack> o, vector<Stack> d, int target) {
    for (size_t i = 7; i < o.size(); i++) {     // For every possible operation order
        for (size_t j = 0; j < d.size(); j++) {     // For every possible digit order

            Stack digits = d[j];
            Stack operations = o[i];

            if (target_is_found(digits, operations, target)) { // If targeting is found,
                calculate_result(d[j], o[i], target, true);        // print the operations 
                return;                                            // that return the target
            }
        }
    }
}

/// @brief Reads input from file, creates the digit and operation orderings, 
/// and solves digits. 
/// @param file_name Name of the input file. 
void test_from_file(string file_name) {
    ifstream the_file(file_name);

    if( !the_file.is_open()){
        cout << "File not found: " << file_name << endl;
        throw invalid_argument("File not found: " + file_name);
    }
    
    int item;               // Read from file the digits
                            // and the target
    vector<int> digits;
    for (int i = 0; i < 6; i++) {
        the_file >> item;
        digits.push_back(item);
    }
    int target;
    the_file >> target;

    cout << '\n' << "DIGITS:\n" << digits << '\n' << endl;
    cout << "TARGET:\n" << target << '\n' << endl;

    vector<Stack> all_operations;        // Create all possible operation orders
    permute_operations(all_operations);  // i.e. +++++, ++++-, ++++/, ++++*, +++-+ ...

    vector<Stack> all_digits;                           // Create all possible orderings of digits
    permute(digits, 0, digits.size() - 1, all_digits);  // i.e. 1 2 3 4 5 6, 2 1 3 4 5 6, ...

    cout << "SOLUTION:" << endl;
    solve_digits(all_operations, all_digits, target); // Solve digits
    cout << '\n';
}

/// @brief Controls program flow.
/// @param argc Argument count
/// @param argv Argument vector
int main(int argc, char ** argv) {
    if (argc != 2) { 
        cout << "usage: " << argv[0] << " <commands file name>" << endl;
        exit(1);
    }
    string test_file = argv[1];
    test_from_file(test_file);
}
