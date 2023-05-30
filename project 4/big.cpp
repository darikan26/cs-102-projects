/**
 * CS-102 Project 04: A program that reads a mathematical operator along 
 * with a pair of numbers from a text file, then produces the desired result.
 * @file big.cpp
 * @author(s) Derya Arikan
 * @date Monday, February 20th
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// GLOBAL VARIABLES
string OPERATOR, NUMBER1, NUMBER2;

/// @brief Takes string input of a number, and cuts off the leading zeros
/// @param s String input composed of numeric characters
/// @return String output composed of numeric characters without leading zeros
string cut_leading_zeros(string s) {
    bool done = false;
    //int i = 0;
    while (!done)  {
        if (s[0] != '0' or s.length() == 1) {
            done = true;     
        } else {
            s.erase(0, 1);
        }
        //i++;
    }
    return s;
}

/// @brief Takes two number arrays and their sizes, and returns TRUE if the first number is 
///        larger than or equal to the second number.
/// @param n1 The array of the larger number
/// @param s1 The size of the array of the larger number
/// @param n2 The array of the smaller number
/// @param s2 The size of the array of the smaller number
/// @return boolean result of the operation
bool leq(int* n1, int s1, int* n2, int s2) {
    // convert n1 into string and cut leading zeros
    string n1_as_string;  
    for (int i = 0; i < s1; i++) { 
        n1_as_string =  n1_as_string + to_string(n1[i]);
    }
    n1_as_string = cut_leading_zeros(n1_as_string);

    // convert n2 into string and cut leading zeros
    string n2_as_string;  
    for (int i = 0; i < s2; i++) { 
        n2_as_string =  n2_as_string + to_string(n2[i]);
    }
    n2_as_string = cut_leading_zeros(n2_as_string);

    bool equal = true;

    if (n1_as_string.length() > n2_as_string.length()) { //if n1 has more digits, l is true, eq is false.
        equal = false;
        return true;
    } else if (n2_as_string.length() > n1_as_string.length()) { //if n2 has more digits, l is false, eq is false.
        equal = false;
        return false;
    } else if (n1_as_string.length() == n2_as_string.length()) { //if digit count is equal...
        for (int i = 0; i < s2; i++) {
            if (n1_as_string[i] > n2_as_string[i]) {             //...AND n1[i] > n2[i], l is true, eq is false
                equal = false;          
                return true;
            } else if (n2_as_string[i] > n1_as_string[i]) {      //...AND n2[i] > n1[i], l is true, eq is false
                //...AND n1[i] > n2[i], l is true, eq is false
                return false;
            } else {
                equal = true; 
            }
        }
    }
    if (equal == true && 
        n1_as_string[n1_as_string.length()-1] == n2_as_string[n2_as_string.length()-1]) {
        return true; //this is if the two numbers are equal.
    }
}

/// @brief Takes two number arrays and their sizes, and calculates the sum of the two numbers.
/// @param n1 The array of the larger number
/// @param s1 The size of the array of the larger number
/// @param n2 The array of the smaller number
/// @param s2 The size of the array of the smaller number
/// @return string result of the addition operation
string addition(int* n1, int s1, int* n2, int s2) {

    string final_sum;
    int carry = 0;
    int digit_sum = 0;

    for ( int i = 1; i <= s1; i++ ) {
        if (s1 == s2 && i == s1) { //if digit count is equal and we've reached the last digit (special case)
            digit_sum = n1[s1-i] + n2[s2-i] + carry;
            final_sum = to_string(digit_sum) + final_sum;
        } else if (s2-i >= 0) { //if we haven't yet run out of digits in n2
            digit_sum = n1[s1-i] + n2[s2-i] + carry;
            final_sum = to_string(digit_sum%10) + final_sum;
            carry = int(digit_sum)/int(10);
        } else if (s2-i < 0) { //after we run out of digits in n2
            digit_sum = n1[s1-i] + carry;
            final_sum = to_string(digit_sum%10) + final_sum;
            carry = int(digit_sum)/int(10);
        } 
    }
    return final_sum;
}

/// @brief Takes two number arrays and their sizes, and calculates the smaller number subtracted 
///        from the larger number.
/// @param n1 The array of the larger number
/// @param s1 The size of the array of the larger number
/// @param n2 The array of the smaller number
/// @param s2 The size of the array of the smaller number
/// @return string result of the subtraction operation
string subtraction(int* n1, int s1, int* n2, int s2) {
    string final_sub;
    int digit_sub;
    int borrow = 0;

    for ( int i = 1; i <= s1; i++ ) {
        if (s2-i >= 0) { // if we haven't yet reached the last digit of n2
            if ( n1[s1-i] + borrow >= n2[s2-i]) { // this is the straightforward part.
                digit_sub = ( n1[s1-i] + borrow ) - n2[s2-i];
                borrow = 0;
                final_sub = to_string(digit_sub) + final_sub;
            } else { // if s1<s2, what do? add ten to current, make borrow -1, apply borrow to neighbor. 
                n1[s1-i] += 10;
                digit_sub = ( n1[s1-i] + borrow ) - n2[s2-i];
                borrow = -1;
                final_sub = to_string(digit_sub) + final_sub;
            } 
        } else if (s2-i < 0) { //there are no more n2 digits left. working with n1 only.
            if ( (n1[s1-i] + borrow >= 0) ) { //if the digit not zero
                digit_sub = n1[s1-i] + borrow;
                borrow = 0;
                final_sub = to_string(digit_sub) + final_sub;
            } else if ( (n1[s1-i] + borrow < 0) && (s1-i != 0) ) {//if digit is less than zero and not last
                n1[s1-i] += 10;
                digit_sub = n1[s1-i] + borrow;
                borrow = -1;
                final_sub = to_string(digit_sub) + final_sub;     
            }
        } 
    }
    return cut_leading_zeros(final_sub);
}

/// @brief Takes two number arrays and their sizes, and calculates the larger number modulus 
///        smaller number.
/// @param n1 The array of the larger number
/// @param s1 The size of the array of the larger number
/// @param n2 The array of the smaller number
/// @param s2 The size of the array of the smaller number
/// @return string result of the modulus operation
string modulo(int* n1, int s1, int* n2, int s2) {
    string n2_as_string;   // will store n2 as string to make it easier to multiply by pwrs of 10

    //convert n2 into string
    for (int i = 0; i < s2; i++) { //add (s1-s2-1) zeros for n2*10^(s1-s2-1) 
        n2_as_string = n2_as_string + to_string(n2[i]);
    }
    string zeros;
    for (int i = 0; i < s1-s2-1; i++) { //add (s1-s2-1) zeros for n2*10^(s1-s2-1) 
        zeros += "0";
    }
    // add the zeros to the end of n2_as_string
    string mult_n2_as_string = n2_as_string + zeros;
    int s_new;
    s_new = s2 + (s1-s2-1);

    int* multiple_of_n2 = new int[s_new];         // create new array to store the multiplication result
    for (int i = 0; i < s_new; i++) {   // read n2_as_string into multiple_of_n2
        multiple_of_n2[i] = int(mult_n2_as_string[i]) - 48;
    }

    // starts from (n1 - multiple_of_n2) and decreases by increments of n2 while (remainder > n2)
    int* remainder = new int[s1]; // new array that will hold the remainder 
    string remainder_as_string = subtraction(n1, s1, multiple_of_n2, s_new);
    for (int i = 0; i < s1; i++) {   // read remainder_as_string into remainder array
        remainder[i] = int(remainder_as_string[i]) - 48;
    }

    while (stoi(subtraction(remainder, s1, n2, s2)) > stoi(n2_as_string) ) { //if (remainder//n2) is larger than zero
        remainder_as_string = subtraction(remainder, s1, n2, s2);
        for (int i = 0; i < s1; i++) {   // read remainder_as_string into remainder array
            remainder[i] = int(remainder_as_string[i]) - 48;
        }
    }
}

/// @brief This function takes the operator symbol and sends the number arrays and sizes 
///        to the function of the appropriate mathematical operation.
/// @param o  String of operator symbol.
/// @param n1 Number array of the larger number
/// @param s1 Size of the larger number array
/// @param n2 Number array of the smaller number
/// @param s2 Size of the smaller number array
/// @return string return of whatever the operation functions return.
string math_operation(string o, int* n1, int s1, int* n2, int s2) {
    if ( o == "+" ) {
        return addition(n1, s1, n2, s2);
    } else if ( o == "-" ) {
        return subtraction(n1, s1, n2, s2);
    } else if ( o == "%" ) {
        return modulo(n1, s1, n2, s2);
    } else {
        cout << "Invalid operator. Try again with valid input for operator. \n";
    }
}

/// @brief Takes input from a file.
/// @param file_name The name of the file that contains the input.
void input_from_file(string file_name) {
    ifstream the_file(file_name);     // ifstream of file
    the_file >> OPERATOR >> NUMBER1 >> NUMBER2; //get input  
}

/// @brief Controls the flow of code.
int main(int argc, char ** argv) {
    string file_name = argv[1];
    input_from_file(file_name);

    // read NUMBER1 into array digits1
    int size1 = NUMBER1.length();
    int* digits1 = new int[size1];
    for (int i = 0; i < size1; i++) {
        digits1[i] = int(NUMBER1[i]) - 48;
    }

    //read number2 into array digits2
    int size2 = NUMBER2.length();
    int* digits2 = new int[size2];
    for (int i = 0; i < size2; i++) {
        digits2[i] = int(NUMBER2[i]) - 48;
    };

    // apply operation - send the larger number's array first into the function!
    if (leq(digits1, size1, digits2, size2)) {
        cout << math_operation(OPERATOR, digits1, size1, digits2, size2) << '\n';
    } else { 
        cout << math_operation(OPERATOR, digits2, size2, digits1, size1) << '\n';
    }
}