 /**
    * Reads integers from file into a BST and takes a target key to remove from the BST,
    * then outputs the results of JR-remove and normal remove. 
    * @file main.cpp
    * @author(s) Derya Arikan
    * Pseudocode for the calculate_depth() function was written collaboratively with 
    * Peter Ryan. See binarysearchtree.cc for more details. 
    * @date April 19, 2023
    */
#include <iostream>
#include <fstream>
#include <vector>
#include "node.h"
#include "binarysearchtree.h"

using namespace std;

/// @brief Reads the values into the BST from file, reads target key from file,
/// and outputs the results of JR remove and normal remove. 
/// @param file_name the input file's name
void test_from_file(string file_name) {
    ifstream the_file(file_name);

    if (!the_file.is_open()) {
        cout << "File not found: " << file_name << endl;
        throw invalid_argument("File not found: " + file_name);
    }

    Binary_Search_Tree bst1, bst2;
    int item;
    vector<int> numbers;
    
    while (the_file >> item) {
        numbers.push_back(item);
    }

    int target_key = numbers[numbers.size()-1];
    numbers.pop_back();

    for (int i = 0; i < numbers.size(); i++) {
        bst1.insert(numbers[i]);
        bst2.insert(numbers[i]);
    }

    bst1.remove(target_key);
    bst1.display();
    bst2.JR_remove(target_key);
    bst2.display();

    cout << "NORMAL REMOVE:\nDepth of tree:" << bst1.calculate_depth(bst1.root) << endl;
    cout << "JR REMOVE:\nDepth of tree:" << bst2.calculate_depth(bst2.root) << endl;

}

/// @brief Testing the program with a function that does not require an input file. 
void test_from_function() {
    // NORMAL REMOVAL
    Binary_Search_Tree bst;
    bst.insert(7); bst.insert(11); bst.insert(3);
    bst.insert(2); bst.insert(17); bst.insert(5);
    bst.insert(10);

    bst.display();

    bst.remove(17); cout << "NORMAL REMOVE \nRemoved 17: \n";
    bst.display();

    cout << "Depth of tree:" << bst.calculate_depth(bst.root) << endl;

    // JR REMOVE
    Binary_Search_Tree bst_jr;
    bst_jr.insert(7); bst_jr.insert(11); bst_jr.insert(3);
    bst_jr.insert(2); bst_jr.insert(17); bst_jr.insert(5);
    bst_jr.insert(10);

    bst_jr.display();

    bst_jr.JR_remove(17); cout << "JR-REMOVE \nRemoved 17: \n";
    bst_jr.display();

    cout << "Depth of tree:" << bst_jr.calculate_depth(bst_jr.root) << endl;

}  

/// @brief Controls program flow.
/// @param argc Argument count
/// @param argv Argument vector
int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <commands file name>" << endl;
        exit(1);
    }

    string test_file = argv[1];
    test_from_file(test_file);
    //test_from_function();
} 
